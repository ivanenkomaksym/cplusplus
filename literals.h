#ifndef LITERALS_H
#define LITERALS_H

#include <iostream>
#include <string>

using namespace std;

constexpr long double operator"" _cm(long double x) { return x * 10; }
constexpr long double operator"" _m(long double x) { return x * 1000; }
constexpr long double operator"" _mm(long double x) { return x; }

// Example:
int operator"" _bin(const char *str, size_t l)
{
    int ret = 0;
    for (int i = 0; i < l; i++)
    {
        ret = ret << 1;
        if (str[i] == '1')
            ret += 1;
    }
    return ret;
}

void literals()
{
    /*
    * 14. New String Literals
    */

    // C++ 03:
    char*     a1 = "string";

    // C++ 11:
    char*     a = u8"string";  // to define an UTF-8 string.
    char16_t* b = u"string";   // to define an UTF-16 string.
    char32_t* c = U"string";   // to define an UTF-32 string.
    char*     d = R"(string\\)";  // to define raw string.

    /*
    *  User defined Literals
    */

    /*
    * Literals are constants.
    *
    * C++ has 4 kinds of literals:
    * 	integer         ---  45
    * 	floating point  ---  4.5
    * 	character       ---  'z'
    * 	string          ---  "Dog"
    */

    // 45;  // int literal
    // 45u;  // unsigned int  (suffix specifies type)
    // 45l;  // long

    //C++ 99:
    long double height1 = 3.4;  // Metres? Centimeters? Inches?

    // Ideally, always attach units to the values:
    // height = 3.4cm;
    // ratio = 3.4cm / 2.1mm; //  ratio = 3.4 * 10 / 2.1

    //Why we don't do that anymore?
    // 1. No language support
    // 2. Run time cost associated with the unit translation

    // C++ 11:
    long double height = 3.4_cm;
    cout << height  << endl;              // 34
    cout << (height + 13.0_m)  << endl;   // 13034
    cout << (130.0_mm / 13.0_m)  << endl; // 0.01

    //Note: add constexpr to make the translation happen in compile time.
    cout << "110 is " << "110"_bin << endl;
    cout << "1100110 is " << "1100110"_bin << endl;

    /* Restriction: it can only work with following parameters:
    char const*
    unsigned long long
    long double
    char const*, std::size_t
    wchar_t const*, std::size_t
    char16_t const*, std::size_t
    char32_t const*, std::size_t*/
    // Note: return value can be of any types.

    // C++ went a long way to make user defined types (classes) to behave same as build-in types.
    // User defined literals pushes this effort even further
}

#endif // LITERALS_H
