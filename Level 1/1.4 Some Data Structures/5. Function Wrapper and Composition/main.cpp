//main.cpp

//Purpose: Function wrapper and Composition
/*
    Modify a class hierarchy containing polymorphic functions to a single class that uses a function wrapper. This is similar to exercise 4, except that we now have
    asingle class C that is composed of a function wrapper. No derived classes anymore, just instances of C.

    This design is a next-generation design pattern (to be described in more detail in Level 5) in the sense that 
    we do not need to create a class hierarchy in combination with (pure) virtual functions, in order to create 
    flexible software. In this particular case, we have a single class with one or more function wrappers as 
    members (composition again). They must be initialised in the class constructor, but they can be assigned 
    to another target method (function).

*/

//Author: Andrew Guerrand

//Modification date: 4/12/2023


#include <iostream>
#include <functional>
#include <cmath>


//Prototypical function wrapper
template <typename T>
using FunctionType = std::function<T (const T& t)>;


template <typename T>
class Shape
{
private:
    FunctionType<T> m_func; //Member function (note: 'private' here, rather than 'protected')
    T m_fac;                //Member factor that can be used within m_func when calling rotate() for example

public:

    //Constructor taking function wrapper and factor as arguments
    Shape(const FunctionType<T>& function, const T& factor) : m_fac(factor)
    {
        m_func = function;
    };

    //Rotate function calling member function/method stored and associated member factor 
    T rotate(double d) { return m_func(d) * m_fac; };

    //Setter function to modify member function method stored in 'private'
    void switchFunction(const FunctionType<T>& function)
    {
        m_func = function;
    };

};

int main()
{

// PART B): The below is pretty much the same implementation as what I provided in exercise 4 ...

    //Method 1 using lambda
    FunctionType<double> f1 = [](const double& d) -> double 
    {
        std::cout << "Method 1 of rotating for circle by: " << d << " rotations." << std::endl;
        return d;
    };

    //Create shape instance with arguments a function wrapper and a double (for m_fac)
    Shape<double> s1(f1, 3.2);
    s1.rotate(2.0);                 

    //Method 2 using lambda
    FunctionType<double> f2 = [](double d)-> double 
    {
        std::cout << "Method 2 of rotating for circle by: " << pow(d,2) << " rotations."<< std::endl;
        return pow(d,2);   
    };

    //Call switch function to change m_func in Shape class from f1 to f2
    s1.switchFunction(f2);
    s1.rotate(3.2);

    return 0;
}





