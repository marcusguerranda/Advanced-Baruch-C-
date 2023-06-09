//PointE.hpp

//Purpose: Derived class of Shape class for questions D and E


#include "Shape.hpp"

class PointE : public Shape
{
public:

    PointE(){};
    virtual void draw() override{};                     //Polymorphic function guaranteeing overriding from method in abstract base class 'Shape'
    
    PointE(const PointE&) = delete;                     //Deleting copy constructor
    PointE& operator = (const PointE&) = delete;        //Deleting copy assignment operator

    //Note: YOU CANNOT USE CONST IN MOVE constructors and assignment operators. It's an rvalue...!
    PointE( PointE&&) = default;                   //Move constructor
    PointE& operator = ( PointE&&) = default;      //Move assignment operator
};