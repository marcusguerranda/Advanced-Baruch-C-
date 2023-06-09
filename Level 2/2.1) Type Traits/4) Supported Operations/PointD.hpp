//PointD.hpp

//Purpose: Derived class of Shape class for questions D and E


#include "Shape.hpp"

class PointD : public Shape
{
public:

    PointD(){};
    virtual void draw() override{};                     //Polymorphic function guaranteeing overriding from method in abstract base class 'Shape'
    
    PointD(const PointD&) = delete;                     //Deleting copy constructor
    PointD operator = (const PointD&) = delete;         //Deleting copy assignment operator
};