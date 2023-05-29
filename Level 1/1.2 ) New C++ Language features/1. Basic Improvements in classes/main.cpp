//main.hpp 

//1.2.1 New C++ Language Features ("Improving your classes")
//1. Basic Improvement in classes
//Author: Andrew Guerrand

//Purpose: Controlling for default creation of certain special member functions, using move semantics and rvalue references, and
//         creating move constructor and move operator

//Modification date: 4/6/2023


#include "C_a.hpp"   //Header file for the default class implementation at the beginning of the exercise
#include "C_bcd.hpp" //Header file for subquestions b,c, and d of part 1 (Basic Improvements in classes) in 1.2) New C++ Language Features

int main()
{
/*

//PART A:

    C_a<int> c1;                                //Default constructor summoned

    std::vector<int> vector1 = {1,2,3,4,5};
    C_a<int> c2(vector1);                     //Using overloaded constructor

    C_a<int>c3(c2);                           //Using copy constructor to create and instantiate c3 instance
    
    c1.print();  //Printing contents of c1 (will contain nothing, as expected), c2, and c3
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
*/


//                                              When testing my code, I get the following:
/*
error: use of deleted function 'C_a<T>::C_a(const C_a<T>&) [with T = int]'
   26 |     C_a<int>c3(c2);                           //Using copy constructor to create and instantiate c3 instance
      |                  ^
note: declared here
   31 |     C_a(const C_a& source) = delete;
      |     ^~~
error: use of deleted function 'C_a<T>& C_a<T>::operator=(const C_a<T>&) [with T = int]'
   38 |     c3 = c2;                                  //Using assignment operator
      |          ^~
note: declared here
   34 |     C_a& operator = (const C_a& source) = delete;
      |          ^~~~~~~~
Build finished with error(s).
*/


//Remarks: As expected, when using the assignment operator and copy constructor, I get a compiling error because of the deleted functions.
//         When solely focusing on the default constructor, I simply get a message saying the print function is used and the destructor is used.
//         Indeed, there are std::cout messages in the latter (print() and destructor), but the default constructor simply does not output a message.
//         Everything is expected here.



//PART B:


    C_bcd<int> c1;                                //Default constructor summoned

    std::vector<int> vector1 = {1,2,3,4,5};       
    C_bcd<int> c2(vector1);                       //Using overloaded constructor

    //Testing 'explicit' for overloaded constructor. It will not compile as the implicit conversion is called, when we want an explicit conversion.
    //C_bcd<int> c4 = vector1;    
    /*
    error: conversion from 'std::vector<int, std::allocator<int> >' to non-scalar type 'C_bcd<int>' requested
    82 |     C_bcd<int> c4 = vector1;
    */            

    C_bcd<int>c3(c2);                             //Using copy constructor to create and instantiate c3 instance (explicit conversion here)

    c1.print();  //Printing contents of c1 (will contain nothing, as expected), c2, and c3
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
