//Point.cpp

//Purpose: source file for the Point class


#include "Point.hpp"


//Default constructor
Point::Point(): m_x(0.0), m_y(0.0){};

//Overloaded constructor
Point::Point(double newxval, double newyval): m_x(newxval), m_y(newyval){};

//Copy constructor
Point::Point(const Point& source):m_x(source.m_x), m_y(source.m_y){};

//Copy assignment operator
Point& Point::operator = (const Point& source)
{
//Assignment operator to avoid unnecessary copy of object
	if (this == &source)
    {
		return *this;			//Self-assignment
	}
	else
	{
		m_x = source.m_x;
		m_y = source.m_y;
    }
	return *this;				//Current object is returned
}

Point::Point(Point&& source)
{
    //Move the dynamic data
    m_x = std::move(source.m_x);
}

Point& Point::operator = (Point&& source)
{
    m_x = std::move(source.m_x);
    return *this;               //NOTE TO SELF: IMPORTANT to return *this -> a Point reference here...
}


//Destructor
Point::~Point(){};                                   

//GETTERS
//Same approach as with first course in C++

//Get X coordinate
const double& Point::X() const
{
    return m_x;
}                 

//Get Y coordinate
const double& Point::Y() const         
{
    return m_y;
}         

//MODIFIERS
//Setter functions to set new values of X
void Point::X(double newxval)
{
    m_x = newxval;
}              

//Setter functions to set new values of Y
void Point::Y(double newyval)
{
    m_y = newyval;
}

//Function ToString() to return string description of the point
std::string Point::ToString() const
{
    std::stringstream ss;
    ss << " Poiint(" << m_x << "," << m_y << ") ";
    return ss.str();                                //String retrieval from string buffer
}   

//Ostream operator overloading, to replace ToString()
std::ostream& operator << (std::ostream& os, const Point& source)
{
    os << source.ToString();                        //Seding to os stream
    return os;
}

//OPERATOR OVERLOADING


//Add coordinates
Point Point::operator + (const Point& source) const   
{
    return Point (m_x+source.m_x, m_y+source.m_y);
}


//Negate the coordinates
Point Point::operator - (const Point& source) const  
{
	return Point(-m_x, -m_y);
}

//Scale the coordinates
Point Point::operator * (double factor) const        
{
    return Point(m_x*factor, m_y*factor);
}


//Equally compare operator
bool Point::operator == (const Point& source)       
{
    //Returns boolean value
    return (m_x == source.m_x && m_y ==source.m_y);				
}

//Scale the coordinates and assignment
Point& Point::operator *= (double factor)             
{
    m_x *= (factor);
	m_y *= (factor);

	return *this;
}