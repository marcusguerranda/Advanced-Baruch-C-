//4.1) STL Algorithms - 3.Compile-Time matrix class

//Purpose: same as exercise 2 but with matrices
//Author: Andrew Guerrand

//Modification dates: 6/24/2023


#include <iostream>
#include "Matrix.hpp"


int main()
{
    Matrix<int,3,3> matrix0;                    //Default matrix
    Matrix<int,3,3> matrix1(0);                 //With singe value: Create a 3x3 matrix with all elements initialized to 0

    NestedMatrix<int, 3, 3> nestedMatrix1 = 
    {{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    }}; 
    Matrix<int, 3, 3> matrix2(nestedMatrix1);   //With nested matrix as argument: Create a matrix with the provided nested matrix

    std::cout << "First element in the first row and column is: " << matrix2(1,1) << std::endl;

    //Adding using + operator
    Matrix<int, 3, 3> matrix3 = matrix1 + matrix2;
    std::cout << "matrix1 + matrix2:" << std::endl;
    matrix3.Print();

    //Substracting using - operator
    Matrix<int,3,3> matrix4 = matrix2 - matrix1;
    std::cout << "matrix2 - matrix1:" << std::endl;
    matrix4.Print();

    //Unary minus
    Matrix<int,3,3> matrix5 = -matrix2;
    std::cout << "-matrix2:" << std::endl;
    matrix5.Print();

    //Premultiplication by a scalar quantity
    Matrix<int,3,3> matrix6 = matrix2 * 2;
    std::cout << "matrix2 * 2:" << std::endl;
    matrix6.Print();

    //Modify matrix elements using a lambda function
    matrix2.Modify([](int& element) { return element * 10; });
    std::cout << "Modified matrix2:" << std::endl;
    matrix2.Print();


    return 0;
}
