//IODevice1.hpp

//Purpose: Derived class for IODevice1

//Author: Andrew Guerrand

//Modification date: 4/25/2023

#ifndef IODevice1_hpp
#define IODevice1_hpp

#include "IODevice.hpp"
#include "Circle.hpp"
#include "Line.hpp"


class IODevice1: public IODevice
{ // Interface for displaying CAD objects

public:
    
    virtual void operator << (const Circle& c) override
    {
        std::cout << "Using IODevice1." << c << std::endl;
    }

    virtual void operator << (const Line& l) override 
    {
        std::cout << "Using IODevice1." << l << std::endl;
    }
};

#endif //IODevice1_hpp