//2.8) 5. Creating object Adapters for bitset, compile-time

//Purpose: Create a compile-time matrix (BitMatrix<N, M>) consisting of N rows and M columns whose elements are bits.
//         -The chosen data structure must be efficient (accessing the elements, etc.)
//         -Its interface must have the same look andfeel as that of std::bitset
//         -It must be generic enough to support a range of applications in different domains

//Author: Andrew Guerrand

//Modification dates:5/30/2023

#include "BitMatrix.hpp"

int main() 
{
/*PART A:
    Determine which data structure to use in order to implement BitMatrix<N, M>, for example as a:
    - nested array std::array<std::bitset<M>, N>, OR a
    - one-dimensional array std::bitset<N*M>
        ->Which choice is “optimal” is for you to decide.
*/

/*
ANSWER: Factors to consider one over the other really depends on the size of the matrix, the typical access patterns, available memory, and performance
        requirements of the application at hand.

        -> If memory consumption a concern -> one-dimensional array may be more suitable (less memory overhead)
        -> If the matrices are smaller and direct element-level access is crucial, nested array may provide a more intuitive interface.

ONE-DiMENSION ARRAY: 
    Advantages: 
        -> consumes less memory (uses one single instance of std::bitset to represent entire matrix)
        -> contiguous memory layout (especially for larger matrices) = better memory locality and cache efficiency

NESTED ARRAY:
    Advantages:
        -> Clearer separation of rows and columns, which can be more intuitive and easier to understand
        -> Enables direct access to individual elements by row and column indices, making element-level operations more straightforward. 


Conclusion: I will go for nested array
*/

    constexpr int M = 3; //Number of rows
    constexpr int N = 4; //Number of columns

    //Testing constructors  
    BitMatrix<M, N> matrix1;            //Default
    BitMatrix<M, N> matrix2(0b1010);    //Overloaded
    BitMatrix<M, N> matrix3(matrix1);   //Copy constructor

    //Testing printing functions
    matrix1.Print();                    //Print all rows
    matrix1.Print(1);                   //Print specific row

    //Testing setting/resetting/flipping bits
    BitMatrix<M, N> matrix4;
    matrix4.Set();
    matrix4.Print();
    matrix4.Reset();
    matrix4.Print();
    matrix4.Flip();
    matrix4.Print();

    //Testing bit tests
    bool allSet = matrix2.All();
    bool rowAllSet = matrix2.All(1);
    bool noneSet = matrix2.None();
    bool rowNoneSet = matrix2.None(1);
    bool anySet = matrix2.Any();
    bool rowAnySet = matrix2.Any(1);

    std::cout << "All bits set: " << allSet << std::endl;
    std::cout << "Row 1 - All bits set: " << rowAllSet << std::endl;
    std::cout << "No bits set: " << noneSet << std::endl;
    std::cout << "Row 1 - No bits set: " << rowNoneSet << std::endl;
    std::cout << "Any bit set: " << anySet << std::endl;
    std::cout << "Row 1 - Any bit set: " << rowAnySet << std::endl;

    //Testing accessing elements
    bool bit1 = matrix2(1, 0);
    bool bit2 = matrix2(0, 2);

    std::cout << "Element (1, 0): " << bit1 << std::endl;
    std::cout << "Element (0, 2): " << bit2 << std::endl;

    //Testing counting bits
    size_t count1 = matrix2.Count();
    size_t count2 = matrix2.Count(1);

    std::cout << "Count of bits: " << count1 << std::endl;
    std::cout << "Count of bits in row 1: " << count2 << std::endl;

    //Testing bitwise operations
    BitMatrix<M, N> matrix5(0b1100);
    BitMatrix<M, N> matrix6(0b0110);

    BitMatrix<M, N> resultOr = matrix5 | matrix6;
    BitMatrix<M, N> resultXor = matrix5 ^ matrix6;
    BitMatrix<M, N> resultAnd = matrix5 & matrix6;

    resultOr.Print();
    resultXor.Print();
    resultAnd.Print();

    return 0;
}