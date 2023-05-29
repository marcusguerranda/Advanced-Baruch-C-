//C.hpp 

//1.2.1 New C++ Language Features ("Improving your classes")
//Prior to starting exercise

//Author: Andrew Guerrand

//Purpose: Controlling for default creation of certain special member functions, using move semantics and rvalue references, and
//         creating move constructor and move operator

//Modification date: 4/6/2023


#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>


#ifndef C_hpp
#define C_hpp

template <typename T>
class C
{
private:

    std::vector<T> m_vector;

public:

//CONSTRUCTORS AND DESTRUCTOR

    //Default constructor
    C();    

    //Overloaded constructor, taking vector as argument
    C(const std::vector<T>& source);  

    //Copy constructor, taking C instance as argument
    C(const C& source);

    //Assignment operator
    C& operator = (const C& source);

    //Destructor
    ~C();                      


//GETTERS

    //Getter function for member vector variable within C class
    std::vector<T> const& getVector() const;

//SETTERS

    //Modifier function for member vector variable within C class
    void setVector(std::vector<T> newvector);

    //Scale function to multiply each element within the member vector by a scalar. The proposed approach in the exercise was to simply use 
    //a factor of 2, but I brought this to a more abstract implementation by requesting a scalar.
    void scale(const double& factor);

//OTHER MEMBER FUNCTIONS

    //Print function to print elements within a vector
    void print();
};



#endif //C_hpp

#ifndef C_cpp   
#include "C.cpp"    
#endif              //C_cpp
