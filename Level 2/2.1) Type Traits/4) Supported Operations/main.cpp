//2.1.4: Supported Operations

//Purpose: Checking a classes member functions/constructors by calling <type_trait> functionalities relevant to us

//Author: Andrew Guerrand

//Modification dates: 5/11/2023

#include <iostream>
#include <type_traits>
#include "PointABC.hpp"        //Point headerfile (derived, for questions A,B, and C), which includes "Shape.hpp" itself
#include "PointD.hpp"          //Point headerfile (derived, for questions D), which includes "Shape.hpp" itself
#include "PointE.hpp"          //Point headerfile (derived, for question E), which includes "Shape.hpp" itself

int main()
{

//Part A: Programmatically determine if the type Point has a virtual destructor 

    std::cout << std::boolalpha;    //Note: to reverse, simply type: std::cout << std::noboolalpha;
    std::cout << "PART A\n";
    std::cout << "Does PointABC have a virtual destructor? :" << std::has_virtual_destructor<PointABC>::value << std::endl;
    //This makes sense because Shape is an abstract class, and therefore cannot be instantiated. Ensues, nothing can be destroyed...


//Part B: Programmatically determine if type Point has the following constructors: default, copy, move
//Not to mistak wit std::is_copy_assignable! See belo for personal notes
    std::cout << "\nPART B\n";
    std::cout << "Does PointABC have a default constructor? : " << std::is_default_constructible<PointABC>::value << std::endl;
    std::cout << "Is PointABC copy constructible? (has a copy constructor?): " << std::is_copy_constructible<PointABC>::value << std::endl;
    std::cout << "Is PointABC move constructible (has a move constructor)?: " << std::is_move_constructible<PointABC>::value << std::endl;  

//Part C: Programmatically determine if type Point is copy assignable/move assignable
    std::cout << "\nPART C\n";
    std::cout << "Is PointABC copy assignable? : " << std::is_copy_assignable<PointABC>::value << std::endl;
    std::cout << "Is PointABC move assignable? : " << std::is_move_assignable<PointABC>::value << std::endl;

//Part D: Set the copy constructor and assignment operator as ‘deleted functions’ and perform steps b)-c) again; 
//        do you get the same result?

    std::cout << "\nPART D\n"; 
    std::cout << "Does PointD have a default constructor? : " << std::is_default_constructible<PointD>::value << std::endl;
    std::cout << "Is PointD copy constructible? (has a copy constructor?): " << std::is_copy_constructible<PointD>::value << std::endl;
    std::cout << "Is PointD move constructible (has a move constructor)?: " << std::is_move_constructible<PointD>::value << std::endl;  
    std::cout << "Is PointD copy assignable? : " << std::is_copy_assignable<PointD>::value << std::endl;
    std::cout << "Is PointD move assignable? : " << std::is_move_assignable<PointD>::value << std::endl;

//Part E:  Add move semantics code (explicit move constructor and move assignment operator) and perform 
//         steps b)-c) again; do you get the same result?

    std::cout << "\nPART E\n"; 
    std::cout << "Does PointE have a default constructor? : " << std::is_default_constructible<PointE>::value << std::endl;
    std::cout << "Is PointE copy constructible? (has a copy constructor?): " << std::is_copy_constructible<PointE>::value << std::endl;
    std::cout << "Is PointE move constructible (has a move constructor)?: " << std::is_move_constructible<PointE>::value << std::endl;  
    std::cout << "Is PointE copy assignable? : " << std::is_copy_assignable<PointE>::value << std::endl;
    std::cout << "Is PointE move assignable? : " << std::is_move_assignable<PointE>::value << std::endl;

    return 0;
}



/*                                              NOTES TO SELF:

What is the difference between std::is_copy_constructible and std::is_copy_assignable?

Firstly, they are two type traits in the <type_traits> header of the C++ standard library.
Secondly:

    - 'std::is_copy_constructible' checks if a type is copy-constructible, meaning that an object of the type 
      can be constructed from an existing object of the same type.

    - 'std::is_copy_assignable' checks if a type is copy-assignable, meaning that an existing object of the type 
      can be assigned the value of another object of the same type.

Examples:

MyClass obj1(42); // create a MyClass object
MyClass obj2 = obj1; // construct a new MyClass object from obj1        --> HERE, OBJ2 IS CONSTRUCTED FROM OBJECT OBJ1


MyClass obj1(42); // create a MyClass object
MyClass obj2(0); // create another MyClass object
obj2 = obj1; // assign obj1's value to obj2                             --> HERE, OBJ1 ASSIGNS ITS VALUE TO OBJ2


    - std::is_move_constructible: This trait checks whether a type is move-constructible. 
      A type is move-constructible if it can be CONSTRUCTED from an rvalue of its own type.

    - std::is_move_assignable: This trait checks whether a type is move-assignable. 
    A type is move-assignable if it can be ASSIGNED from an rvalue of its own type.



The copy constructor and the copy assignment operator are both ways of copying one object to another, but they differ in how they are used.

The copy constructor is used to create a new object from an existing object. It is called when a new object is created by copying an existing object, 
either by passing the existing object by value, or by initializing a new object with an existing object.

The copy assignment operator is used to assign the value of one object to another. It is called when an existing object is assigned a new value, 
either by direct assignment or by passing the existing object by reference to a function that assigns a new value.

In terms of syntax, the copy constructor has a signature of ClassName(const ClassName&), where ClassName is the name of the class, while the copy 
assignment operator has a signature of ClassName& operator=(const ClassName&).



*/