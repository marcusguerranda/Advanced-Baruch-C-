//Shape.hpp

//Abstract base class


//Note to self: #pragma once not supported by all compilers, but #ifndef guards are a standard way to avoid multiple inclusion.
//I'll stick to #ifndef guards as I hav in the past.

#ifndef Shape_hpp
#define Shape_hpp

class Shape
{
public:
    //Does not make sense to instantiate an instance of Shape abstract class
    //Shape() = default;

    //Pure virtual member function, making this an abstract base class
    virtual void draw() =0; 
};



#endif //Shape_hpp