//2.5 and2.6 IEEE 754 and C floating point classification

//Purpose: Machine epsilon -> gives an upper bound on the relative error due to rounding in floating point arithmetic.

//Author: Andrew Guerrand

//Modification dates: 5/27/2023

#include <iostream>
#include <limits>

//Generalise the function given so that it works with other types other than doubles
template <typename T>
T epsilon_computer()
{
    T epsilon = (T)1.0;
    while((T)1.0 + (T)0.5*epsilon != (T) 1.0) 
    {
        epsilon *= (T) 0.5;
    }

    return epsilon;
}

//Numeric_limits epsilon function
template <typename T>
T epsilon_numeric()
{   //Note to self: do include the <limits> header file to use such functionalities...
    return std::numeric_limits<T>::epsilon();
}


int main()
{
//PART A: testing on floats, doubles, int, long long

    std::cout << "PART A: MACHINE EPSILON -> Upper bound on the RELATIVE error due to rounding in floating point arithmetic." << std::endl;
    std::cout << "Epsilon for an 'int' is: " << epsilon_computer<int>() << std::endl;
    std::cout << "Machine epsilon for a 'double' is: " << epsilon_computer<double>() << std::endl;
    std::cout << "Machine epsilon for a 'float' is: " << epsilon_computer<float>() << std::endl;
    std::cout << "Machine epsilon for a 'long long' is: " << epsilon_computer<long long>() << std::endl;

//PART B: using std::numeric_limits::epsilon() functionality rather than proprietary function

    std::cout << "\nPART B: NUMERIC LIMITS MACHINE EPSILON FUNCTION" << std::endl;
    std::cout << "Epsilon for an 'int' is: " << epsilon_numeric<int>() << std::endl;
    std::cout << "Machine epsilon for a 'double' is: " << epsilon_numeric<double>() << std::endl;
    std::cout << "Machine epsilon for a 'float' is: " << epsilon_numeric<float>() << std::endl;
    std::cout << "Machine epsilon for a 'long long' is: " << epsilon_numeric<long long>() << std::endl;


//Conclusion: for 'double', the machine epsilon values are the same.

    return 0;
}