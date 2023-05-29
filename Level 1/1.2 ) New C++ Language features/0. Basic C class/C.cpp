//C.cpp

#ifndef C_cpp
#define C_cpp

#include "C.hpp"


//CONSTRUCTORS AND DESTRUCTOR

    //Default constructor    
    template <typename T>
    C<T>::C(){std::cout << "Default constructor in C class has been used." << std::endl;};    

    //Overloaded constructor, taking vector as argument
    template<typename T>
    C<T>::C(const std::vector<T>& source): m_vector(source)                   
    {
        std::cout << "Overloaded constructor in C class has been used." << std::endl;
    };  

    //Copy constructor, taking C instance as argument
    template<typename T>
    C<T>::C(const C& source): m_vector(source.m_vector)                                       
    {
        std::cout << "Copy constructor in C class has been used." << std::endl;
    };

    //Assignment operator
    template <typename T>
    C<T>& C<T>::operator = (const C& source)
    {
        m_vector = source.m_vector;
        std::cout << "Assignment operator in C class has been used." << std::endl;
        return *this;
    };

    //Destructor
    template <typename T>
    C<T>::~C() {std::cout << "Destructor in C class has been used." << std::endl;};                      


//GETTERS

    //Getter function for member vector variable within C class
    template<typename T>
    std::vector<T> const& C<T>::getVector() const 
    { 

    //std::cout << "Get vector function in C class has been used." << std::endl;
        return m_vector;
    };
    

//SETTERS

    //Modifier function for member vector variable within C class
    template<typename T>
    void C<T>::setVector(std::vector<T> newvector)
    {
        m_vector = newvector;
        //std::cout << "Set vector function in C class has been used." << std::endl;
    };


    //Scale function to multiply each element within the member vector by a scalar. The proposed approach in the exercise was to simply use 
    //a factor of 2, but I brought this to a more abstract implementation by requesting a scalar.
    template<typename T>
    void C<T>::scale(const double& factor)
    {
        //This requires the same kind of implementation required in 1.1 exercises, on the multiplication of vector elements by a scalar.
        //I could be using std::multiplies, std::for_each, or std::transform. Here, I simply use std::for_each
        std::for_each(m_vector.begin(), m_vector.end(), [factor](T& element){element *= factor;});
    };

//OTHER MEMBER FUNCTIONS

    //Print function to print elements within a vector
    template<typename T>
    void C<T>::print()
    {
        std::cout << "Print function in C class is now used" << std::endl;
        for(const T& element: m_vector) //Range-based for-loop
        {
            std::cout << element << ", " << std::endl;
        }
    };

#endif

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
//main.hpp 

//1.2.1 New C++ Language Features ("Improving your classes")
//1. Basic Improvement in classes
//Author: Andrew Guerrand

//Purpose: Controlling for default creation of certain special member functions, using move semantics and rvalue references, and
//         creating move constructor and move operator

//Modification date: 4/6/2023


#include "C.hpp"   //Header file for the default class implementation at the beginning of the exercise


int main()
{

//Testing C class 

    C<int> c1;                              //Default constructor summoned

    std::vector<int> vector1 = {1,2,3,4,5};
    C<int> c2(vector1);                     //Using overloaded constructor

    C<int>c3(c2);                           //Using copy constructor to create and instantiate c3 instance
    
    c1.print();                             //Printing contents of c1 (will contain nothing, as expected), c2, and c3
    c2.print();
    c3.print();


    std::vector<int> storage = c3.getVector();  //Using getter vector function
    c3.setVector(std::vector<int>{2,4,6,8,10}); //Using setter vector function

    c3.print();                                                                     //Print new c3 vector that was altered by setter function
    for(const auto& elem: storage){std::cout << elem << ", " <<std::endl;};         //Print old c3 vector that was stored (using range-based for-loop)
    c3 = c2;                                                                        //Using assignment operator

    c3.print();                                                                     //Reusing print function.

    //Using scale function, using integer scalar 3
    c3.scale(3);    
    c3.print();

  return 0;  
};
