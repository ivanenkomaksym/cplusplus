#ifndef DEDUCING_TYPES_H
#define DEDUCING_TYPES_H

template<typename T>
void f(T& param);       // param is a reference

int x = 27;             // int
const int cx = x;       // const int
const int &rx = x;      // & const int

f(x);                   // T is int, param's type is int&
f(cx);                  // T is const int, param's type is const int&
f(rx);                  // T is const int, param's type is const int&

//-------------------------------------------------------------------------

template<typename T>
void f(const T& param); // param is a reference to const

int x = 27;             // int
const int cx = x;       // const int
const int &rx = x;      // & const int

f(x);                   // T is int, param's type is const int&
f(cx);                  // T is int, param's type is const int&
f(rx);                  // T is int, param's type is const int&

//-------------------------------------------------------------------------

template<typename T>
void f(T* param); // param is a reference to const

int x = 27;             // int
const int *px = &x;     // px is a ptr to x as a const int

f(x);                   // T is int, param's type is int*
f(px);                  // T is const int, param's type is const int*

//-------------------------------------------------------------------------

template<typename T>
void f(T&& param);       // param is a universal reference

int x = 27;             // int
const int cx = x;       // const int
const int &rx = x;      // & const int

f(x);                   // T is int, param's type is int&
f(cx);                  // T is const int, param's type is const int&
f(rx);                  // T is const int, param's type is const int&
f(27);                  // 27 is rvalue, so T is int, param's type is int&&

//-------------------------------------------------------------------------

template<typename T>
void f(T param);        // param is passed by value

int x = 27;             // int
const int cx = x;       // const int
const int &rx = x;      // & const int

f(x);                   // T is int, param's type is int
f(cx);                  // T is int, param's type is int
f(rx);                  // T is int, param's type is int

#endif // DEDUCING_TYPES_H
