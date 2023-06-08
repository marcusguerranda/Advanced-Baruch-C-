//IODevice.hpp

//Purpose: Abstract base class for IODevice classes

//Author: Andrew Guerrand

//Modification date: 4/25/2023

#ifndef IODevice_hpp
#define IODevice_hpp


class Shape;
class Line;   //Forward declaration to avoid circular dependencies
class Circle;

class IODevice
{ // Interface for displaying CAD objects

public:

    virtual void operator << (const Circle& c) = 0;
    virtual void operator << (const Line& c) = 0;

};

#endif //IODevice_hpp