//Main.cpp

//Purpose:  - Reduce functions with a given arity to functions with a lower arity
//          - Getting used to std::bind
//          - Placeholders in conjunction with the test function

//Author: Andrew Guerrand

//Modification date: 4/10/2023

#include <iostream>
#include <functional>


//Source: https://www.geeksforgeeks.org/bind-function-placeholders-c/

//Test function 
//Arity of 3
double freeFunction3(double x, double y, double z)
{
    return x+y+z;
}

/*
FIRST APPROACH FOR PART A

I could also, alternatively, use:

using namespace std::placeholders, so that I don't have to repeat std::placeholders every time.

//Arity 2
double freeFunction2(double y, double z)
{
    auto f = std::bind(&freeFunction3, std::placeholders::_1, y, z);
    return f(1.0);
}

//Arity 1
double freeFunction1(double z)
{
    auto f = std::bind(&freeFunction2, std::placeholders::_1, z);
    return f(2.0);
}

//Arity 0
double freeFunction0()
{
    auto f = std::bind(&freeFunction1, 3.0);
    return f();
}

*/


int main()
{

//PART A:

    //Using placeholders to reduce the arity of the function
    auto freeFunction2 = std::bind(freeFunction3, std::placeholders::_1, std::placeholders::_2, 4.44);
    auto freeFunction1 = std::bind(freeFunction3, std::placeholders::_1, 2.22, 4.44);
    auto freeFunction0 = std::bind(freeFunction3, 1.0, 2.22, 4.44);

    //Testing the reduced-arity functions
    std::cout << "Reduced arity function with 2 parameters: " << freeFunction2(1.11, 3.33) << std::endl;
    std::cout << "Reduced arity function with 1 parameter: " << freeFunction1(1.11) << std::endl;
    std::cout << "Reduced arity function with 0 parameters: " << freeFunction0() << std::endl;

//Remark: the output is correct.

    return 0;
}