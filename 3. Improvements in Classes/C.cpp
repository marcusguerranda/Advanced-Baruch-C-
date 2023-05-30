#include "C.hpp"

#ifndef C_cpp
#define C_cpp

//CONSTRUCTORS AND DESTRUCTOR

    //Assignment operator
    template <typename T>
    C<T>& C<T>::operator = (const C& source) noexcept
    {
        m_vector = source.m_vector;
        std::cout << "Assignment operator in C class has been used." << std::endl;
        return *this;
    }; 

    //Move assignment operator
    template <typename T>
    C<T>& C<T>::operator = (C&& source) noexcept
    {
        m_vector = std::move(source.m_vector);
        std::cout << "Move assignment operator in C class has been used." << std::endl;
        return *this;
    }

    //Destructor
    template <typename T>
    C<T>::~C() noexcept 
    {
        std::cout << "Destructor in C class has been used." << std::endl;
    };                      


#endif //C_cpp