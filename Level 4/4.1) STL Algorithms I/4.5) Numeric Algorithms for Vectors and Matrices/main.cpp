//4.1) STL Algorithms I. 5) Numeric Algorithms for vectors and matrices

//Purpose: Questions concerning the classes that we have created in the first 4 exercises.

//Author: Andrew Guerrand

//Modification dates: 6/25/2023

#include "Vector.hpp"
#include "Matrix.hpp"
#include <numeric>


//PART A: user-friendly wrappers for the STL inner_product functions.

//FIRST VARIANT. NOTE: in order to use such function, I need to define iterator functionality within the Vector class in order to access iterators of vector
//               instance   
template <typename T, int N>
T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initValue)
{
    /* Include numeric library too! OF FORM (cppreference):
            template< class InputIt1, class InputIt2, class T >
            T inner_product( InputIt1 first1, InputIt1 last1, InputIt2 first2, T init );
    */
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), initValue);

    //Looking at implementation, returns initValue copy with updated value after inner product

    /* Had I used std::transform, and not std::inner_product
        T result = initValue;
        std::transform(v1.begin(), v1.end(), v2.begin(), std::back_inserter(result), [](const T& a, const T& b) { return a * b; });
        return result;
    */
}

template <typename T>
using BinaryFunction = std::function < T (const T& t1, const T& t2)>;


//SECOND VARIANT WITH TWO ADDITIONAL BINARY OPERATIONS TAKEN AS ARGUMENT
template <typename T, int N>
T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initValue, const BinaryFunction<T>& op1, const BinaryFunction<T>& op2)
{
    /*  OF FORM (cppreference):
    template< class InputIt1, class InputIt2, class T, class BinaryOperation1, class BinaryOperation2 >
    T inner_product( InputIt1 first1, InputIt1 last1, InputIt2 first2, T init, BinaryOperation1 op1, BinaryOperation2 op2 );
    */
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), initValue, op1, op2);

    //Looking at implementation, returns initValue copy with updated value after inner product
}

//OUTER PRODUCT
//Outer product of two vectors
template<typename T, int NR, int NC>
Matrix<T, NR, NC> OuterProduct(const Vector<T,NR>& vec1, const Vector<T,NC>& vec2)
{
    Matrix<T, NR, NC> result;
    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            result[i][j] = vec1[i] * vec2[j];
        }
    }
    return result;
}

//OUTER PRODUCT, specialization for complex number
//See WIKIPEDIA: https://en.wikipedia.org/wiki/Conjugate_transpose
//  -> we can use std::conj() to calculate complex conjugates
template<typename T, int NR, int NC>
Matrix<std::complex<T>, NR, NC> OuterProduct(const Vector<std::complex<T>,NR>& vec1, const Vector<std::complex<T>,NC>& vec2)
{
    Matrix<std::complex<T>, NR, NC> result;
    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            result[i][j] = vec1[i] * std::conj(vec2[j]);
        }
    }
    return result;
}


int main()
{
    std::array<int,4> array1{1,2,3,4};
    //BinaryFunction = std::function < T (const T& t1, const T& t2)>
    
    Vector<int,4> v1(array1);
    Vector<int,4> v2(v1);
    v2 = v2*3;

    std::cout << "Vector v1:\n";
    std::cout << "v1: "; v1.Print();
    std::cout << "v2: "; v2.Print(); 

//PARTS A, B, C
//Creating ADD and MUL
    BinaryFunction<int> ADD = [](const int& t1, const int& t2){return t1+t2;};
    BinaryFunction<int> MUL = [](const int& t1, const int& t2){return t1*t2;};

    int result1 = inner_product(v1, v2, 0);
    int result2 = inner_product(v1, v2, 0, ADD, MUL);

    std::cout << "Result using std::inner_product is: " << result1 << std::endl;
    std::cout << "Result using std::inner_product and giving ADD and MUL as two binary additional operations as arguments gives: " << result2 << std::endl;

//PART D: Write code to compute the outer product of two vectors:

    Vector<std::complex<int>,4> complex_vec = std::array<std::complex<int>,4>{(2,1), (1,1), (3,4), (5,2)};

    //Normal overloaded OuterProduct function
    Matrix<int,4,4> normalOuter{OuterProduct(v1,v2)};
    Matrix<std::complex<int>,4,4> complexOuter{OuterProduct(complex_vec,complex_vec)};

    std::cout << "PART D and E for OUTER PRODUCTS\n Outer product of vectors v1 and v2 is:\n";
    normalOuter.Print();

    std::cout<< "\nOuter product of vector complex_vec with itself is: "; complexOuter.Print();


    std::cout << std::endl;
    return 0;
}