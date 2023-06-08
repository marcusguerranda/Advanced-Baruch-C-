//Builder1.hpp

//Purpose: Concrete builder for Circle objects and IODevice1

//Author: Andrew Guerrand

//Modification dates: 4/25/2023


#ifndef Builder1_hpp
#define Builder1_hpp

#include "IODevice1.hpp"    //IODevice1 header file
#include "Builder.hpp"      //Builder abstract class


class Builder1 : public Builder
{
public:
    // Hook functions that derived classes must implement
    //I keep the 'virtual' (although I know it is optional) to be granular in the properties of each function

    //Getter function for Builder1 class shape object
    virtual ShapePointer getShape()
    {
        std::shared_ptr<Circle> circle_ptr (new Circle);
        return circle_ptr;
    }

    //Getter function for Builder1 class IODevice object
    virtual IODevicePointer getIODevice()
    {
        std::shared_ptr<IODevice1> IOD1_ptr(new IODevice1);
        return IOD1_ptr;
    }
};



#endif //Builder1_hpp