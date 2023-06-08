//Line.hpp

//Purpose: Implementation of Line class CAD shape, derived from abstract class Shape

//Author: Andrew Guerrand

//Modification dates: 4/25/2023



#ifndef Line_hpp
#define Line_hpp

#include "Shape.hpp"
#include "IODevice.hpp"
#include <sstream>

class Line : public Shape
{
private:

    //I do not intend to create a Point class to generate any point coordinates.
    //for the line (with one double for the x-value and one other for the y-value. This is not the goal of this exercise). 
    //Instead, I assume that the line has two points, where each points has identical values for both x- and y- values.

    double m_point1;
    double m_point2;


public:

    //Default constructor
    Line(): m_point1(4.0), m_point2(6.0)
    {
        std::cout << "\nOverloaded constructor in Line class used." << std::endl;
    }

    //Destructor
    ~Line()
    {
        std::cout << "Destructor in Line class used.\n" << std::endl;
    }

    
    virtual void display(IODevice& ioDevice) const 
    {
        //Using << operator overloading, defined in both IODevice1.hpp and IODevice2.hpp
        ioDevice << *this; 
        //Note to self: don't pass the IODevice by const reference, as passing the argument by *this disqualified the const argument
    }

    //Note to self: setting the operator << function to friend is optional when within class
    friend std::ostream& operator << (std::ostream& os, const Line& line) 
    {
        os << "Line object instance has first point with coordinates: (" 
           << line.getPoint1() << ", " << line.getPoint1() 
           << "), and second point with coordinates: (" << line.getPoint2() 
           << ", " << line.getPoint2() << ").";
        return os;
    }


    //Getter function for the two points of Line instance
    double const& getPoint1() const 
    {
        return m_point1;
    }

    double const& getPoint2() const 
    {
        return m_point2;
    }
};



#endif //Line_hpp