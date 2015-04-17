#include<iostream>

#include "move_semantics.h"
#include "literals.h"
#include "compiler_generated_functions.h"
#include "cplusplus11features.h"
#include "smart_pointers.h"

using namespace SMART_POINTERS;

int main()
{
    std::cout << "C++11 Advanced and Modern Examples" << std::endl;
    move_semantics();
    literals();
    cplusplus11features();
    shared_pointers();
    weak_pointers();
    unique_pointers();

    return 0;
}
