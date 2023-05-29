
#include "C_bcd.hpp"

#ifndef C_bcd_cpp
#define C_bcd_cpp

//CONSTRUCTORS AND DESTRUCTOR

    //Assignment operator
    template <typename T>
    C_bcd<T>& C_bcd<T>::operator = (const C_bcd& source) noexcept
    {
        m_vector = source.m_vector;
        std::cout << "Assignment operator in C class has been used." << std::endl;
        return *this;
    };

    //Destructor
    template <typename T>
    C_bcd<T>::~C_bcd() noexcept 
    {
        std::cout << "Destructor in C class has been used." << std::endl;
    };                      


#endif //C_bcd_cpp

