//main.cpp

//Purpose: Numeric algorithms with tuples

//Author: Andrew Guerrand

//Modification Date: 4/13/2023


/*
PART A) Create a template class with static member functions to compute the maximum, sum and average of 
the elements in the tuple. A typical class is:
        template <typename T, typename Tuple, std::size_t N>
        struct Calculator
        {
            // TBD
        };
PART B) Test the code on tuples with two and three elements whose underlying type is double.
PART C) Compute the sum and average of a tuple whose element type is std::complex<int>.
*/




#include <iostream>
#include <tuple>
#include <algorithm>
#include <complex>
#include <cmath>

template<typename T, typename Tuple, std::size_t N>
struct Calculator
{
    static T maxCalculator(const Tuple& source_tuple)
    {   
        return std::apply([](const auto&... args) { return std::max({args...}); }, source_tuple);
    };

    static T sumCalculator(const Tuple& source_tuple)
    {   
        return std::apply( [](const auto&... args) { return (args + ...); }, source_tuple);
    };  

    //Average calculator
    static T averageCalculator(const Tuple& source_tuple)
    {
        // Using static_cast instead of std::real to avoid the need to include the <complex> header file
        return sumCalculator(source_tuple) / static_cast<T>(N);
    };
};

//Alias to make declarations more succint
template <typename T, typename Tuple>
using Calculator_t = Calculator<T, Tuple, std::tuple_size<Tuple>::value>;


int main()
{

//PART B:  Test the code on tuples with two and three elements whose underlying type is double
    auto tup1 = std::make_tuple(1.23, 3.45);             //Two elements
    auto tup2 = std::make_tuple(1.11, 2.22, 3.33);       //Three elements


    //Average, sum, and max calculations (in order) for tup1 (tuple with two elements)
    double av1 = Calculator_t<double, decltype(tup1)>::averageCalculator(tup1);
    double sum1 = Calculator_t<double, decltype(tup1)>::sumCalculator(tup1);
    double max1 = Calculator_t<double, decltype(tup1)>::maxCalculator(tup1);

    std::cout << "For tup1 with two double elements, the average is: " << av1 << " , the sum is: " << sum1 << " , and the max is: " << max1 << ".\n" << std::endl;

    //Average, sum, and max calculations (in order) for tup2 (tuple with three elements)
    double av2 = Calculator_t<double, decltype(tup2)>::averageCalculator(tup2);
    double sum2 = Calculator_t<double, decltype(tup2)>::sumCalculator(tup2);
    double max2 = Calculator_t<double, decltype(tup2)>::maxCalculator(tup2);

    std::cout << "For tup2 with three double elements, the average is: " << av2 << " , the sum is: " << sum2 << " , and the max is: " << max2 << ".\n" << std::endl;

//PART C:  Compute the sum and average of a tuple whose element type is std::complex<int>

    auto tup3 = std::make_tuple(std::complex<int>(1, 2), std::complex<int>(-3, 4), std::complex<int>(5, -6));

    std::complex<int> av3 = Calculator_t<std::complex<int>, decltype(tup3)>::averageCalculator(tup3);
    std::complex<int> sum3 = Calculator_t<std::complex<int>, decltype(tup3)>::sumCalculator(tup3);

    std::cout << "For tup3 with three complex numbers, the average is: " << av3 << ", and the sum is: " << sum3 << ".\n" << std::endl;
    return 0;
}




//NOTE TO SELF: We use 'static' as a design mechanism to structure related functionality that is not object specific.
//              There is no need to create Calculator objects, so using static make the code and design a lot cleaner.









/*
                FIRST ATTEMPT
                                --> Didn't work because 

template<typename T, typename Tuple, std::size_t N>
struct Calculator
{
    static T maxCalculator(const Tuple& source_tuple)
    {   
        return std::apply([](const auto&... args) { return std::max({args...}); }, source_tuple);
    };

    static T sumCalculator(const Tuple& source_tuple)
    {   
        return std::apply( [](const auto&... args) { return (args + ...); }, source_tuple);
    };  

    //Average calculator
    static T averageCalculator(const Tuple& source_tuple)
    {
        return static_cast<double>(sumCalculator(source_tuple)/N);
    };
};


*/