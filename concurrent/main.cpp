#include <QCoreApplication>

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <chrono>
#include <condition_variable>
#include <future>

class Message
{
    public:
        std::string getHeader (const std::string& header_name) const { return header_name; }
        // other methods...
};

class MessageSorter
{
    public:
        // take the field to sort by in the constructor
        MessageSorter (const std::string& field) : _field( field ) {}
        bool operator() (const Message& lhs, const Message& rhs)
        {
            // get the field to sort by and make the comparison
            return lhs.getHeader( _field ) < rhs.getHeader( _field );
        }
    private:
        std::string _field;
};

void functorExample()
{
    std::vector<Message> messages;
    // read in messages
    MessageSorter comparator("str");
    sort( messages.begin(), messages.end(), comparator );
}

void function_1()
{
    std::cout << "function_1" << std::endl;
}

class Fctor
{
public:
    void operator()()
    {
        for (int i = 0; i > -100; i--)
            std::cout << "from t1 " << i << std::endl;
    }
};

class Fctor2
{
public:
    void operator()(std::string &msg)
    {
        std::cout << "t2 says: " << msg << std::endl;
        msg = "something";  // even though msg is & msg is passed by value
    }
};

void thread_management()
{
    std::cout << std::this_thread::get_id() << std::endl;   // thread id

    // Wrapper w(t1);   //joined in dctor
    Fctor fct;
    std::thread t1(fct); // t1 starts

    std::thread t1copy = std::move(t1); // thread can only be moved, not copied
    std::cout << t1copy.get_id() << std::endl;

    t1copy.join();

    std::string s = "Where there is no trust, there is no love";
    std::thread t2((Fctor2()), std::ref(s));

    t2.join();

    std::cout << "from main: " << s << std::endl;

    std::cout << "max nr of threads: " << std::thread::hardware_concurrency() << std::endl;    // Indication  how many thread can be run
}

std::mutex mu;

void shared_print(std::string msg, int id)
{
    std::lock_guard<std::mutex> guard(mu);  // RAII in case of exception to definetely unlock the mutex
    //mu.lock();
    std::cout << msg << id << std::endl;
    //mu.unlock();
}

void function_1_shared()
{
    for (int i = 0; i > -100; i--)
        shared_print("From function_1_shared: ", i);
}

class LogFile
{
public:
    LogFile()
    {
        f.open("log.txt");
    } // Need dctor to clock file

    void shared_print(std::string id, int value)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        f << "From" << id << ": " << value << std::endl;
        std::cout << "From" << id << ": " << value << std::endl;
    }

    // Never return f to the outside world

private:
    std::mutex m_mutex;
    std::ofstream f;     // Under protection of mutex
};

void function_2_shared(LogFile &log)
{
    for (int i = 0; i > -100; i--)
        log.shared_print("From function_2_shared: ", i);
}

void mutex_example()
{
    std::thread t1(function_1_shared);

    for (int i = 0; i < 100; i++)
        shared_print("From mutex_example: ", i);

    t1.join();

    // Second example
    LogFile log;
    std::thread t2(function_2_shared, std::ref(log));

    for (int i = 0; i < 100; i++)
        log.shared_print("From mutex_example: ", i);

    t2.join();
}

class LogFileDeadLock
{
public:
    LogFileDeadLock()
    {
        f.open("log.txt");
    } // Need dctor to clock file

    void shared_print(std::string id, int value)
    {
        //std::lock_guard<std::mutex> locker(m_mutex);    // t2 lock m_mutex
        //std::lock_guard<std::mutex> locker2(m_mutex2);  // t2 waiting for main to release m_mutex2
        std::lock(m_mutex, m_mutex2);
        std::lock_guard<std::mutex> locker(m_mutex, std::adopt_lock);
        std::lock_guard<std::mutex> locker2(m_mutex2, std::adopt_lock);
        std::cout << "From" << id << ": " << value << std::endl;
    }

    void shared_print2(std::string id, int value)
    {
        std::lock_guard<std::mutex> locker2(m_mutex2);  // main locks m_mutex2
        std::lock_guard<std::mutex> locker(m_mutex);
        std::cout << "From" << id << ": " << value << std::endl;
    }

    // Never return f to the outside world

private:
    std::mutex m_mutex;
    std::mutex m_mutex2;
    std::ofstream f;     // Under protection of mutex
};

void function_2_shared_deadlock(LogFileDeadLock &log)
{
    for (int i = 0; i > -100; i--)
        log.shared_print("From function_2_shared_deadlock: ", i);
}

void deadlock_example()
{
    /*
     * To avoid deadlocks:
     * 1. Prefer locking single mutex
     * 2. Avoid calling a mutex and then calling a user function
     * 3. std::lock to lock more than one mutex
     * 4. Lock in the same order
     */
    LogFileDeadLock log;
    std::thread t2(function_2_shared_deadlock, std::ref(log));

    for (int i = 0; i < 100; i++)
        log.shared_print2("From deadlock_example: ", i);

    t2.join();
}

class LogFileUnique
{
public:
    LogFileUnique()
    {
    }

    void shared_print(std::string id, int value)
    {
        //std::unique_lock<std::mutex> locker(m_mutex_open);        // Lazy initialization
        //if (!f.is_open())
        //{
        //    f.open("log.txt");
        //}
        std::call_once(m_flag, [&](){f.open("log.txt");});

        std::unique_lock<std::mutex> locker(m_mutex, std::defer_lock);
        // do something else

        locker.lock();
        std::cout << "From" << id << ": " << value << std::endl;
        locker.unlock();
        //...
        locker.lock();
        std::unique_lock<std::mutex> locker2 = std::move(locker);
        locker2.unlock();
    }

    // Never return f to the outside world

private:
    std::mutex m_mutex;
    std::mutex m_mutex_open;
    std::once_flag m_flag;
    std::ofstream f;     // Under protection of mutex
};

void function_2_unique(LogFileUnique &log)
{
    for (int i = 0; i > -100; i--)
        log.shared_print("From function_2_unique: ", i);
}

void unique_lock_example()
{
    LogFileUnique log;
    std::thread t2(function_2_unique, std::ref(log));

    for (int i = 0; i < 100; i++)
        log.shared_print("From unique_lock_example: ", i);

    t2.join();
}

std::deque<int> q;
std::condition_variable cond;

void func1()    // producer of the data
{
    int count = 10;
    while (count > 0)
    {
        std::unique_lock<std::mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        //cond.notify_one();
        cond.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        count--;
    }
}

void func2()    // consumer of the data
{
    int data = 0;
    while (data != 1)
    {
        std::unique_lock<std::mutex> locker(mu);
        //cond.wait(locker);  // in sleep until notified by thread 1
        cond.wait(locker, [](){ return !q.empty(); });  // spurious wake
        if (!q.empty())
        {
            data = q.back();
            q.pop_back();
            locker.unlock();
            std::cout << "t2 got a value from t1: " << data << std::endl;
        }
        //else
        //{
        //    locker.unlock();
        //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //}
    }
}

void condition_varible()
{
    std::thread t1(func1);
    std::thread t2(func2);

    t1.join();
    t2.join();
}

int factorial(int N)
{
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;

    std::cout << "Result is: " << res << std::endl;
    return res;
}

int factorial2(std::future<int> &f)
{
    int res = 1;

    int N = f.get();    // if not set std::future_errc::broken_promise
    for (int i = N; i > 1; i--)
        res *= i;

    std::cout << "Result is: " << res << std::endl;
    return res;
}

void future_promise()
{
    // Pass value from child thread to a parent thread
    int x;
    //std::thread t1(factorial, 4, std::ref(x));
    //std::future<int> fu = std::async(factorial, 4); // get something in the future
    //std::future<int> fu = std::async(std::launch::deferred, factorial, 4);  // not create a thread, defer the execution
    std::future<int> fu = std::async(std::launch::async, factorial, 4);  // create another thread
    //std::future<int> fu = std::async(std::launch::deferred | std::launch::async, factorial, 4);  // determined by the implementation, by default
    x = fu.get();   // wait until the child thread finish
    // fu.get();    // crash. Call only once
    //t1.join();

    // Pass value from parent thread to a child thread
    std::cout << "X= " << x << std::endl;

    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::future<int> fu2 = std::async(std::launch::async, factorial2, std::ref(f)); // send him the value in the future
    // do something else
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    p.set_value(4);
    // p.set_exception(std::make_exception_ptr(std::runtime_error("To err is human")));

    x = fu2.get();

    std::cout << "X2= " << x << std::endl;

    // Multiple threads
    std::shared_future<int> sf = f.share();

    //std::future<int> fu3 = std::async(std::launch::async, factorial2, sf);
    //std::future<int> fu4 = std::async(std::launch::async, factorial2, sf);
    //std::future<int> fu5 = std::async(std::launch::async, factorial2, sf);
    //std::future<int> fu6 = std::async(std::launch::async, factorial2, sf);
}

class A
{
public:
    void f(int x, char c) {}
    long g(double x) { return 0; }
    int operator()(int N) { return 0; }
};

void foo(int x){}

void callable_objects()
{
    A a;
    std::thread t0(a , 6);  // copy_of_a() in a different thread
    //std::async(std::launch::async, a, 6); // same
    //std::bind(a, 6);                      // same
    //std::call_once(std::once_flag, a, 6); // same
    std::thread t1(std::ref(a), 6); // a() in a different thread
    std::thread t3(A(), 6); // temp A;
    std::thread t4([](int x){ return x*x; }, 6);
    std::thread t5(foo, 7);
    std::thread t6(&A::f, a, 8, 'w');   // copy_of_a.f(8, 'w') in a different thread
    std::thread t7(&A::f, &a, 7, 'w');   // a.f(8, 'w') in a different thread
    std::thread t8(std::move(a), 6);    // no longer usable in the main thread

    t0.join();
    t1.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
}

std::deque<std::packaged_task<int()> > task_q;

void thread_1()
{
    std::packaged_task<int()> t;
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){ return !task_q.empty(); });
        t = std::move(task_q.front());
        task_q.pop_front();
    }
    t();
}

void packaged_task()
{
    std::packaged_task<int(int)> t(factorial);  // cannot pass a parameter
    std::packaged_task<int()> t1(std::bind(factorial, 6));
    //auto t = std::bind(factorial, 6);
    //...
    t(6);   // In a different context, can be transported
    //int x = t1.get_future().get();

    //t1();

    //std::cout << "X3 = " << x << std::endl;

    // Deque
    std::future<int> fu = t1.get_future();
    {
        std::lock_guard<std::mutex> locker(mu);
        task_q.push_back(std::move(t1));
    }
    cond.notify_one();

    std::cout << "Packaged task: " << fu.get() << std::endl;
}

int main(int argc, char *argv[])
{
    std::thread t1(function_1); // t1 starts running

    t1.join();                  // main thread waits for t1 to finish
    //t1.detach();                // t1 will freely on its own -- daemon process

    if (t1.joinable())
        t1.join();                // no join anymore

    thread_management();
    mutex_example();
    deadlock_example();
    unique_lock_example();
    condition_varible();
    future_promise();
    callable_objects();
    packaged_task();

    return 0;
}

