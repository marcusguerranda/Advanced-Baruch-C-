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
