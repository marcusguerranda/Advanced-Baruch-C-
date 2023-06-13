//2.4.1: (Smart pointers in boost and C++) 

//Purpose: First encounters with smart pointers: unique pointers

//Author: Andrew Guerrand

//Modification dates: 5/16/2023

#include <iostream>
#include "Point.hpp"    //Point class
#include <memory>       //For smart pointers


int main()
{
    std::cout << "PART A: Running code as given." << std::endl;
    {
    //Block with raw pointer lifecycle
    double* d = new double (1.0);
    Point* pt = new Point(1.0, 2.0);            //Two-d Point class
    
    //Dereference and call member functions
    *d = 2.0;
    (*pt).X(3.0);                               //Modify x coordinate
    (*pt).Y(3.0);                               //Modify y coordinate
    
    //Can use operators for pointer operations
    pt->X(3.0);                                 //Modify x coordinate
    pt->Y(3.0);                                 //Modify y coordinate
    
    //Explicitly clean up memory (if you have not forgotten)
    delete d;
    delete pt;
    }

    std::cout << "Code from Part A works perfectly well. NOW LET'S RE-RUN THE CODE, BUT DIRECTLY AFTER MEMORY ALLOCATION, THROW AN EXCEPTION." << std::endl;

    try
    {  // Block with raw pointer lifecycle
        double* d = new double (1.0);
        Point* pt = new Point(1.0, 2.0);// Two-d Point class

        // Dereference and call member functions
        *d = 2.0;
        (*pt).X(3.0);// Modify x coordinate
        (*pt).Y(3.0);// Modify y coordinate

        // Can use operators for pointer operations
        pt->X(3.0);// Modify x coordinate
        pt->Y(3.0);// Modify y coordinate

        //Throw exception -> memory will not be cleaned, because exception thrown before memory is deleted.
        throw "Exception thrown."; 
        // Explicitly clean up memory (if you have not forgotten)
        delete d;
        delete pt;
    }
    catch (const char* exception) 
    {
        std::cerr << exception << std::endl;
    }

//PART B: Now port the above code by replacing raw pointers by std::unique_ptr. Run the code. Are there 
//        memory leaks now?
    std::cout << "PART B: Using unique pointers " << std::endl;
    try
    {
    //Block with raw pointer lifecycle
    std::unique_ptr<double> d = std::make_unique<double>(1.0);
    std::unique_ptr<Point> pt = std::make_unique<Point>(1.0, 2.0);      //Two-d Point class
    
    //Dereference and call member functions
    *d = 2.0;
    (*pt).X(3.0);                               //Modify x coordinate
    (*pt).Y(3.0);                               //Modify y coordinate
    
    //Can use operators for pointer operations
    pt->X(3.0);                                 //Modify x coordinate
    pt->Y(3.0);                                 //Modify y coordinate
    
    //Throw exception 
    throw "Exception thrown."; 
    }
    //No need to explicitly clean up memory given the use of smart pointers automates memory management
    //No memory leaks
    catch (const char* exception) 
    {
        std::cerr << exception << std::endl;
    }



//PART C: Experiment with the following: 
//        - initialising two unique pointers to the same pointer, 
//        - assigning a unique pointer to another unique pointer and 
//        - transferring ownership from one unique pointer to another unique pointer

    std::cout << "PART C " << std::endl;

//  Initialising two unique pointers to the same pointer,
    int* int_ptr1 = new int(1);  //Pointer to a

    //std::unique_ptr<int> uptr_1(int_ptr1);
    //std::unique_ptr<int> uptr_2(int_ptr1);

    //Strangely enough, my code compiles and code runs but after a few seconds running...Strange. Using GCC compiler. What I would assume happens 
    //is that the compiler knows I have used to unique pointers to point to one same object, and therefore deletes 'uptr1' when creating 'uptr2'.


//  Assigning a unique pointer to another unique pointer  
    
    //uptr_1 = uptr_2;
    //Error: getting error: error: use of deleted function 'std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = Point; _Dp = std::default_delete<Point>]'

//  Transferring ownership from one unique pointer to another unique pointer
    std::unique_ptr<int> uptr_1(int_ptr1);
    std::unique_ptr<int> uptr_2(std::move(uptr_1));
    //Works perfectly fine.

//PART D:

    std::cout << "PART D: See comments in code." << std::endl;
    //Not sure what the point of this is when the whole exercise has been conducted already.
    //At best, I could have used the following to make the code more concise and more readable:


    //-> to include out of scope to use templates
        //template <typename T>
        //using Unique_Pointer = std::unique_ptr<T>;  

    //Literally, the rest of the code does not necessitate alias templates...

    return 0;
}