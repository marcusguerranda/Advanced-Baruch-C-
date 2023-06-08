//Builder.hpp

//Purpose: Builder abstract class which will call different functions overriden by derived builder classes.
//         I will have 4 CONCRETE builder classes: that is because we have a combination of 2 shapes and 2 IODevices, and thus 4 tuple combinations possible

//Author: Andrew Guerrand

//Modification dates; 4/25/2023


#ifndef Builder_hpp     //Guards
#define Builder_hpp

#include <tuple>        //Tuple header file
#include <memory>       //Header file for the use of smart pointers (and thus shared_ptr's)
#include "Circle.hpp"    
#include "Line.hpp"
#include "IODevice.hpp" //IODevice abstract file

using ShapePointer = std::shared_ptr<Shape>;
using IODevicePointer = std::shared_ptr<IODevice>;


class Builder
{ // A Builder hierarchy that builds shapes and io devices
    public:

    //In the case of the 'Builder'pattern, having a pure virtual destructor in the base class ensures that all 
    //derived classes have a destructor that can be called when an object is deleted through a pointer to the base class. 
    virtual ~Builder() = default;

    //IMPORTANT: I could have potentially made this function a PVMF and defined it in each builder, but the code given did not infer such a process
    //           TEMPLATE METHOD PATTERN!
    std::tuple<ShapePointer, IODevicePointer> getProduct()
    {   
        //Make a tuple of the relevant shared pointers to derived shape class instance and IODevice derived instance
        std::tuple<ShapePointer, IODevicePointer> tuple_Product{std::make_tuple(getShape(), getIODevice())};
        return tuple_Product;
    }

    // Hook functions that derived classes must implement
    virtual ShapePointer getShape() = 0;
    virtual IODevicePointer getIODevice() = 0;
};

#endif  //Builder_hpp