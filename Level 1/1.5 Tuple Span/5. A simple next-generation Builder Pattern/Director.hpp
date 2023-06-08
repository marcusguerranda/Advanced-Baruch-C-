//Director.hpp

//Purpose: The purpose of the Director in the Builder pattern is to encapsulate the steps involved in constructing a complex object using the Builder. 
//      The Director provides a higher-level interface to the client code, which allows it to construct complex objects without knowing the details of the 
//      construction process.
//      In other words, the Director defines the sequence of steps needed to build an object, while the Builder provides the implementation of those steps. 

//Author: Andrew Guerrand

//Modification dates: 4/25/2023

#ifndef Director_hpp
#define Director_hpp

#include <memory>
#include "Builder.hpp"

class Director
{
private:
    
    std::shared_ptr<Builder> m_builder;

public:
    Director(std::shared_ptr<Builder> builder): m_builder(builder){};

    void setBuilder(std::shared_ptr<Builder> builder)
    {
        m_builder = builder;
    }

    std::tuple<ShapePointer, IODevicePointer> construct()
    {
        //Call the hook functions of the builder to build the product
        ShapePointer shape = m_builder->getShape();
        IODevicePointer ioDevice = m_builder->getIODevice();

        //Return the product as a tuple
        return std::make_tuple(shape, ioDevice);
    }
};

#endif //Director_hpp