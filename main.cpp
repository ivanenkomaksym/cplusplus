#include<iostream>
#include<vector>

#include "move_semantics.h"
#include "literals.h"
#include "compiler_generated_functions.h"
#include "cplusplus11features.h"
#include "smart_pointers.h"
#include "resource_managing_class.h"
#include "enum_hack.h"
#include "constness.h"

#include <map>
#include <string>

using namespace SMART_POINTERS;
using namespace COMPILER_GENERATED_FUNCTIONS;

class Widget2
{
public:
    Widget2() = default;
    ~Widget2() = default;

    Widget2(const Widget2 &) = delete;
    Widget2(Widget2 &&) noexcept
    {
    }
};

Widget2 getWidget2()
{
    auto w2 = Widget2();

    return w2;
}

class WidgetFactory
{
public:

    void addElement(Widget2 widget)
    {
        widgets.push_back(std::move(widget));
    }

    void lambda(Widget2 &widget)
    {
        auto valid = true;
        auto globalerror = std::string();

        auto reportError = [&](std::string error)
        {
            valid = false;
            globalerror = error;
            //widgets.emplace_back(widget);
        };
    }

private:
    std::vector<Widget2> widgets;
};

struct SimpleStruct
{
    int a;
    double b;
    std::string str;
};

enum class ValidType
   {
   VALID = 0,
   WARNINGS,
   NOTVALID
   };

struct InvalidObject
   {
   std::string objectName;
   std::string instanceName;
   std::string reason;
   ValidType   validType = ValidType::NOTVALID;
   };

class Base
{
public:
    void a(){}
protected:
    void b(){}
private:
    void c(){}
};

class Derived : private Base
{
public:
    Derived()
    {
        a();
        b();
        //c();
    }
};

class Derived2 : private Derived
{
public:
    Derived2()
    {
        //a();
        //b();
        //c();
    }
};

class A
{
private:
    double *a;
public:
    A()
    {
        std::cout << "A()" << std::endl;
        a = new double[100];
    }

    ~A()
    {
        delete[] a;
        std::cout << "~A()" << std::endl;
    }
};

class B: public A
{
public:
    B()
    {
        std::cout << "B()" << std::endl;
    }

    ~B()
    {
        std::cout << "~B()" << std::endl;
    }
};

int main()
{
    Base base;
    base.a();
    //base.b();
    //base.c();

    Derived derived;
    //derived.a();
    //derived.b();
    //derived.c();

    Derived derived2;
    //derived2.a();
    //derived2.b();
    //derived2.c();

    std::cout << "C++11 Advanced and Modern Examples" << std::endl;
    move_semantics();
    literals();
    cplusplus11features();
    shared_pointers();
    weak_pointers();
    unique_pointers();
    resource_managing_class();
    constness();
    compiler_generated_functions();

    auto widgets = std::vector<Widget2>();
    widgets.push_back(getWidget2());

    auto widgetFactory = WidgetFactory();
    widgetFactory.addElement(getWidget2());

    std::string res;
    std::string temp("Message2");
    res.append("Message1");
    res.append("\r\n");
    res.append(temp);
    if (res.find(temp) == res.npos)
        res.append(temp);
    std::cout << res << std::endl;

    std::vector<SimpleStruct> structs;
    structs.push_back({1, 2.0, "str"});

    auto valid = ValidType();

    A *b = new B();
    delete b;

    return 0;
}
