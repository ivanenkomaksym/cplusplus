#ifndef SMART_POINTERS_H
#define SMART_POINTERS_H

#include <memory>

using namespace std;

namespace SMART_POINTERS
{
    class Dog
    {
    public:
        Dog() {}
        Dog(string name) { cout << "Dog is created: " << name << endl; m_name = name; }
        ~Dog() { cout << "dog is destroyed: " << m_name << endl; }

        void bark() { cout << "Dog " << m_name << " rules!" << endl; }
        void makeFriend(shared_ptr<Dog> f) { m_pFriend = f; }
        void showFriend()
        {
            if (!m_pFriend.expired())
                cout << "My friend is: " << m_pFriend.lock()->m_name << endl;
            cout << " He is owned by " << m_pFriend.use_count() << " pointers." << endl;
        }
    private:
        //shared_ptr<Dog> m_pFriend;    // cyclic reference
        weak_ptr<Dog> m_pFriend;

        string m_name;
    };

    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    class Foo
    {
    public:
        Foo(Foo &&rhs)
        {}
    };

    class MyClass
    {
    public:
        MyClass() = default;
        MyClass(std::vector<std::unique_ptr<Foo>> foos) :
            foos_(std::move(foos))
        {};

        std::vector<std::unique_ptr<Foo>> &getFoos() { return foos_; }

        std::vector<std::unique_ptr<Foo>> foos_;
    };

    void bar(std::vector<std::unique_ptr<Foo>> &foos)
    {

    }

    void vectorOfUniquePointers()
    {
        //auto test = MyClass(std::vector<std::unique_ptr<Foo>>()); //remove this, and all works fine!
        auto myClass = make_unique<MyClass>();
        bar(myClass->getFoos());
    }

    void shared_pointers()
    {
        shared_ptr<Dog> p1 = make_shared<Dog>("Gunner");
        shared_ptr<Dog> p2 = make_shared<Dog>("Tank");
        //p1 = p2;        // Gunner is deleted
        //p1 = nullptr;   // Gunner is deleted
        //p1.reset();     // Gunner is deleted

        // Custom deleter
        shared_ptr<Dog> p3 = shared_ptr<Dog>(new Dog("Tank")
                                             , [](Dog *p) { cout << "Custom deleting." << endl; delete p;});

        //shared_ptr<Dog> p4(new Dog[3]); // dog[1] and dog[2] memory leak
        shared_ptr<Dog> p5(new Dog[3], [](Dog *p) { delete []p; });
    }

    void weak_pointers()
    {
        shared_ptr<Dog> pD(new Dog("Gunner"));
        shared_ptr<Dog> pD2(new Dog("Smokey"));
        pD->makeFriend(pD2);
        pD2->makeFriend(pD);

        pD->showFriend();
    }

    unique_ptr<Dog> getDog()
    {
        unique_ptr<Dog> p(new Dog("Smokey"));
        return p;
    }

    void unique_pointers()
    {
        unique_ptr<Dog> pD(new Dog("Gunner"));
        unique_ptr<Dog> pD2(new Dog("Smokey"));
        pD2 = move(pD);
        // 1. Smokey is destroyed
        // 2. pD becomes empty.
        // 3. pD2 owns Gunner.

        pD2->bark();
    //    f(move(pD));
    //    if (!pD) {
    //        cout << "pD is empty.\n";
    //    }
    //
        auto pD3 = getDog();
        pD3->bark();
        // Custom deleter
        //shared_ptr<Dog> p3 = shared_ptr<Dog>(new Dog("Tank")
        //                                     , [](Dog *p) { cout << "Custom deleting." << endl; delete p;});
        unique_ptr<Dog[]> dogs(new Dog[3]);
        dogs[1].bark();
        //(*dogs).bark(); // * is not defined
    }
}

#endif // SMART_POINTERS_H
