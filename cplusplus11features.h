#ifndef CPLUSPLUS11FEATURES_H
#define CPLUSPLUS11FEATURES_H

#include <initializer_list>
#include <vector>

class Widget
{
public:
    Widget() {}
    Widget(int i, bool b) {}
    Widget(int i, double b) {}
    Widget(std::initializer_list<bool> il) {}
};

void cplusplus11features()
{
    Widget w1(10, 5.0);  // Calls Widget(int i, double b).
    Widget w2{10, 5.0};  // Calls std::initializer_list ctor. Error! requires narrowing conversion.
    Widget w3({});       // Calls std::initializer_list ctor with empty list.
    Widget w4{{}};       // ditto.

    std::vector<int> v1(10, 20);    // create 10-element vector with value 20
    std::vector<int> v2{10, 20};    // use std::initializer_list to create 2-element vector with values 10 and 20.
}

#endif
