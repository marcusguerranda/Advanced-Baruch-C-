//1.1.2 Comparing lambda functions with function objects and free functions
//Author: Andrew Guerrand

//Purpose: Examine the application of lambda functions in C++. We look at std::accumulate 

//Modification date: 4/5/2023


#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>
#include <complex> //to use std::complex. Note for self: go see all down below on how to further use template class.
#include <iterator>

// Using complex numbers
using Complex = std::complex<double>;


//Note to self: std::accumulate is part of <numeric> header file.
//              std::multiplies is part of <functional> header file.
//              std::complex is part of <complex> header file

//Generic lambda function
auto MyMultiply = [] (auto x, auto y) { return x*y ;};


//Struct and generic function
//Note to self: by defining this as a struct instead of a function, it can be used in contexts that require an object, such as with function 
//              templates that expect functions objects as arguments. This can be useful in generic algorithms like "std::transform", where you
//              can provide your own function object to perform the transformation operation.
struct FOMultiply
{
    //The operator() is an overloaded function call operator that allows objects of the 'FOMultiply' type to be called like functions.
    //When I use FOMultiply with the std::accumulate function, it calls the operator() function of FOMultiply for each element in the 
    //range being accumulated, passing the current accumulated value and the current element as arguments. The operator() function multiplies
    //the two values and returns the result, which is then used as the accumulated value for the next element in the range. 

    template <typename T>
    T operator () (const T& x, const T& y) 
    { 
        return x * y; 
    }
};

//Given MyMultiply2 function
template <typename T>
T MyMultiply2(const T& x, const T& y) { return x*y; };


//Print function to print the contents in a container such as a vector
template <typename Container>
void print(const Container& source)
{
    std::copy(source.begin(), source.end(), std::ostream_iterator<typename Container::value_type>(std::cout, " "));
    std::cout << std::endl;
}



int main()
{
//PART A: Impllement and test the algorithm using the generic lambda

    //A vector of integers
    std::vector<int> vec {1,2,3,4,5};
    int initVal = 1;                    //Initial value from which we start our accumulation summation

    //A vector of two complex numbers
    std::vector<Complex> complexArray{Complex(1.0, 1.0), Complex(2.0, 2.0)};   
    Complex initCVal(1.0, 1.0);         //Initial value  (complex) to try out std::accumulate 



    //Accumulating with defined lambda function MyMultiply
    int acc_MyMultiply = std::accumulate (vec.begin(), vec.end(), initVal, MyMultiply);
    
    //Accumulating using standard std::multiplies function
    int acc_std = std::accumulate(vec.begin(), vec.end(), initVal, std::multiplies<int>());    //USES std::multiplies part of <functional> library
    
    //Accumulating using function object 
    int acc_FOMultiply = std::accumulate(vec.begin(), vec.end(), initVal, FOMultiply());

    //Printing out results
    std::cout << "Sum using lambda function: " << acc_MyMultiply << "\n Sum using std::multiplies: " << acc_std << "\n Sum using generic function: " 
    << acc_FOMultiply << std::endl;

/*
Remarks:
- In terms of functionality, there is no difference between the lambda function, the function object using a struct, 
  and std::multiplies. All three can be used to perform multiplication on two values of the same type.

- The main difference between them is the syntax and how they are used in different contexts. 

- The advantage of using a function object defined using a struct over a lambda function is that it can be used in 
  contexts that require an object, such as with function templates that expect function objects as arguments. This 
  can be useful in generic algorithms like std::transform, where you can provide your own function object to perform 
  the transformation operation
*/

    //WITH COMPLEX NUMBERS NOW:

    auto accC_MyMultiply = std::accumulate (complexArray.begin(), complexArray.end(), initCVal, MyMultiply);
    std::cout << "Sum complex numbers, using MyMultiply() and complexArray." << accC_MyMultiply << std::endl;

    auto accC_FOMultiply = std::accumulate(complexArray.begin(), complexArray.end(), initCVal, FOMultiply());
    std::cout << "Sum complex numbers, using FOMultiply() and complexArray." << accC_FOMultiply << std::endl;

    auto accC_std = std::accumulate (complexArray.begin(), complexArray.end(), initCVal, std::multiplies<std::complex<double>>());
    std::cout << "Sum complex numbers, using std::multiplies() and complexArray." << accC_std << std::endl;

    Complex accC_now = std::accumulate (complexArray.begin(), complexArray.end(), initCVal, MyMultiply2<Complex>);
    std::cout << "Sum complex numbers, using MyMultiply2<Complex>() and complexArray." << accC_now << std::endl;

/*
Remark:
    It seems like whether I use the lambda function, the generic function, the std::multiplies<std::complex<double>>, or MyMultiply2, 
    I get the same result and that complex numbers are supported. We can also use function objects.

*/



//*********************************************************************************************************************************


//PART B: Implementing the std::accumulate accumulation algorithm using an embedded lambda function in combination with std::for_each
//        and captured variables

//Implementation of the accumulate function without using std::accumulate, but rather using std::for_each

// ADDITION

    //vec defined line 66 as:     std::vector<int> vec {1,2,3,4,5};
    //For simple integers in vec example:
    auto sum_int = 0.0;
    std::for_each(vec.begin(), vec.end(), [&](const auto& elements) {sum_int += elements;});


    //For complex numbers in complexArray example:
    Complex sum_complex(0.0, 0.0);
    std::for_each(complexArray.begin(), complexArray.end(), [&](const auto& elements) {sum_complex += elements;}); 

    std::cout << "Sum of vec elements using std::for_each: " << sum_int << std::endl;
    std::cout << "Sum of complexArray complex numbers using std::for_each: " << sum_complex << std::endl; 

// MULTIPLICATION

    //For simple integers in vec example:

    int product_int = initVal;
    std::for_each(vec.begin(), vec.end(), [&](const auto& elements) {product_int *= elements;});


    //For complex numbers in complexArray example:
    Complex product_complex = initCVal;
    std::for_each(complexArray.begin(), complexArray.end(), [&](const auto& elements) {product_complex *= elements;}); 

    std::cout << "Multiplication of vec elements using std::for_each: " << product_int << std::endl;
    std::cout << "Multiplication of complexArray complex numbers using std::for_each: " << product_complex << std::endl;


//*********************************************************************************************************************************

//PART C:

/*
Multiple examples can be provided, using std::copy_if, std::transform, std::sort, and std::find_if
I'll implement all of these, as I believe they may come in handy in the future.
*/

//std::copy_if:
    auto MyEven = [] (const int& x) { return x % 2 == 0; };

    std::vector<int> evenNumbers; //New vector created, where I will insert even numbers using MyPredicate function 
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(evenNumbers), MyEven);
    print(evenNumbers);

//std::transform
    auto MyTransform = [](const int& x) {return x*2;};
    std::transform(vec.begin(), vec.end(), vec.begin(), MyTransform);
    print(vec);

//std::sort
    //Reverse order of elements being compared
    //Initializing vec_descending with the elements of the vec vector. It uses the constructor of std::vector that takes two iterators as arguments
    std::vector<int> vec_descending(vec.begin(), vec.end());    
    auto MyOrder = [] (const int& a, const int& b){return a > b;};
    std::sort(vec_descending.begin(), vec_descending.end(), MyOrder); 
    print(vec_descending);
    
    return 0;
}



//Review/Reflection -> when to use lambda over a function object
/*
When using lambda functions over function objects, I need to evaluate the circumstance in which I am doing so. 
COMPLEXITY: if the function is small and only used in one place, a lambda function is most likely preferred over a separate function.
TYPE: lambdas are particularly useful when working with generic algorithms that accept function objects, as they provide a way to create 
      a function object "on the fly" without having to define a separate class.

*/






/*      std::complex, in <complex> header file

std::complex is a C++ Standard Library template class that represents a complex number, consisting of a real part and an imaginary part.
Defining complex numbers can be done as such:

    std::complex<double> z1(1.0, 2.0);  // Define a complex number with real part 1.0 and imaginary part 2.0
    std::complex<double> z2(2.0, -1.0); // Define another complex number with real part 2.0 and imaginary part -1.0

*/
