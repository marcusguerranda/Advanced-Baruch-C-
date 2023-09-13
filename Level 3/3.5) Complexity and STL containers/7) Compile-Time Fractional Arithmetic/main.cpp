//3.5) C++ Complexity

/*Purpose:  This exercise is based on std::ratio, a class template that supports rational arithmetic. It reduces the 
            risk of run-time overflow because a ratio and any ratios resulting from ratio arithmetic are always reduced 
            to the lowest terms. 
*/
//Author: Andrew Guerrand

//Modification dates: 6/20/2023

//SEE BELOW FOR PERSONAL NOTES ON STD::RATIO

#include <iostream>
#include <ratio>

int main()
{

//PART A) Create a number of instances of std::ratio and print them.
    typedef std::ratio<1, 3> ratio1;
    typedef std::ratio<3, 4> ratio2;

    //Now starts the fun... 
    std::ratio<1, 1000000000000000000> atto;    //(10^-18)
    std::ratio<1, 1000000000000000> femto;      //(10^-15)
    std::ratio<1, 1000000000000> pico;          //(10^-12)
    std::ratio<1, 1000000000> nano;             //(10^-9)
    std::ratio<1, 1000000> micro;               //(10^-6)
    std::ratio<1, 1000> milli;                  //(10^-3)
    std::ratio<1, 100> centi;                   //(10^-2)
    std::ratio<1, 10> deci;                     //(10^-1)
    std::ratio<10, 1> deca;                     //(10^1)
    std::ratio<100, 1> hecto;                   //(10^2)
    std::ratio<1000, 1> kilo;                   //(10^3)

    //Printing one randomly
    std::cout << "Sherlock, what is the ratio of femto? It is: " << femto.num << "/" << femto.den << std::endl;

//PART B) Create two std::ratio instances; add, subtract, multiply and divide them.
    //IMPORTANT: type	std::ratio<num, den>

    typedef std::ratio_add<ratio1, ratio2> sum;             //Addition typedef
    typedef std::ratio_subtract<ratio1, ratio2> difference; //Substraction
    typedef std::ratio_multiply<ratio1, ratio2> product;    //Multiplication
    typedef std::ratio_divide<ratio1, ratio2> quotient;     //Division

    std::cout << "Sum: " << sum::num << "/" << sum::den << std::endl;
    std::cout << "Difference: " << difference::num << "/" << difference::den << std::endl;
    std::cout << "Product: " << product::num << "/" << product::den << std::endl;
    std::cout << "Quotient: " << quotient::num << "/" << quotient::den << std::endl;

    return 0;
}

/*              STD::RATIO


template <std::intmax_t NUMERATOR, std::intmax_t DENOMINATOR> 
class ratio;


The class template std::ratio provides compile-time rational arithmetic support. Each instantiation of this template exactly represents any finite 
rational number as long as its numerator Num and denominator Denom are representable as compile-time constants of type std::intmax_t. 
In addition, Denom may not be zero and both Num and Denom may not be equal to the most negative value.

*/