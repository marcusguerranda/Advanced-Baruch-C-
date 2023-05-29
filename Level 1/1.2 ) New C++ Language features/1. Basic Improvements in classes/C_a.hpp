//C_a.hpp 

//1.2.1 New C++ Language Features ("Improving your classes")
//1. Basic Improvement in classes
//Subquestion a 

//Author: Andrew Guerrand

//Purpose: Controlling for default creation of certain special member functions, using move semantics and rvalue references, and
//         creating move constructor and move operator

//Modification date: 4/6/2023


#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>


#ifndef C_a_hpp
#define C_a_hpp

template <typename T>
class C_a
{
private:

    std::vector<T> m_vector;

    //Copy constructor, to prevent copying of objects of C_a class (known as "disabling copying semantics")
    //Compiler will generate an error if someone tries to copy or assign objects of the C_a class
    C_a(const C_a& source) = delete;

    //Assignment operator, to prevent assigning of objects of C_a class 
    C_a<T>& operator = (const C_a& source) = delete;

public:

//CONSTRUCTORS AND DESTRUCTOR

    //Default constructor, making it default below (I could have also alternatively, defined it as: C(){}; without arguments)
    // C_a(){std::cout << "Default constructor in C class has been used." << std::endl;};    
    C_a() = default;    

    //Overloaded constructor, taking vector as argument
    C_a(const std::vector<T>& source);  

    //Destructor
    ~C_a();                      

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


#ifndef C_a_cpp
#include "C_a.cpp"
#endif              //C_a_cpp


#endif              //C_a_hpp


