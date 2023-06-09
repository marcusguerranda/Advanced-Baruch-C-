//2.1.2: Simple switchable Bridge Functionality)

/*
Purpose:    We create a template function that supports both pointers and reference types. If it is a pointer it is 
            dereferenced and then printed while if it is not a pointer type and it is a scalar reference type then it is 
            printed directly. Use the is_pointer() function in conjunction with std::true_type and 
            std::false_type to determine which implementation should be called.
*/

//Author: Andrew Guerrand

//Modification date: 5/10/2023

/*Note: See class notes on why we use two bridge functions. We, in particular, had seen the example where the following function wouldn't compile,
        and thus justifying the use of bridge functions:

        template<typename T>
        void IsPointer2(const T& val)
        {//This code does not compile when called, why?
            std::cout << (std::is_pointer<T>::value ? *val : val);
        }
*/

#include <iostream>
#include <type_traits>  //Functions for performing compile-time type introspection


//If pointer type, this bridge function will be called
template<typename T>
void IsPointer_bridge(T&& t, std::true_type)
{
    std::cout << "Type is a pointer. Dereferenced value of pointer is: " << *t << std::endl;
}

//If not a pointer type, this bridge function will be called
template<typename T>
void IsPointer_bridge(T&& t, std::false_type)
{
    std::cout << "Type is NOT a pointer. Vaue is: " << t << std::endl;
}

template<typename T>
void IsPointer( T&& t)
{
    //Calling bridge functions to print appropriate message as a function of whether the type is a pointer or not.
    IsPointer_bridge(std::forward<T>(t), std::is_pointer<typename std::remove_reference<T>::type>());
}



int main()
{
    int a = 3.33;       //Not a pointer
    int* b = &a;        //Pointer
    const int& c = a;   //Not a pointer
    const int* d = &a;  //Pointer

    IsPointer(i);
    IsPointer(p);
    IsPointer(r);
    IsPointer(q);

    return 0;
}


/*
The use of && in the function parameter is a universal reference, which allows for both lvalues 
and rvalues to be passed to the function. The std::forward<T>(t) expression inside the function 
then preserves the value category (lvalue or rvalue) of the argument that is being passed in.

Using '&' instead of '&&' would limit the flexibility of the code, because I could only pass 
on lvalue references.
*/