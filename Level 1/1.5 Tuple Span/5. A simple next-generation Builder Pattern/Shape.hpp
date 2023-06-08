//Shape.hpp

//Purpose: Defining the abstract base class Shape

//Author: Andrew Guerrand

//Modification dates: 4/25/2023


#ifndef Shape_hpp
#define Shape_hpp

#include <string>
#include <sstream>
#include <iostream>


//Forward declaration to avoid circular dependency
class IODevice;

// Class hierarchy
class Shape
{
public:

    //PVFM display() function, to display information on whichever CAD shape the function is called upon from IODevice or another.
    virtual void display(IODevice& ioDevice) const = 0;
};


#endif //Shape_hpp