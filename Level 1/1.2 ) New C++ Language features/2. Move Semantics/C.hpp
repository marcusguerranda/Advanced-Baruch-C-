//C.hpp 

//1.2.1 New C++ Language Features ("Improving your classes")
//2. Move Semantics 


//Author: Andrew Guerrand

//Purpose: Controlling for default creation of certain special member functions, using move semantics and rvalue references, and
//         creating move constructor and move operator

//Modification date: 4/7/2023


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

    //Default constructor (explicit is optional here, as there is nothing that the constructor does that can be known at compile-time specifically)
    constexpr C() noexcept: m_vector({}) {std::cout << "Default constructor in C class has been used." << std::endl;};    
 

    //Overloaded constructor, taking vector as argument
    explicit constexpr C(const std::vector<T>& source) noexcept: m_vector(source)                   
    {
        std::cout << "Overloaded constructor in C class has been used." << std::endl;
    };  

    //Copy constructor, taking C instance as argument
    constexpr C(const C& source) noexcept: m_vector(source.m_vector)                                       
    {
        std::cout << "Copy constructor in C class has been used." << std::endl;
    };

    //Assignment operator
    C& operator = (const C& source) noexcept;

    //Destructor
    ~C() noexcept;                      


//GETTERS

    //Getter function for member vector variable within C class
    constexpr std::vector<T> const& getVector() const noexcept
    { 
        //std::cout << "Get vector function in C class has been used." << std::endl;
        return m_vector;
    };
    

//SETTERS

    //Modifier function for member vector variable within C class
    constexpr void setVector(std::vector<T> newvector) noexcept
    {
        m_vector = newvector;
        //std::cout << "Set vector function in C class has been used." << std::endl;
    };


    //Scale function to multiply each element within the member vector by a scalar. The proposed approach in the exercise was to simply use 
    //a factor of 2, but I brought this to a more abstract implementation by requesting a scalar.
    constexpr void scale(const double& factor) noexcept
    {
        std::for_each(m_vector.begin(), m_vector.end(), [factor](T& element){element *= factor;});
    };

//OTHER MEMBER FUNCTIONS

    //Print function to print elements within a vector
    constexpr void  print() noexcept
    {
        std::cout << "Print function in C class is now used" << std::endl;
        for(const T& element: m_vector) //Range-based for-loop
        {
            std::cout << element << ", " << std::endl;
        }
    };

};

#endif //C_hpp

