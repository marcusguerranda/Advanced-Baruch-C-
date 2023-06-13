//2.3.3: Doing mathematics in C++

//Purpose: We build a simple vector space of functions. The basic objective is to show how to create higher-order functions in C++.
//         We consider only functions of a single variable returning a scalar value. ALL UNDERLYING TYPES ARE 'DOUBLE'

//Author: Andrew Guerrand

//Modification dates: 5/15/2023

/*
    PART A: Create functions to add, multiply and subtract two functions. Create unary additive inverse of a 
    function and a function representing scalar multiplication. 

    PART B: Create trigonometric and other functions such as those in <cmath>.

    PART C: Finally, produce code that allows you to do the following:
            auto h1 = min(f, g);
            auto h2 = max(f, g);
            std::cout << "min(f,g): " << h1(2.0) << '\n';
            std::cout << "max(f,g): " << h2(2.0) << '\n';
            auto h3 = min(h1, max(2 * f, 3 * g));
            auto h4 = max(h2, max(-2 * f, 3 * g));
*/


#include <functional>
#include <iostream>
#include <cmath>

//Function maps 'Domain' to 'Range'
template <typename R, typename D> 
using FunctionType = std::function<R (const D x)>;

//Working function type
using ScalarFunction = FunctionType<double, double>;


//Addition of two functions
template <typename R, typename D>
FunctionType<R,D> operator + (const FunctionType<R,D>& f, const FunctionType<R,D>& g)
{ // Addition of functions
    return [=] (const D& x)
    {
        return f(x) + g(x);
    };
}


//Substraction of two functions
template <typename R, typename D>
FunctionType<R,D> operator - (const FunctionType<R,D>& f, const FunctionType<R,D>& g)
{
    return [=](const D& x)
    {
        return f(x) - g(x); 
    };
}

//Multiplication of two functions
template<typename R, typename D>
FunctionType<R,D> operator * (const FunctionType<R,D>& f , const FunctionType<R,D>& g)
{
    return [=](const D x)
    {
        return f(x) * g(x);
    };
}


//Division of two functions
template<typename R, typename D>
FunctionType<R,D> operator / (const FunctionType<R,D>& f , const FunctionType<R,D>& g)
{
    return [=](const D x)
    {
        return f(x) / g(x);
    };
}


//Composition of functions
template <typename R, typename D>
FunctionType<R,D> operator << (const FunctionType<R,D>& f, const FunctionType<R,D>& g)
{
    return [=](const D& x)
    {
        return f(g(x));
    };
}

//Scalar multiplication
template <typename R, typename D>
FunctionType<R,D> operator * (const double scalar, const FunctionType<R,D>& f)
{
    return [=](const D& x)
    {
        return scalar * f(x);
    };
}



//Additive inverse of a function
template <typename R, typename D>
FunctionType<R,D> operator - (const FunctionType<R,D>& f)
{
    return [=](const D& x)
    {
        return -f(x);
    };
} 

//PART B: Create trigonometric and other functions such as those in <cmath>
//        Implement the following functions: cos, sin, tan, exp, log, abs, and sqrt

//Exponential function
template <typename R, typename D>
FunctionType<R,D> exp(const FunctionType<R,D>& f)
{   
    return [=](const D& x)
    {
        return std::exp(f(x));
    };
}

//Cosine function
template <typename R, typename D>
FunctionType<R,D> cos(const FunctionType<R,D>& f)
{
    return [=](const D& x)
    {
        return std::cos(f(x));
    };
}

//Sine function
template <typename R, typename D>
FunctionType<R,D> sin(const FunctionType<R,D>& f)
{
    return [=](const D& x)
    {
        return std::sin(f(x));
    };
}

//Tan function
template <typename R, typename D>
FunctionType<R,D> tan(const FunctionType<R,D>& f)
{
    return [=](const D& x)
    {
        return std::tan(f(x));
    };
}

//Log function
template <typename R, typename D>
FunctionType<R,D> log(const FunctionType<R,D>& f)
{
    return [=](const D& x)
    {
        return std::log(f(x));
    };
}

//Abs function
template <typename R, typename D>
FunctionType<R,D> abs(const FunctionType<R,D>& f)
{
    return [=](const D& x)
    {
        return std::abs(f(x));
    };
}

//Sqrt function
template <typename R, typename D>
FunctionType<R,D> sqrt(const FunctionType<R,D>& f)
{
    return [=](const D& x)
    {
        return std::sqrt(f(x));
    };
}


//PART C: Creating min and max functions which calculates the min between two functions for a given value

//Min function
template<typename R, typename D>
FunctionType<R,D> min(const FunctionType<R,D>& f, const FunctionType<R,D>& g)
{
    return [=](const D x )
    {
        return std::min(f(x),g(x));
    };
}

//Max function
template<typename R, typename D>
FunctionType<R,D> max(const FunctionType<R,D>& f, const FunctionType<R,D>& g)
{
    return [=](const D x )
    {
        return std::max(f(x),g(x));
    };
}


int main()
{
    ScalarFunction f = [](double x) {return x*x; };
    ScalarFunction g = [=](double x) { return x; };
    std::cout << g(2) << ", " << g(8) << "*";
    // Set I: Arithmetic functions
    double scale = 2.0;
    auto fA = 2.0*(f + g);
    auto fM = f - g;
    auto fD = f / g;
    auto fMul = f * g;
    auto fC = g << g << 4.0*g; // Compose
    auto fMinus = -(f + g);
    double x = 5.0;
    std::cout<< fA(x) << ", " << fM(x) << ", " << fD(x) << ", "
    << fMul(x)<<", compose: "<< fC(x) <<", " << fMinus(x);



//PART B: Create trigonometric and other functions such as those in <cmath>.

    auto ftmp = log(g); 
    auto ftmp2 = cos(f);
    auto f2 = (abs(exp(g))*log(g) + sqrt(ftmp)) / ftmp2;
    std::cout << f2(x) << std::endl;


//PART C: Produce code that allows you to do the following 
//        Basically create min and max functions

    auto h1 = min(f, g);
    auto h2 = max(f, g);
    std::cout << "min(f,g): " << h1(2.0) << '\n';
    std::cout << "max(f,g): " << h2(2.0) << '\n';

//CONCLUSION: all the code snippets provided in the pdf work after defining appropriate functions!

    return 0;
}