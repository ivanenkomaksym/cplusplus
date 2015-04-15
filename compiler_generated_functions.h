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
#endif // COMPILER_GENERATED_FUNCTIONS_H
