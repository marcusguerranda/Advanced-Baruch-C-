//C_a.cpp source file


#include "C_a.hpp"

#ifndef C_a_cpp
#define C_a_cpp


//CONSTRUCTORS AND DESTRUCTOR

    //Default constructor was defined as "default"

    //Overloaded constructor, taking vector as argument
    template<typename T>
    C_a<T>::C_a(const std::vector<T>& source): m_vector(source)                   
    {
        std::cout << "Overloaded constructor in C class has been used." << std::endl;
    };  
 
    //Destructor
    template<typename T>
    C_a<T>::~C_a() {std::cout << "Destructor in C class has been used." << std::endl;};                      


//GETTERS

    //Getter function for member vector variable within C class
    template<typename T>
    std::vector<T> const& C_a<T>::getVector() const 
    { 
        //std::cout << "Get vector function in C class has been used." << std::endl;
        return m_vector;
    };
    

//SETTERS

    //Modifier function for member vector variable within C class
    template<typename T>
    void C_a<T>::setVector(std::vector<T> newvector)
    {
        m_vector = newvector;
        //std::cout << "Set vector function in C class has been used." << std::endl;
    };


    //Scale function to multiply each element within the member vector by a scalar. The proposed approach in the exercise was to simply use 
    //a factor of 2, but I brought this to a more abstract implementation by requesting a scalar.
    template<typename T>
    void C_a<T>::scale(const double& factor)
    {
        //This requires the same kind of implementation required in 1.1 exercises, on the multiplication of vector elements by a scalar.
        //I could be using std::multiplies, std::for_each, or std::transform. Here, I simply use std::for_each
        std::for_each(m_vector.begin(), m_vector.end(), [factor](T& element){element *= factor;});
    };

//OTHER MEMBER FUNCTIONS

    //Print function to print elements within a vector
    template<typename T>
    void C_a<T>::print()
    {
        std::cout << "Print function in C class is now used" << std::endl;
        for(const T& element: m_vector) //Range-based for-loop
        {
            std::cout << element << ", " << std::endl;
        }
    };


#endif //C_a_cpp



/*
NOTE TO SELF:

if you mark your copy constructor and assignment operator as " = delete" in the header file and they are defined in the private section, 
there is no need to define them in the source file.

In fact, marking them as " = delete" explicitly tells the compiler to generate an error if someone tries to use them, so it's important 
that they are not defined anywhere else. 
*/
