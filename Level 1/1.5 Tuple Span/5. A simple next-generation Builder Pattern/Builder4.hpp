//Builder4.hpp

//Purpose: Concrete builder for Line objects and IODevice2

//Author: Andrew Guerrand

//Modification dates: 4/25/2023


#ifndef Builder4_hpp
#define Builder4_hpp

#include "IODevice2.hpp"
#include "Builder.hpp"


class Line;
class IODevice2;

class Builder4 : public Builder
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
        std::shared_ptr<IODevice2> IOD2_ptr(new IODevice2);
        return IOD2_ptr;
    }
};



#endif //Builder4_hpp