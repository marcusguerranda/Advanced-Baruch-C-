//BITMATRIX header file

#ifndef BITMATRIX_HPP
#define BITMATRIX_HPP

#include <iostream>
#include <bitset>
#include <array>

template<int M, int N>
class BitMatrix 
{
private:
    
    //Compile-time mtrix consisting of N rows and M columns, whose elements are bits
    std::array<std::bitset<N>, M> matrix;

public:

//CONSTRUCTORS AND DESTRUCTOR

    // Default constructor
    constexpr BitMatrix() : matrix() {} 

    //Overloaded constructor
    constexpr BitMatrix(unsigned long val) : matrix() 
    {
        for (std::bitset<N>& bs : matrix)
            bs = std::bitset<N>(val);
    }

    //Copy constructor
    constexpr BitMatrix(const BitMatrix<M, N>& source) : matrix(source.matrix) {} 

    //Move constructor
    constexpr BitMatrix(BitMatrix<M, N>&& source) : matrix(std::move(source.matrix)) {} 

    //Copy assignment operator
    constexpr BitMatrix<M, N>& operator=(const BitMatrix<M, N>& source)
    {
        if (this != &source)
            matrix = source.matrix;
        return *this;
    }

    //Move assignment operator
    constexpr BitMatrix<M, N>& operator=(const BitMatrix<M, N>&& source)
    {
        if (this != &source)
            matrix = std::move(source.matrix);
        return *this;
    }

    //Destructor
    ~BitMatrix(){};


/*PART C:Implement the following for ALL rows in the matrix and FOR A GIVEN row in the matrix:
    • Set/reset all bits.
    • Flip the bits.
    • Test if none, all or any bits are set.
    • Access the elements.
    • Count the number of set bits
*/

    //Print function for all rows
    void Print() const 
    {
        for (const auto& row : matrix)
            std::cout << row << "\n";
        std::cout << std::endl;
    }

    //Print function for a given row
    void Print(const size_t row) const 
    {
        std::cout << matrix[row] << "\n";
    }

    //Setter function for all rows
    void Set() 
    {
        for (auto& row : matrix)
            row.set();
    }

    //Setter for a given row 
    void Set(const size_t row) 
    {
        matrix[row].set();
    }

    //Resetter function for all rows
    void Reset() 
    {
        for (auto& row : matrix)
            row.reset();
    }

    //Resetter function for a given row
    void Reset(const size_t row) 
    {
        matrix[row].reset();
    }

    //Flip function for all rows
    void Flip() 
    {
        for (auto& row : matrix)
            row.flip();
    }

    //Flip function for a given row
    void Flip(const size_t row) 
    {
        matrix[row].flip();
    }

    //Testing if all bits are set in each row
    bool All() const 
    {
        for (const auto& row : matrix) 
        {
            if (!row.all())
                return false;
        }
        return true;
    }

    //Testing if all bits are set in a given row
    bool All(const size_t row) const 
    {
        return matrix[row].all();
    }

    //Testing if no bits are set in all rows
    bool None() const 
    {
        for (const auto& row : matrix) 
        {
            if (row.any())
                return false;
        }
        return true;
    }

    //Testing if no bits are set in a given row
    bool None(const size_t row) const 
    {
        return matrix[row].none();
    }

    //Testing if any of the bits in all rows are set
    bool Any() const 
    {
        for (const auto& row : matrix) 
        {
            if (row.any())
                return true;
        }
        return false;
    }

    //Testing if any bit of the bits in a given row is set
    bool Any(const size_t row) const 
    {
        return matrix[row].any();
    }

    //Accessing functions by overloading () operator, both for all rows, and a specific row and column
    bool operator () (const size_t row, const size_t col) const 
    {
        return matrix[row][col];
    }

    bool operator () (const size_t row) const 
    {
        return matrix[row].to_ulong() > 0;
    }

    //Counting function to count number of bits in all rows
    size_t Count() const 
    {
        size_t sum = 0;
        for (const auto& row : matrix)
            sum += row.count();
        return sum;
    }

    //Counting function to count number of bits in a given row
    size_t Count(const size_t row) const 
    {
        return matrix[row].count();
    }

//PART D: Create member functions for XOR, OR, and AND bitwise operations on bit matrices
   
    //Operator OR
    BitMatrix<M, N> operator | (const BitMatrix<M, N>& source) const 
    {
        BitMatrix<M, N> result;
        for (size_t i = 0; i < M; ++i)
            result.matrix[i] = matrix[i] | source.matrix[i];
        return result;
    }

    //Operator XOR
    BitMatrix<M, N> operator ^ (const BitMatrix<M, N>& source) const 
    {
        BitMatrix<M, N> result;
        for (size_t i = 0; i < M; ++i)
            result.matrix[i] = matrix[i] ^ source.matrix[i];
        return result;
    }

    //Operator AND
    BitMatrix<M, N> operator & (const BitMatrix<M, N>& source) const 
    {
        BitMatrix<M, N> result;
        for (size_t i = 0; i < M; ++i)
            result.matrix[i] = matrix[i] & source.matrix[i];
        return result;
    }
};

#endif //BITMATRIX_HPP