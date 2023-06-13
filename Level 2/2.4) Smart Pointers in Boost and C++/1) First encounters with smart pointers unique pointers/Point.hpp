//Point.hpp

//Purpose: class header file for 'Point' class

#ifndef Point_hpp
#define Point_hpp

//VERY IMPORTANT NOTE: technically I should have created a pure abstract class 'Shape' to ensure extensability of object classes other than 'Point' class
//                     This is not however the objective of the exercise, and therefore don't go into the absolute nitty-gritty of all proper best-practices.

#include <iostream>
#include <string>
#include <sstream>

class Point
{
private:

    double m_x;
    double m_y;

public:

//CONSTRUCTORS AND DESTRUCTOR
    Point();                                    //Default constructor
    Point(double newxval, double newyval);      //Overloaded constructor
    Point (const Point& source);                //Copy constructor
    Point& operator = (const Point& source);    //Copy assignment operator
    Point (Point&& source);                     //Move constructor
    Point& operator = (Point&& source);         //Move assignment operator
    ~Point();                                   //Destructor

//GETTERS
//Same approach as with first course in C++

    const double& X() const;                    //Get X coordinate
    const double& Y() const;                    //Get Y coordinate

//MODIFIERS

    void X(double newxval);                     //Setter functions to set new values of X and Y
    void Y(double newyval);

    std::string ToString() const;               //Function ToString() to return string description of the point
    friend std::ostream& operator << (std::ostream& os, const Point& source);   //Ostream operator overloading, to replace ToString()

//OPERATOR OVERLOADING

    Point operator + (const Point& source) const;   //Add coordinates
    Point operator - (const Point& source) const ;  //Negate the coordinates
    Point operator * (double factor) const;         //Scale the coordinates
    bool operator == (const Point& source);         //Equally compare operator
    Point& operator *= (double factor);             //Scale the coordinates and assignment
};



#endif //Point_hpp






/*  NOTE FOR SELF:

Difference in 'constness' within a function. Returning a const reference versus 'const' at the end, which essentially ensures the object is not modified when
calling said function.

double const& X(): This function returns a constant reference to a double value. 
It means that the caller of this function can access the value, but cannot modify it. 
The function itself does not modify the object on which it is called. The object itself may or may not be const-qualified.

double X() const: This function is a const member function, indicated by the const keyword at the end of the function declaration. 
It means that the function does not modify the object on which it is called. The function itself does not return a constant reference, 
but instead returns a copy of the double value. The object on which this function is called must be const-qualified.

ON ANOTHER NOTE: -> on the order of having 'const' in your function
Yes, you can write const double& X() instead of double const& X(). The order of const and the type (double) in a function declaration doesn't matter. 
Both forms are equivalent and indicate that the return type is a reference to a constant double.

In C++, the placement of const before or after the type is a matter of personal preference or coding style. 
It doesn't affect the semantics or behavior of the function. You can use either const double& or double const& to declare a 
reference to a constant double, and both forms are widely used in codebases. Choose the style that you find more readable and consistent 
with your codebase or coding guidelines.


*/