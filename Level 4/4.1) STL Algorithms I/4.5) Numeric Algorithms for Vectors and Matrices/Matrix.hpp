//Matrix.hpp

#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <complex>
#include "Vector.hpp"

template <typename T, int NR, int NC> 
using NestedMatrix = std::array<std::array<T, NC>, NR>;

//Fixed-size vector class
//where NR is "number of row" and NC is "number of column"
template <typename T, int NR, int NC>
class Matrix 
{
private:

    NestedMatrix<T, NR, NC> matrix;

public:

    //Default constructor
    Matrix(){}

    //Overloaded constructor with single value of type T as argument 
    explicit Matrix(const T& value)
    {
        for (auto& row : matrix)
        {
            std::fill(row.begin(), row.end(), value);
        }
    }

    //Overloaded constructor with nested matrix as argument (array of arrays)
    Matrix(const NestedMatrix<T, NR, NC>& source): matrix(source){}

    //Copy constructor, taking Matrix instance as argument
    Matrix(const Matrix& source) : matrix(source.matrix){}

    //Accessing elements (read/write) with (,) operator
    std::array<T,NC>& operator[] (int row) 
    {
        return matrix[row];
    }

    //Accessing elements (read/write) with (,) operator
    const std::array<T,NC>& operator[] (int row) const
    {
        return matrix[row];
    }

    //Accessing elements using (row, col) syntax
    T& operator() (int row, int col)
    {
        return matrix[row][col];
    }

    //Accessing elements using (row, col) syntax (const version)
    const T& operator() (int row, int col) const
    {
        return matrix[row][col];
    }

    //Addition using + operator
    Matrix operator + (const Matrix& other) const
    {
        Matrix result;
        for (int i = 0; i < NR; i++)
        {
            for (int j = 0; j < NC; j++)
            {
                result(i + 1, j + 1) = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    //Subtraction using - operator
    Matrix operator - (const Matrix& other) const
    {
        Matrix result;
        for (int i = 0; i < NR; i++)
        {
            for (int j = 0; j < NC; j++)
            {
                result(i + 1, j + 1) = matrix[i][j] - other.matrix[i][j];
            }
        }
        return result;
    }

    //Unary minus (used to negate an expression or numeric operand)
    Matrix operator - () const
    {
        Matrix result;
        for (int i = 0; i < NR; i++)
        {
            for (int j = 0; j < NC; j++)
            {
                result(i + 1, j + 1) = -matrix[i][j];
            }
        }
        return result;
    }

    //Premultiplication by a scalar quantity
    Matrix operator * (const T& scalar) const
    {
        Matrix result;
        for (int i = 0; i < NR; i++)
        {
            for (int j = 0; j < NC; j++)
            {
                result(i + 1, j + 1) = matrix[i][j] * scalar;
            }
        }
        return result;
    }

    //Printer function
    void Print() const
    {
        std::cout << "[";
        for (int i = 0; i < NR; i++)
        {
            std::cout << "[";
            for (int j = 0; j < NC; j++)
            {
                std::cout << matrix[i][j];
                if (j != NC - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << "]"<<std::endl;;
            /*if (i != NR - 1)
            {
                std::cout << ", ";
            }*/
        }
        std::cout << "]" << std::endl;
    }

    void Modify(const std::function<T(&)>& f)
    {
        for (auto& row : matrix)
        {
            for (auto& element : row)
            {
                element = f(element);
            }
        }
    }


};

#endif // MATRIX_CLASS_HPP


