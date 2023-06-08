//IODevice2.hpp

//Purpose: Derived class for IODevice2

//Author: Andrew Guerrand

//Modification date: 4/25/2023

#ifndef IODevice2_hpp
#define IODevice2_hpp

#include "IODevice.hpp"
#include "Circle.hpp"
#include "Line.hpp"


class IODevice2: public IODevice
{ // Interface for displaying CAD objects

public:

    virtual void operator << (const Circle& c) override 
    {
        std::cout << "Using IODevice2." << c << std::endl;
    }

    virtual void operator << (const Line& l) override 
    {
        std::cout << "Using IODevice2." << l << std::endl;
    }
};

#endif //IODevice2_hpp