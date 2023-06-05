//main.cpp

//Purpose: Function wrapper and Inheritance. Instead of a public pure virtual member function, we define a protected function wrapper in the base class
//         which will be implemented in derived classes.

//Author: Andrew Guerrand

//Modification date: 4/11/2023


/*Note to self: 
Comments by Avi:"You aren't creating a function wrapper 'as' or 'to' a pure virtual function. Rather, as mentioned above, it's an 
independent design technique that emulates a pure virtual function (in that they can only be called on the derived classes), but 
not actually using pure virtual functions."


"The public rotate() function should simply invoke the function wrapper that was saved down as part of the object construction."
*/


#include <iostream>
#include <functional>
#include <cmath>

//Function wrapper
using voidFunctionType = std::function<void(double)>;

// Class hierarchy
class Shape
{
//Emulate pure virtual functions by replacing them with an instance of VoidFunctionType as a protected data member in the base class
protected:
    voidFunctionType f;

public:

    Shape() = delete;

    //Constructor in base class
    Shape(const voidFunctionType& source_func)
    {
        f = source_func;
        std::cout << "Shape class constructor used." << std::endl;
    };

    void rotate(double d) 
    { 
        f(d);   //Calling protected rotate method in base class 'Shape', to emulate pure virtual functions
    };
};


//Derived class Circle from base class Shape
class Circle : public Shape
{
public:

    Circle() = delete;

    //Constructor in derived constructor, and requires a method to be built
    Circle(const voidFunctionType& source_func): Shape(source_func)
    {
        std::cout << "Circle class constructor used." << std::endl;
    };

    //Setter function to modify method in base class, and 'protected'
    void setRotateFunction(const voidFunctionType& source_func)
    {
        f = source_func;
    };

};


int main()
{
    voidFunctionType f1= [](const double& d){std::cout << "Method 1 of rotating for circle by: " << d << " rotations." << std::endl;};
    Circle c1(f1); 
    c1.rotate(3.2);

    //Assigning another function c1's method
    voidFunctionType f2 = [](double d){std::cout << "Method 2 of rotating for circle by: " << pow(d,2) << " rotations."<< std::endl;};
    c1.setRotateFunction(f2);
    c1.rotate(3.2);

    return 0;
}















//NOTE TO SELF:
/*
what is the purpose of having a protected function wrapper in Shape class?

The purpose of having a protected function wrapper in the Shape class is to provide a way for the derived classes to implement 
the functionality of the original pure virtual function rotate(double) in a flexible and customizable way.

By defining a function wrapper as a protected member of the Shape class, the derived classes can access and modify it to 
customize the behavior of the rotate function. The rotate function in the base class can then simply call the function wrapper, 
which in turn calls the overridden rotate function in the derived class.

This approach allows for more flexibility in the design of the class hierarchy since the behavior of the rotate function can be 
customized independently in each derived class, without changing the interface of the base class.





*/