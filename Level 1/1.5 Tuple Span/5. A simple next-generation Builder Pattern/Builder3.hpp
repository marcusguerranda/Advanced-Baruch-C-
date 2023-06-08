//Builder3.hpp

//Purpose: Concrete builder for Line objects and IODevice1

//Author: Andrew Guerrand

//Modification dates: 4/25/2023


#ifndef Builder3_hpp
#define Builder3_hpp

#include "IODevice1.hpp"
#include "Builder.hpp"


class Line;
class IODevice1;

class Builder3 : public Builder
{
public:
    // Hook functions that derived classes must implement
    //I keep the 'virtual' (although I know it is optional) to be granular in the properties of each function
    virtual ShapePointer getShape()
    {
        std::shared_ptr<Line> line_ptr(new Line);
        return line_ptr;
    }

    virtual IODevicePointer getIODevice()
    {
        std::shared_ptr<IODevice1> IOD1_ptr(new IODevice1);
        return IOD1_ptr;
    }
};



#endif //Builder3_hpp