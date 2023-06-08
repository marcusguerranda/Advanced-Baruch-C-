//Circle.hpp

//Purpose: Implementation of Circle class CAD shape, derived from abstract class Shape

//Author: Andrew Guerrand

//Modification dates: 4/25/2023

#ifndef Circle_hpp
#define Circle_hpp

#include "Shape.hpp"
#include <iostream>

class IODevice;

class Circle : public Shape
{
private:

    //This implementation reminds me of what was done in the first C++ course. However, I do not intend to create a Point class to generate the centerpoint
    //for the circle (with one double for the x-value and one other for the y-value. This is not the goal of this exercise). 
    //Instead, I assume, for simplicity, that the circle has a centerpoint with identical values for both x- and y- values.
    double m_centerpoint;
    double m_radius;


public:

    //Default constructor
    Circle(): m_centerpoint(2.0), m_radius(5.0)
    {
        std::cout << "\nOverloaded constructor in Circle class used." << std::endl;
    }

    //Destructor
    ~Circle()
    {
        std::cout << "Destructor in Circle class used.\n" << std::endl;
    }


    //Getter function for m_centerpoint and m_radius
    double const& getCenter() const
    {
        return m_centerpoint;
    }

    double const& getRadius() const
    {
        return m_radius;
    }

    //Display function overriding the pure virtual member function display() in abstract base class 'Shape'
    virtual void display(IODevice& ioDevice) const override
    {
        //Using << operator overloading, defined in both IODevice1.hpp and IODevice2.hpp
        ioDevice << *this; 
        //Note to self: 1. when dealing with pure virtual member functions in the base class, I do not need to specify 'override' in the derived classes' member functions
        //2. don't pass the IODevice by const reference, as passing the argument by *this disqualifies the const argument
    }

    //Note to self: setting the operator << function to friend is optional when within class
    friend std::ostream& operator << (std::ostream& os, const Circle& circle) 
    {
        os << "\nCircle object instance has centerpoint with coordinates: (" << circle.getCenter() << ", " << circle.getCenter() << "), and radius: "
        << circle.getRadius() << ". ";
        return os;
    }
};


#endif //Circle_hpp