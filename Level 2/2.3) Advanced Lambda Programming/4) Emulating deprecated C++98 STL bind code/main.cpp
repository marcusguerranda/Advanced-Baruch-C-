//2.3.4: (Emulating deprecated C++ 98 STL Bind Code)

//Purpose: Emulating deprecated C++ 98 STL Bind Code

//Author: Andrew Guerrand

//Modification dates: 5/15/2023


#include <iostream>
#include <functional>

//Given in 2.3.3
//Function maps 'Domain' to 'Range'
template <typename R, typename D> 
using FunctionType = std::function<R (const D x)>;

//Working function type
using ScalarFunction = FunctionType<double, double>;


template <typename T>
std::function<T (const T&)> bind1st
(const std::function<T (const T& x, const T& y)>& f, const T& x_)
{   
    return [=](const T& y_)
    {
        return f(x_,y_);
    };
}

template <typename T>
std::function<T(const T&)> bind2nd
(const std::function<T (const T& x, const T& y)>& f, const T& y_)
{   
    return [=](const T& x_)
    {
        return f(x_,y_);
    };
}




int main()
{   //I add some code to the already given code.
    //Notably, I need to define fxy, and add fy, by using bind1st

    double yval = 10.0;
    double xval = 11.11;

    //Simple lambda function
    auto fxy = [](const double& x, const double& y){return x + y;};

    ScalarFunction fx = bind2nd<double>(fxy, yval);
    ScalarFunction fy = bind1st<double>(fxy, xval);
    std::cout << "fx= " << fx(3.0) << ". fy= " << fy(3.0) << std::endl;

    // Test new bind code on STL algorithms
    std::vector<double> vec(10, 2.0);
    
    std::cout << "Applying fx scalar function to each element of our vector vec." << std::endl;
    std::transform(vec.begin(), vec.end(), vec.begin(), fx);
    for (auto i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << ",";
    }
    std::cout << std::endl;

    std::transform(vec.begin(), vec.end(), vec.begin(), fy);

    std::cout << "\nApplying fy scalar function to each element of our vector vec." << std::endl;
    for (auto i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << ",";
    }
    std::cout << std::endl;



    return 0;
}