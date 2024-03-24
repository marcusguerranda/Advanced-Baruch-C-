//4.1) STL Algorithms - 2.Compile-Time vector class

/*Purpose:
    In the next two exercises we create fixed-sized vector and matrix classes, that is classes whose instances 
    reside on the stack rather than on the heap. There are many applications of these classes where there is a 
    need for tiny vectors and tiny matrices. The scope and requirements for both classes are:
        - Constructors: default, with value as argument, and copy constructor.
        - Accessing elements (read/write) using [].
        - Adding and subtraction; unary minus.
        - Premultiplication by a scalar quantity.
*/

//Author: Andrew Guerrand

//Modification dates: 6/22/2023


#include <iostream>
#include "Vector.hpp"


int main()
{
    //Default constructor, with size 3
    Vector<int, 3> v1;                  //Creates a vector of size 3 with default-initialized elements

    //Overloaded constructor with value as argument
    std::array<int, 3> arr = {1, 2, 3};
    Vector<int, 3> v2(arr);             //Creates a vector with elements {1, 2, 3}

    //Copy constructor
    Vector<int, 3> v3(v2);              //Creates a copy of v2

    //Accessing elements (read/write) with [] operator
    v2[0] = 10;                         //Assigns 10 to the first element of v2
    std::cout << v2[0] << std::endl;    //Prints 10

    // Addition using + operator
    Vector<int, 3> v4 = v2 + v3;        //Performs element-wise addition of v2 and v3

    //Subtraction using - operator
    Vector<int, 3> v5 = v2 - v3;        //Performs element-wise subtraction of v2 and v3

    //Unary minus
    Vector<int, 3> v6 = -v2;            //Negates all elements of v2

    //Premultiplication by a scalar quantity
    int scalar = 2;
    Vector<int, 3> v7 = v2 * scalar;    //Multiplies all elements of v2 by the scalar value

    //Print instances
    std::cout << "v1: ";
    v1.Print();
    std::cout << "v2: ";
    v2.Print();

    //PART D: Implement the scalar multiplication operation as a template member function having an extra template parameter
    //Scalar multiplication with double scalar

    int scalar1 = 2;
    double scalar2 = 2;
    Vector<int, 3> v8(v4);
    Vector<int,3> scalar_vector1 = (v8*scalar1);
    Vector<double,3> scalar_vector2 = (v8* scalar2);

    std::cout << "\nPART D: Scalar multiplication with int and double scalar of vector v8:\n ";
    scalar_vector1.Print();
    scalar_vector2.Print();

    //PART E: Modify the elements of v2 using a lambda function
    std::function<int(int&)> squaring = [](int& element) { return element *= 2; };
    v2.Modify(squaring);
    std::cout << "v2 squared with modify() function: ";
    v2.Print();
    
    std::cout << "v3: ";
    v3.Print();
    std::cout << "v4: ";
    v4.Print();
    std::cout << "v5: ";
    v5.Print();
    std::cout << "v6: ";
    v6.Print();
    std::cout << "v7: ";
    v7.Print();

    return 0;
}

