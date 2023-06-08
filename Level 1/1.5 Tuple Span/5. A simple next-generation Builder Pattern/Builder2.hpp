//Builder2.hpp

//Purpose: Concrete builder for Circle objects and IODevice2

//Author: Andrew Guerrand

//Modification dates: 4/25/2023


#ifndef Builder2_hpp
#define Builder2_hpp

#include "IODevice2.hpp"
#include "Builder.hpp"


class Builder2 : public Builder
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
        std::shared_ptr<IODevice2> IOD2_ptr(new IODevice2);
        return IOD2_ptr;
    }
};


#endif //Builderw_hpp