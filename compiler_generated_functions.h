#ifndef COMPILER_GENERATED_FUNCTIONS_H
#define COMPILER_GENERATED_FUNCTIONS_H

#include <string>

using namespace std;

namespace COMPILER_GENERATED_FUNCTIONS
{
/*
  C++ 03:
  1. default constructor (generated only if no constructor is declared by user)
  2. copy constructor (generated only if no 5, 6 not declared)
  3. copy assignment operator (generated only if no 5, 6 declared)
  4. destructor

  C++ 11:
  1. default constructor (generated only if no constructor is declared by user)
  2. copy constructor (generated only if no 3, 4, 5, 6 not declared)
  3. copy assignment operator (generated only if no 2, 4, 5, 6 declared)
  4. destructor
  5. move constructor (generated only if 2, 3, 4, 6 not declared by user)
  6. move assignment operator (generated only if 2, 3, 4, 5 not declared by user)
  */

class Dog
{
public:
    // C++ 03:
    Dog() {}
    Dog(string name) {}
    Dog(const Dog &) {}
    Dog &operator = (const Dog &) {}
    ~Dog() {}

    // C++ 11:
    Dog(Dog &&) {}
    Dog &operator = (Dog &&) {}
};

class Frog
{
    Frog(int = 0) {}                  // default ctor
    Frog(const Frog &, int = 0) {}    // copy ctor
    Frog(Frog &&, int = 0) {}         // move ctor
};

class Cow   // 1, 2(deprecated), 4
{
    Cow &operator = (const Cow &) = delete;
};

template<class T>
class NamedObject
{
public:
    NamedObject(std::string& name, const T& value)
        : nameValue(name)
        , objectValue(value)
    {}
    // operator= is not declared
    //
private:
    std::string& nameValue;           // this is now a reference
    const T objectValue;              // this is now const
};

class Uncopyable
{
protected:                                   // allow construction
    Uncopyable() {}                            // and destruction of
    ~Uncopyable() {}                           // derived objects...

    //Uncopyable(const Uncopyable&) = delete;
    //Uncopyable& operator=(const Uncopyable&) = delete;

private:
    Uncopyable(const Uncopyable&);             // ...but prevent copying
    Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale: private Uncopyable       // class no longer declares copy ctor or copy assign. operator
{
public:
    HomeForSale(){}
};

class DBConnection
{
public:
    explicit DBConnection() = default;

    static DBConnection create()
    {
        return DBConnection();
    }

    void close()
    {
    }
};

class DBConn
{                          // class to manage DBConnection
public:                                 // objects
    explicit DBConn(DBConnection dbConnection)
        : db(dbConnection)
    {}

    ~DBConn()
    {
        if (!closed)
        {
            try
            {                                           // close the connection
                db.close();                             // if the client didn't
            }
            catch (...)
            {   // if closing fails, note that and terminate or swallow
                //make log entry that call to close failed;
            }
        }
    }

    void close()                                     // new function for
    {                                                // client use
        db.close();
        closed = true;
    }

private:
    DBConnection db;
    bool closed;
};

class Transaction
{
public:
    explicit Transaction(const std::string& logInfo)
    {
        // virtualLogTransaction();                         // Do not call virtual functions in ctors
        logTransaction(logInfo);                                // non-virtual call
    }
    void logTransaction(const std::string& logInfo) const{}   // non-virtual func

    virtual void virtualLogTransaction() const = 0;       // make type-dependent
};

class BuyTransaction: public Transaction
{
public:
    BuyTransaction(const std::string& logInfo)
        : Transaction(createLogString(logInfo))             // pass log info to base class ctor
    {}

    virtual void virtualLogTransaction() const override {}

private:
    static std::string createLogString(const std::string& logInfo) { return std::string("Some info"); }
};

class Bitmap{};

class Widget
{
public:
    Widget& operator+=(const Widget& rhs)   // the convention applies to +=, -=, *=, etc.
    {
        return *this;
    }

    Widget& operator=(const Widget& rhs)
    {
      Widget temp(rhs);             // make a copy of rhs's data
      swap(temp);                   // swap *this's data with the copy's
      return *this;
    }

    Widget& operator=(Widget rhs)   // rhs is a copy of the object
    {                                       // passed in — note pass by val
      swap(rhs);                            // swap *this's data with
                                            // the copy's
      return *this;
    }

private:
    void swap(Widget& rhs){}   // exchange *this's and rhs's data;

    Bitmap *pb;                 // ptr to a heap-allocated object
};


void logCall(const std::string& funcName)
{
    std::cout << funcName << std::endl;
}

class Date {};       // for dates in time

class Customer
{
public:
    explicit Customer() = default;
    Customer(const Customer& rhs);
    Customer& operator=(const Customer& rhs);

private:
    std::string name;
    Date lastTransaction;
};

Customer::Customer(const Customer& rhs)
    : name(rhs.name)                                 // copy rhs's data
{
    logCall("Customer copy constructor");
}

Customer& Customer::operator=(const Customer& rhs)
{
    logCall("Customer copy assignment operator");
    name = rhs.name;                               // copy rhs's data
    return *this;                                  // see Item 10
}

class PriorityCustomer: public Customer
{
public:
    explicit PriorityCustomer() = default;
    PriorityCustomer(const PriorityCustomer& rhs);
    PriorityCustomer& operator=(const PriorityCustomer& rhs);

private:
    int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
    : Customer(rhs)                   // invoke base class copy ctor
    , priority(rhs.priority)
{
    logCall("PriorityCustomer copy constructor");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
    logCall("PriorityCustomer copy assignment operator");
    Customer::operator=(rhs);           // assign base class parts
    priority = rhs.priority;
    return *this;
}

void compiler_generated_functions()
{
    std::string newDog("Persephone");
    std::string oldDog("Satch");

    NamedObject<int> p(newDog, 2);
    NamedObject<int> s(oldDog, 36);
    //NamedObject<int> r(p);          // couldn't create a default copy constructor and default assignment operator
    //p = s;                          // because of reference member nameValue and const member objectValue

    HomeForSale a;
    //auto b = HomeForSale(a);          // Error: copy ctor not allowed
    //auto c = a;                       // Error: assignment operator not allowed

    DBConn dbc(DBConnection::create()); // Destructors should never emit exceptions

    auto name = std::string("Text");
    auto transaction = BuyTransaction(name);
    auto customer1 = PriorityCustomer();
    auto customer2 = PriorityCustomer();
    customer1 = customer2;
}

}
#endif // COMPILER_GENERATED_FUNCTIONS_H
