//main.cpp

//Purpose: Fundamentals of variadics: create a variadic print function that supports overloading of the standard output stream

//Author: Andrew Guerrand

//Modification date: 4/10/2023

#include <iostream>
#include <bitset>

/*Remarks:
When I define the tail function void print() without any template parameters, the function can only match an empty parameter pack, 
and it is called only when no arguments are passed to the print function. Output I got below:

        Variadic
        1, Tail function of print function used and called last.
        Variadic
        2, Tail function of print function used and called last.
        Variadic
        1, Variadic
        2, Tail function of print function used and called last.
        Variadic
        2, Variadic
        1, Tail function of print function used and called last.

        With 3 parameters:

        Variadic
        2, Variadic
        1, Variadic
        11101001, Tail function of print function used and called last.

I can see here that even with only one argument, the variadic function is called. This seems anodyne, but such is not the case if I define
an additional templated one-argument print tail function. In such a case, the latter function would be called for the very last element in 
any container, and not called when all parameters have been unpacked. I believe doing so is counterintuitive to the purpose of variadic 
functions themselves.

As such, I have commented out the templated "template <typename T> void print(T arg)" function. BELOW ARE THE UNPACKING OF EACH SPECIFIC FUNCTIONS USING
CPPINSIGHTS !


template <typename T>
void print(T arg) 
{
    std::cout << arg << std::endl;
    std::cout << "Tail function 1 of print function used and called last." << std::endl;
};*/

void print() 
{
    std::cout << "Tail function of print function used and called last." << std::endl;
};

template <typename T, typename... Args>                    // '...' == parameter pack
void print(const T& arg1, const Args& ... args)            // '...' parameters are unpacked.
{
    //std::cout << "Variadic" << std::endl;
    std::cout << arg1 << ", ";
    print(args ...);                    //Unpacking arguments
};


int main()
{
    // Variadic function templates
    int j = 1; double d = 2.0;
    print(j);                           //Tail function called
    print(d);                           //Tail function called
    print(j, d);                        //Variadic function called for j, then tail function called for d
    print(d, j);                        //Variadic function called for d, then tail function called for j            
    
    std::cout << "\n With 3 parameters: \n \n";
    print(d, j, std::bitset<8>(233));   //Variadic function called for d, and j. Tail function called for std::bitset<8>(233)
}




/*

First instantiated from: insights.cpp:68
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void print<int>(const int & arg1)
{
  std::operator<<(std::cout, "Variadic").operator<<(std::endl);
  std::operator<<(std::cout.operator<<(arg1), ", ");
  print();
}
#endif


First instantiated from: insights.cpp:69 
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void print<double>(const double & arg1)
{
  std::operator<<(std::cout, "Variadic").operator<<(std::endl);
  std::operator<<(std::cout.operator<<(arg1), ", ");
  print();
}
#endif


First instantiated from: insights.cpp:70
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void print<int, double>(const int & arg1, const double & __args1)
{
  std::operator<<(std::cout, "Variadic").operator<<(std::endl);
  std::operator<<(std::cout.operator<<(arg1), ", ");
  print(__args1);
}
#endif


First instantiated from: insights.cpp:71 
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void print<double, int>(const double & arg1, const int & __args1)
{
  std::operator<<(std::cout, "Variadic").operator<<(std::endl);
  std::operator<<(std::cout.operator<<(arg1), ", ");
  print(__args1);
}
#endif


First instantiated from: insights.cpp:74 
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void print<double, int, std::bitset<8> >(const double & arg1, const int & __args1, const std::bitset<8> & __args2)
{
  std::operator<<(std::cout, "Variadic").operator<<(std::endl);
  std::operator<<(std::cout.operator<<(arg1), ", ");
  print(__args1, __args2);
}
#endif


First instantiated from: insights.cpp:60 
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void print<int, std::bitset<8> >(const int & arg1, const std::bitset<8> & __args1)
{
  std::operator<<(std::cout, "Variadic").operator<<(std::endl);
  std::operator<<(std::cout.operator<<(arg1), ", ");
  print(__args1);
}
#endif


First instantiated from: insights.cpp:60 
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void print<std::bitset<8> >(const std::bitset<8> & arg1)
{
  std::operator<<(std::cout, "Variadic").operator<<(std::endl);
  std::operator<<(std::operator<<(std::cout, arg1), ", ");
  print();
}
#endif


*/