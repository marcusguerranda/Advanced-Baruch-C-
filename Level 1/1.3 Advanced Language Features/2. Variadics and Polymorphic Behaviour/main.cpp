//main.cpp

//Purpose: Using variadics to call polymporhic and non-polymorphic functions on a fixed set of objects

//Author: Andrew Guerrand

//Modification date: 4/10/2023

#include <iostream>
#include <array>

//Related classe hierarchy that has a pure virtual member rotate functions and polymorphic behavior.
class Shape
{
    public:
    virtual void rotate(double d) = 0;
};

class Circle : public Shape
{
    public:
    void rotate(double d) override { std::cout << "c\n"; }
};

class Line : public Shape
{
    public:
    void rotate(double d) override { std::cout << "l\n"; }
};


//Unrelated class that also has a rotate member function
class Valve
{
    public:
    void rotate(double d) { std::cout << "v\n"; }
};


//Tail function for rotate() variadic template function taking different objects, who all have, as a member function, rotate()
void rotate(const double& factor)
{
    std::cout << "Tail function of variadic template function rotate() called." << std::endl;
}

template <typename Object, typename ... Objects>
void rotate(const double& factor, Object object, Objects ... other_objects)
{
    object.rotate(factor);                  //Calling rotate() function for first instance 'object'
    rotate(factor, other_objects...);     //Recursively calling rotate() function for the remaining objects
   
/*
Explicitly, this is what the variadic function does:

    if constexpr (sizeof...(other_objects) > 0) 
    {
    rotate(factor, other_objects...);   //Recursively call rotate for the remaining objects
    } else 
    {
        rotate();                           //Call the tail function when the parameter pack is empty
    }

*/
}


int main()
{
//PART A:

    Circle circle;
    Line line;
    Valve valve;
    double factor = 2.0;

//We can in essence create compile-time aggregates/wholepart objects on the fly. We only need to write one function.
    rotate(factor, circle);
    rotate(factor, circle, line);
    rotate(factor, circle, valve);
    rotate(factor*2, circle, valve, line);


//Alternative approach:
    // The other way of doing it.
    std::array<Shape*, 5> shapeList{ &circle, &line, &circle, &circle, &line };
    double factor2 = 20.0;
    for (auto& elem : shapeList)
    {
        elem->rotate(factor2);
    }

//PART B: Why can we not include valves in this array? And why can we include valves in the variadic approach?
/*
The answer is quite straightforward. In our array, we explicitly create an array of 5 pointers to instances derived from base class 'Shape'.
Therefore, when calling rotate(), Valve is not a derived class from Shape, and thus we cannot both call rotate() in Valve while using Shape objects.

When using the variadic function, the rotate function takes any object that has for member function rotate(). And since the Valve class has rotate(),
then it can be alled.

In essence, the array takes for parameter the type of the objects (here of base class Shape), while variadic functions are not stringent, and take 
any objects/instances as long there is a defined rotate() function in their object definition.

*/

    return 0;
}