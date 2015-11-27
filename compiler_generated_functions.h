#ifndef COMPILER_GENERATED_FUNCTIONS_H
#define COMPILER_GENERATED_FUNCTIONS_H

#include <string>

using namespace std;

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
}

#endif // COMPILER_GENERATED_FUNCTIONS_H
