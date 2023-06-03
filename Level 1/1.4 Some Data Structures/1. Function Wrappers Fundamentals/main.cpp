//main.cpp

//Purpose:

//Author: Andrew Guerrand

//Modification date: 4/10/2023

#include <iostream>
#include <functional>       //To use std::function


//Using 'double' as data type for convenience! (ref. exercise 1.4.1)

//FunctionType as alias template, taking const reference as argument of type T, and with an output of type T.
template <typename T>                        
using FunctionType = std::function<T(const T&)>;

//Print function taking as argument functon type, and argument to plug into said-function
template <typename T>                       
void print(const FunctionType<T>& f, T t)
{
    std::cout << f(t) << '\n';
}

//Defining free function that multiplies a number by a scalar
double Function_Free(const double& scalar)
{
    std::cout << "Free function used." << std::endl;
    return scalar* 11.11;
}

struct Function_Object
{
    double operator()(const double& scalar) const
    {
        std::cout << "Function object used." << std::endl;
        return scalar* 11.11;
    }
};



int main()
{
    //Stored lambda function
    auto stored_lambda = [](const double& scalar) -> double 
    {
        std::cout<<"Lambda used."<<std::endl; 
        return scalar* 11.11;
    };

    //Instance of a function wrapper created using alias template FunctionType for a generic function
    FunctionType<double> f; 

    //Assign function wrapper to free function
    f = Function_Free;
    print(f, 10.0);

    //Assign function wrapper to function object
    Function_Object fo;
    f = fo;
    print(f, 10.0);

    //Assign function wrapper to stored lambda
    f = stored_lambda;
    print(f, 10.0);

    
    return 0;
}