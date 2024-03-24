//Vector.hpp

#ifndef VECTOR_CLASS_HPP
#define VECTOR_CLASS_HPP

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>

//Fixed-size vector class
template <typename T, int N>
class Vector {
private:
    std::array<T, N> m_array;

public:
    //Default constructor
    Vector(){}

    //Overloaded constructor with value as argument
    Vector(const std::array<T, N>& array) 
    {
        for (int i = 0; i < N; i++) 
        {
            m_array[i] = array[i];
        }
    }

    //Copy constructor
    Vector(const Vector& vec) 
    {
        for (int i = 0; i < N; i++) 
        {
            m_array[i] = vec.m_array[i];
        }
    }

    //Accessing elements (read/write) with [] operator
    T& operator [] (int index) 
    {
        return m_array[index];
    }

    //Addition using + operator
    Vector operator + (const Vector& vec) const 
    {
        Vector result;
        for (int i = 0; i < N; i++) 
        {
            result[i] = m_array[i] + vec.m_array[i];
        }
        return result;
    }

    //Subtraction using - operator
    Vector operator - (const Vector& vec) const 
    {
        Vector result;
        for (int i = 0; i < N; i++) 
        {
            result[i] = m_array[i] - vec.m_array[i];
        }
        return result;
    }

    //Unary minus (used to negate an expression or numeric operand)
    Vector operator - () const 
    {
        Vector result;
        for (int i = 0; i < N; i++) 
        {
            result[i] = -m_array[i];
        }
        return result;
    }

    //Premultiplication by a scalar quantity
    Vector operator * (const T& scalar) const 
    {
        Vector result;
        for (int i = 0; i < N; i++) 
        {
            result[i] = m_array[i] * scalar;
        }
        return result;
    }


    //By introducing the extra template parameter, I can multiply the vector by a scalar of a different type.
    //Scalar multiplication operator *
    template <typename F>
    Vector<F, N> operator * (const F& scalar) const
    {
        Vector<F, N> result;
        for (int i = 0; i < N; i++) {
            result[i] = m_array[i] * scalar;
        }
        return result;
    }

    //Printer function
    void Print() const 
    {
        std::cout << "[";
        for (int i = 0; i < N; i++) 
        {
            std::cout << m_array[i];
            if (i != N - 1) 
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    //PART E
    /*Create a member function that modifies all the elements of a vector using std::function <T 
    (const T&)>. Internally, the member function should call std::transform or use the internal array 
    directly. Be careful: data is on the stack and not on the heap. The signature of the function is:
                void modify(const std::function < Type (Type&)>& f);
    The power of this member function is that we can modify the elements of a vector by providing different 
    kinds of functions such as scaling, offsetting and so on (in fact, can be seen as a very simple example of a 
    Strategy or even Visitor pattern).*/

    //Modify all elements of the vector using a std::function
    void Modify(const std::function<T(T&)>& f) 
    {
        for(T& element: this->m_array)
        {
            element = f(element);
        }

        //Using std::transform:
            //std::transform(m_array.begin(), m_array.end(), m_array.begin(), f);
    }

};

#endif // VECTOR_CLASS_HPP



/*  WHEN USING TEMPLATES:

if:
    template <typename T, int N> at beginning of class, 
    then in SOURCE FILE, you need to include that at the beginning of every constructor and member function. You also need
    to include <T,N> after Vector such:

    template<typename T, int N>
    Vector<T, N> Vector<T, N>::operator * (const T& scalar) const

    THIS IS NOT THE FIRST TIME YOU FORGET... Now it's registered
*/

