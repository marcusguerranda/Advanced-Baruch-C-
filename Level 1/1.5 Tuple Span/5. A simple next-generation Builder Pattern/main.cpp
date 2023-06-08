//main.cpp

//Purpose: 1.5.5) A simple next-generation builder pattern  --> Pattern called 'the Builder'
/*
    How to create and package objects that can be used when configuring an object. Create the application objects in a step-by-step
    fashion. Here, the objects will be contained in a tuple that clients can use at will.
    This is a major improvement on the traditional Builder pattern that does not provide a clear entry 
    point to the objects that clients need. 

    Goal: Create 2 seperate I/O devices classes that implement IOdevice differently, to showcase the utility in using 'the Builder'

    Benefit of this pattern: That one can mix and match shapes and display devices in a clean way.

    Create 2 concrete shapes, and 2 concrete I/O devices

    See useful information below too.
*/

//Author: Andrew Guerrand

//Modification date: 4/20/2023


//IMPORTANT: forward declare classes such as Circle, to get ride of CIRCULAR REFERENCE ISSUE.


#include "Builder1.hpp"
#include "Builder2.hpp"
#include "Builder3.hpp"
#include "Builder4.hpp"

#include "IODevice1.hpp"
#include "IODevice2.hpp"

#include "Director.hpp"

#include <iostream>
#include <memory>          //For the use of smart pointers

int main()
{
    //I need to use the functionalities for the different combinations of IODevices and Shapes (4 builders thus)
    //I will use Builder1 onwards up until Builder4


//BUILDER 1

    //Builder1 will build a Circle and use IODevice1
    std::cout << "\nBUILDER1!" << std::endl;
    Builder1 builder1;
    auto builderPtr1 = std::make_shared<Builder1>(builder1);
    Director director1(builderPtr1);

    //Call construct method of Director to create product
    auto product1 = director1.construct();

    //Extract the Shape and IODevice from the product tuple
    auto [shapePtr, ioDevicePtr] = product1;

    //Call the display method of the Shape using the IODevice for output
    shapePtr->display(*ioDevicePtr);


//BUILDER 2

    //Concrete builder for Circle objects and IODevice2
    std::cout << "\nBUILDER2!" << std::endl;
    Builder2 builder2;
    auto builderPtr2 = std::make_shared<Builder2>(builder2);
    Director director2(builderPtr2);

    //Call construct method of Director to create product
    auto product2 = director2.construct();

    //Extract the Shape and IODevice from the product tuple
    auto [shapePtr2, ioDevicePtr2] = product2;

    //Call the display method of the Shape using the IODevice for output
    shapePtr2->display(*ioDevicePtr2);


//BUILDER 3

    //Concrete builder for Line objects and IODevice1
    std::cout << "\nBUILDER3!" << std::endl;
    Builder3 builder3;
    auto builderPtr3 = std::make_shared<Builder3>(builder3);
    Director director3(builderPtr3);

    //Call construct method of Director to create product
    auto product3 = director3.construct();

    //Extract the Shape and IODevice from the product tuple
    auto [shapePtr3, ioDevicePtr3] = product3;

    //Call the display method of the Shape using the IODevice for output
    shapePtr3->display(*ioDevicePtr3);


//BUILDER 4

    //Concrete builder for Line objects and IODevice2
    std::cout << "\nBUILDER4!" << std::endl;
    Builder4 builder4;
    auto builderPtr4 = std::make_shared<Builder4>(builder4);
    Director director4(builderPtr4);

    //Call construct method of Director to create product
    auto product4 = director4.construct();

    //Extract the Shape and IODevice from the product tuple
    auto [shapePtr4, ioDevicePtr4] = product4;

    //Call the display method of the Shape using the IODevice for output
    shapePtr4->display(*ioDevicePtr4);

    return 0; 
};




/*
NOTES FOR MYSELF (from the forum)
a)
IODevice knows about Circle and Line and has only abstract functions, Then yes, derived classes must implement << 
(it is a nice way to do operator overloading). In practice circles and line will have io devices for console output, 
on a graphics screen, in a database etc. etc. So each specific output display device is a derived class with its own << stuff.

b) The Builder has two abstract functions (call F1, F2 for convenience) to create a Shape + iodevice. It also has a 
function Builder::F3 with body that create a tuple<ShapePtr, IoDevicePtr> by calling F1 and F2 in its body. So, your main just 
chooses a specific builder class and call the function F3 that return the typle you want.

So, it is not necessary for the Builder to have member data as all the objects are created _dynamically_ on the heap 
(using normal pointers or ideally smart pointers). There can be a whole hierarchy of builders also. e.g. console builders, Windows builders etc.


//This is a very useful piece of design in C++ and it offers great flexibility, i.e. all the I/O stuff is separated from core processing. 
IoDevice is similar to the Visitor pattern in QN C++ course.

A derived class of the Builder, say B1, will just be creating a very specific combination of Shape+IO Device, e.g. Circle+Graphics screen, so that if we want Circle+Graphics, 
we just create an object B1 my_b1, and calls my_b1.getProduct() in the main()

*/