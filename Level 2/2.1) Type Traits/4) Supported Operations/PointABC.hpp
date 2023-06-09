//PointABC.hpp

//Purpose: Derived class of Shape class, for questions A, B, and C


#include "Shape.hpp"

class PointABC : public Shape
{
public:

    PointABC(){};
    virtual void draw() override{};   //Polymorphic function guaranteeing overriding from method in abstract base class 'Shape'

    //No need to define the copy constructor and copy assignment operator. These are implicitly created if not defined (unless using 'delete')
    //I will use 'delete in 'PointDE' class to see the effects of not having these when using <type_trait> functionalities/answering question D
};