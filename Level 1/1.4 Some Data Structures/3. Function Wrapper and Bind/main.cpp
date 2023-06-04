//main.cpp

//Purpose: Function wrapper and bind

//Author: Andrew Guerrand

//Modification date: 4/11/2023


#include <iostream>
#include <functional>


class C
{ // Function object with extra member functions
    private:

        double _data;

    public:
        
        //Constructor
        C(double data) : _data(data) {}

        // () operator
        double operator () (double factor)
        {
            return _data + factor;
        }

        
        double translate (double factor)
        {
            return _data + factor;
        }

        double translate2 (double factor1, double factor2)
        {
            return _data + factor1 + factor2;
        }

        static double Square(double x)
        {
            return x*x;
        }
};


//Function wrapper
template <typename T>
using FunctionType = std::function<T (const T& t)>;


template <typename T>
void print(const FunctionType<T>& f, T t)
{
    std::cout << f(t) << '\n';
}

int main()
{

//PART A: Bind the function wrapper to C’s static member function.

    //Function wrapper for C class' static member function
    //More succint alternative, as WZhang suggests on QuantNet: FunctionType<double> function_wrapper = C::Square;  (given static nature of function)

    FunctionType<double> function_wrapper = std::bind(&C::Square, std::placeholders::_1);
    std::cout << "Square function result below:" << std::endl;
    print(function_wrapper, 2.0);



//PART B: Bind the function wrapper to C’s member functions using std::bind and placeholders.
//Note: in translate() and translate2(), _data member data is required, and thus requires a C class instance.
//      On that note, we need to bind
    
    //C class instance with _data member data = 1.11
    C c1{1.11}; 

    //Function wrapper for C::translate2(). I could obviously plug-in fixed values instead of placeholders
    function_wrapper = std::bind(&C::translate, &c1, std::placeholders::_1);
    print(function_wrapper, 1.11);  //Calls f(1.11) where f() is C::translate()


    //Function wrapper for C::translate2(). I could obviously plug-in fixed values instead of placeholders
    function_wrapper = std::bind(&C::translate2, &c1, std::placeholders::_1, 3.33);
    print(function_wrapper, 1.11);  //Calls f(1.11, 3.33), where f() is C::translate2()
    
    //Not possible: function_wrapper = std::bind(&C::translate2, &c1, std::placeholders::_1, std::placeholders::_2);
    //Because print() functions only takes one argument t in f(t), and thus we would have to redefine f(t) with variadics

    return 0;
}