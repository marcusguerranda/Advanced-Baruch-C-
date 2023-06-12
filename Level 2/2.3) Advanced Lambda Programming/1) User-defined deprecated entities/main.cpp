//2.3.1: Advanced Lambda programming

//Purpose: Marking a range of entities as being deprecated to use them in code. Mark the following as being deprecated and testing your code:
/*
    a) Free/global functions.
    b) Deprecated class and non-deprecated class with deprecated member function.
    c) Deprecated global variable.
    d) Deprecated enum and deprecated enum class.
    e) Deprecated template class specialisation.
    f) Deprecated lambda function
*/

#include <iostream>


//Deprecated global/ free function 
[[deprecated("Deprecated function")]] 
double Summation (double a, double b) {return a +b;}


//Deprecated class 
[[deprecated("Deprecated class")]] 
class deprecated_Class{};


//Non-deprecated class with deprecated member function
class nondeprecated_Class
{
public:
    [[deprecated("Deprecated member function in non-deprecated class")]]
    void Printer(){};
};


//Deprecated global variable
[[deprecated("Deprecated global variable")]] 
int global_var = 1111;


//Deprecated enum and deprecated enum class
[[deprecated("Deprecated enum")]] 
enum ENUM {BLUE,RED,YELLOW};

[[deprecated("Deprecated enum class")]]
enum class ENUMCLASS {BLUE,RED,YELLOW};


//Deprecated template class specialization
template<typename T>[[deprecated("Deprecated template class specialization")]]
class deprecatedClassSpecialization{};

//Deprecated lambda function
[[deprecated("Deprecated lambda function")]]
auto f = [](){ return 111;};

int main()
{
    double a, b = 10.0;

    //Deprecated global/ free function 
    Summation(a,b);

    //Deprecated class 
    deprecated_Class c1;

    //Deprecated global variable
    std::cout << global_var << std::endl;

    //Non-deprecated class with deprecated member function Printer
    nondeprecated_Class c2;
    c2.nondeprecated_Class::Printer();

    //Deprecated enum
    ENUM enum1 = BLUE;

    //Deprecated enum class
    ENUMCLASS enum2;
    enum2 = ENUMCLASS::BLUE;

    //Deprecated template class specialization
    deprecatedClassSpecialization<double> c3;

    //Deprecated lambda function
    std::cout << f << std::endl;

    return 0;
}



/*  Note for self:

Difference between global and free functions?

In C++, there is no difference between a free function and a global function - both refer to a function that is defined outside of a class 
or namespace. The term "global function" can be used to refer to any function that is declared in the global namespace, regardless of whether it is 
free or a member of a class. On the other hand, "free function" specifically refers to a function that is not a member of a class.

*/