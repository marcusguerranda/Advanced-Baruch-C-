//main.hpp 

//1.2.1 New C++ Language Features ("Improving your classes")
//3. Improvements in Classes 
//Author: Andrew Guerrand

//Purpose: Controlling for default creation of certain special member functions, using move semantics and rvalue references, and
//         creating move constructor and move operator

//Modification date: 4/8/2023

#include "C.hpp"     //Header file for C class
#include <vector>    //Header file to use vector library
#include <string>    //Header file for string class
#include <utility>   //Header file to use std::move, for example
#include <chrono>    //Header file to use std::chrono library

/*
//Generic function to move contents from one container to another (of same type) and reporting the time it takes to perform such an operation
template<typename T>
double move_contents(T& source, T& target) 
{
    auto start = std::chrono::high_resolution_clock::now();
    target = std::move(source);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double>> (end - start).count();
}

//Generic function to print contents of many different types of data containers
template <typename Container>
void print_contents(const Container& c)
{
    std::cout << "Elements are: ";
    for (const auto& element : c)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

//User-defined code to swap two objects using COPY constructor
template <typename T>
void SwapCopyStyle(T& a, T& b)
{ // Swap a and b in copying way; temporary object needed
   T tmp(a);               // Copy constructor
   a = b;                  // Copy all elements from b to a
   b = tmp;                // Copy all elements from tmp to b
}

//User-defined code to swap two objects using MOVE semantics
template <typename T>
void SwapMoveStyle(T&& a, T&& b)
{
    T tmp(std::move(a));   // Move constructor
    a = std::move(b);      // Move all elements from b to a
    b = std::move(tmp);    // Move all elements from tmp to b
}
*/



int main()
{

//PART A:

    std::vector<int> vector1 {1,2,3,4,5,6,7,8,9,10};//Creating test vector
    C<int> c1(vector1);                             //Calls overloaded constructor (recall use of 'explicit')

    std::cout << "CONTENT IN C1: " << std::endl;
    c1.print();                                     //Print contents of c1 prior to using move constructor and move assignment operator

    C<int> c2(std::move(c1));                       //Calls move constructor, given std::move(c1) returns an rvalue reference to c1.

    std::cout << "CONTENT IN C1: " << std::endl;    //Calling print function to print m_vector in both c1 and c2, after using move constructor.
    c1.print();                                     
    std::cout << "CONTENT IN C2: " << std::endl;
    c2.print();


    C<int> c3 = std::move(c2);                      //Calls move assignment operator, given std::move(c2) returns an rvalue reference to c2.
    // Calling the move assignment operator with an rvalue without using std::move as cast
    //C<int> c3(C<int>(std::vector<int>{7, 8, 9})); -> The arguments passed on are proper temporary rvalues!
    
    std::cout << "CONTENT IN C2: " << std::endl;    //Calling print function to print m_vector in both c1 and c2, after using move assignment operator.
    c2.print();                                     
    std::cout << "CONTENT IN C3: " << std::endl;
    c3.print();



//PART B: How to ensure the move constructor instead of the move assignment operator is called?
/*
    Using std::move when passing an object to the constructor, or assignment operator, will cast the object to an rvalue reference, and therefore
    call the appropriate move constructor/move assignment operator to move the object. The move constructor needs to also be properly defined and take
    && arguments
*/




//PART C: What happens if you use an lvalue as the source of a move operation? 
//        -> In other words, what happens if you don't use std::move(lvalue) when passing it on to a move constructor/move assignment operator?
//        A: IF the copy constructor and copy assignment operator are not defined and we pass an lvalue as the source of a move operation, I will get errors.
//           IF the latter are defined, then the copy constructor and assignment operator will be called, as we are in effect 
//           passing lvalues.

    C<int> c4(c3);                  //Uses copy constructor
    c4 = c2;                        //Uses copy assignment operator
    C<int> c6(std::move(c3));       //Uses move copy constructor
    c6 = std::move(c4);             //Uses move assignment operator 

    return 0;  



};