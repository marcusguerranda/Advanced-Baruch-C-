//4.2.5) Which style to use?

/*Purpose:  Some STL algorithms need unary and binary predicates. Both types return a Boolean. A unary predicate 
            has one input argument while a binary predicate has two input argument. We can model these predicates 
            and other kinds of functions in a number of ways:
                - User-defined function objects.
                - Predefined STL function objects (for example, std::multiplies<T>()).
                - Using lambda functions (possibly with captured variables)
*/

//Author: Andrew Guerrand

//Modification dates: 7/2/2023

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <cstdlib>
#include <functional>

//Printer function to print elements from set
template <typename T>
void Printer(const std::set<T>& source_set){
    for(const auto& elem: source_set){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


//User-defined global function returning bool whether absolute value is greater than 2
bool user_defined_comparator(const int& element)
{
    return (element>2 || element<-2);
}

//Same as above but taking two input arguments
bool user_defined_comparator2(const int& element, const int& threshold)
{
    return (element>threshold || element<(-threshold));
}


int main()
{
    std::cout << std::endl;
//PART B)   Consider the case of transforming a vector of integers into a set of integers. Only those elements 
//          whose absolute value is strictly greater than a given threshold value. An example is the vector 
//          {1,2,1,4,5,5,-1} . If the threshold value is 2 then the output set will be {4,5}. Implement this 
//          problem using the three bespoke methods.

    std::vector<int> vec{1,2,1,4,5,5,-1};

//User-defined object: UNARY
    std::set<int> result1;
    for(auto& elem: vec){
        if(user_defined_comparator(elem)){result1.insert(elem);}
    }

    std::cout << "Elements in set 'result1', using a global user-defined function with unary predicate are: "; Printer(result1);

//User-defined object: BINARY
    std::set<int> result2;
    for(auto& elem: vec){
        if(user_defined_comparator2(elem, 2)){result2.insert(elem);}
    }

    std::cout << "Elements in set 'result2', using a global user-defined function with binary predicate are: "; Printer(result2);

    
//Predefined STL function objects
    //Copy vector 'vec' so as to not alter the original vector
    std::vector<int> vec2(vec);

    //Remove elements less than or equal to the threshold
    vec2.erase(std::remove_if(vec2.begin(), vec2.end(), std::bind(std::less_equal<int>(), std::placeholders::_1, 2)), vec2.end());

    //Create a set 'result3' from the remaining elements
    std::set<int> result3(vec2.begin(), vec2.end());

    //Print elements
    std::cout << "Elements in set 'result3', using STL functions are: "; Printer(result3);

//Lambda function
    std::set<int> result4;
    for (const auto& elem : vec){
        auto lambda = [](const int& elem) { return (elem < -2 || elem > 2); };
        if (lambda(elem)) {
            result4.insert(elem);
        }
    }

    //Print elements
    std::cout << "Elements in set 'result4', using lambda function is: "; Printer(result4);

//PART C)   Having developed and debugged the code in part b) review the three solutions from the perspective of 
//          understandability, maintainability and efficiency.

    //Lambda easier to use than STL functions. Global free functions work too, but defeat the purpose of using lambdas...

    std::cout << std::endl;
    return 0;
}