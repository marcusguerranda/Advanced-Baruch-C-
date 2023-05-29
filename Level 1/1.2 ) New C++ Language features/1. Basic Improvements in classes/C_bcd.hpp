//C_bcd.hpp 

//1.2.1 New C++ Language Features ("Improving your classes")
//1. Basic Improvement in classes
//Subquestions b, c, and d.

//Author: Andrew Guerrand

//Purpose: Controlling for default creation of certain special member functions, using move semantics and rvalue references, and
//         creating move constructor and move operator

//Modification date: 4/7/2023



/*                              IMPORTANT NOTE TO SELF:

If a constexpr function is not defined inside the header, the compiler can not see the definition of the constexpr functions while 
compiling all the other source files.

Obviously, if it can't see the definition of the functions, it can't perform the steps necessary to calculate them at compile-time. 
Thus all constexpr functions must be defined everywhere they are used
*/


#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>


#ifndef C_bcd_hpp
#define C_bcd_hpp

template <typename T>
class C_bcd
{
private:

    std::vector<T> m_vector;

public:

//CONSTRUCTORS AND DESTRUCTOR

    //Default constructor (explicit is optional here, as there is nothing that the constructor does that can be known at compile-time specifically)
    constexpr C_bcd() noexcept
    {
        std::cout << "Default constructor in C class has been used." << std::endl;
    };    
 

    //Overloaded constructor, taking vector as argument
    //REMARKS ON THE USE OF 'EXPLICIT' FOUND BELOW 
    explicit constexpr C_bcd(const std::vector<T>& source) noexcept: m_vector(source)                   
    {
        std::cout << "Overloaded constructor in C class has been used." << std::endl;
    };  

    //Copy constructor, taking C instance as argument
    constexpr C_bcd(const C_bcd& source) noexcept: m_vector(source.m_vector)                                       
    {
        std::cout << "Copy constructor in C class has been used." << std::endl;
    };

    //Assignment operator
    C_bcd<T>& operator = (const C_bcd& source) noexcept;

    //Destructor
    ~C_bcd() noexcept;                      


//GETTERS

    //Getter function for member vector variable within C class
    constexpr std::vector<T> const& getVector() const noexcept
    { 
        //std::cout << "Get vector function in C class has been used." << std::endl;
        return m_vector;
    };
    

//SETTERS

    //Modifier function for member vector variable within C class
    //I choose not to have constexpr here, because there could be instances where the user is asked for vector inputs, which is then fed into a C_bcd
    //instance using setVector. In that case, setVector function would not be entirely known at compile-time.
    constexpr void setVector(std::vector<T> newvector) noexcept
    {
        m_vector = newvector;
        //std::cout << "Set vector function in C class has been used." << std::endl;
    };


    //Scale function to multiply each element within the member vector by a scalar. The proposed approach in the exercise was to simply use 
    //a factor of 2, but I brought this to a more abstract implementation by requesting a scalar.
    constexpr void scale(const double& factor) noexcept
    {
        //This requires the same kind of implementation required in 1.1 exercises, on the multiplication of vector elements by a scalar.
        //I could be using std::multiplies, std::for_each, or std::transform. Here, I simply use std::for_each
        std::for_each(m_vector.begin(), m_vector.end(), [factor](T& element){element *= factor;});
    };

//OTHER MEMBER FUNCTIONS

    //Print function to print elements within a vector
    constexpr void print() noexcept
    {
        std::cout << "Print function in C class is now used" << std::endl;
        for(const T& element: m_vector) //Range-based for-loop
        {
            std::cout << element << ", " << std::endl;
        }
    };

};

#ifndef C_bcd_cpp
#include "C_bcd.cpp"
#endif                  //C_bcd_cpp

#endif                  //C_bcd_hpp


//The use of 'explicit' is to disallow the use of implicit conversion when creating instances. 
// Here: "C_bcd<int> obj = vec;" will use the implicit constructor (defined by the compiler), but this will not compile because we will have defined
// the overloaded constructor, taking std::vector<int> as an argument to construct an object of type 'C_bcd<int>' from 'vec'. However, since my overloaded
// constructor will be marked as 'explicit', the implicit conversion from 'std::vector' to 'C_bcd<int>' is not allowed, and the code will fail to compile.
// However, "C_bcd<int> obj(vec);" will call the explicit constructor, taking 'std::vector<int>' as an argument, and the code will compile as long as
// the constructor is defined properly.

// By marking the overloaded constructor with the 'explicit' keyword, then I would need to explicitly convert an 'std::vector' to a 'C_bcd' object using a 
// cast or constructor syntax. If I try to pass an std::vector object as an argument to a function that expects a C_bcd object, the compiler will not 
// perform an implicit conversion and will instead generate a compilation error. However, if the constructor is not marked as explicit, then the compiler 
// will perform an implicit conversion from an std::vector object to a C_bcd object when needed.
