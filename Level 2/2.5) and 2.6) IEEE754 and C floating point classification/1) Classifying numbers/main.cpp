//2.5.1:  IEEE754 and C Floating Point Classification

//Purpose: We use C++11 syntax to categorise float, double, long double, and integral types as zero, subnormal, normal, infinite, NaN, or 
//         an implementation-defined category/

//Author: Andrew Guerrand

//Modification dates: 5/18/2023

#include <iostream>
#include <cmath>        //<cmath> to use functionalities like std::fpclassify
#include <cfloat>       //<cfloat> to use DBL_MIN (smallest positive value that can be represented by the double data type without losing precision)
#include <limits>       //<limits> to use std::numeric_limits::... functionalities

//Classifier using generic function
template <typename T>
const char* Classify1(T t) 
{
    switch (std::fpclassify(t))
    {
        case FP_INFINITE: return "Inf";
        case FP_NAN: return "NaN";
        case FP_NORMAL: return "normal";
        case FP_SUBNORMAL: return "subnormal";
        case FP_ZERO: return "zero";
        default: return "unknown";
    }
}


//Classifier using std::isnormal, std::isfinite, std::isinf, std::isnan, etc.
template<typename T>
const char* Classify2(T source)
{
    if(std::isfinite(source))
    {
        return "Is finite\n";
    }

    if(std::isinf(source))
    {
        return "Is infinite\n";
    }

    if(std::isnan(source))
    {
        return "Is NaN\n";
    }

    if(std::isnormal(source))
    {
        return "Is normal\n";
    }

    else {return "No clue what this...\n";};
}


int main()
{

    std::cout << "\nPART A" << std::endl;
    double val = std::numeric_limits<double>::max();    //Retuens the maximum finite value that can be represented by 'double'
    std::cout << "Category of 'std::numeric_limits<double>::max()' is: " << Classify1(val) << std::endl;
    std::cout << "Category of '2.0 * val' is: " << Classify1(2.0 * val) << std::endl;
    std::cout << "Category of '2.0 * val' is: " << Classify1(3.1415 + val) << std::endl;

    double val2 = std::numeric_limits<double>::min() - 3.1415;
    std::cout << "Category of 'std::numeric_limits<double>::min() - 3.1415' is: " << Classify1(val2) << std::endl;
    std::cout << "Category of 'val2/2.0' is: " << Classify1(val2/2.0) << std::endl;
    std::cout << "Category of 'val2/2.0' is: " << Classify1(DBL_MIN/2) << std::endl;
    //DBL_MIN: smallest positive value that can be represented by the double data type without losing precision

//PART B: Using std::isinfinite, std::isinf, std::isnan, std::isnormal

    std::cout << "\nPART B: " << std::endl;
    double factor = 2.0;
    std::cout << "Type of 'double factor = 2.0' is: " << Classify2(factor);
    val = factor*std::numeric_limits<double>::max();
    std::cout << "Type of factor*std::numeric_limits<double>::max(), where factor = 2.0, is: " << Classify2(val);
    
    std::cout << "Type of val-val is: " << Classify2(val - val);
    std::cout << "Type of std::sqrt(-1.0) is " << Classify2(std::sqrt(-1.0));
    std::cout << "Type of std::log(0.0) is: " << Classify2(std::log(0.0));
    std::cout << "Type of std::exp(val) is: " << Classify2(std::exp(val));

    return 0;
}