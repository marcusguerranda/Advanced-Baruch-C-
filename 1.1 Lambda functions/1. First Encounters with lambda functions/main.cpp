//1.1 Lambda functions
//1. First encounters with lambda functions
//Author: Andrew Guerrand

//Purpose: we concentrate on defining lambda functions that process vectors of double precision numbers (or integers) in various ways.

//Modification date: 4/5/2023


#include <iostream>
#include <vector>
#include <algorithm>



//Global function which enables us to print elements in vector container.
//I use auto specifier, as required by part b) in 1.1
template <typename T> 
void print_vector(const std::vector<T>& source_vector)
{
    for(auto& i : source_vector)  
    {
        std::cout << i << std::endl;
    }
}


template <typename T1, typename T2>
void print_pair(const std::pair<T1, T2>& source_pair)
{
    std::cout << "[" << source_pair.first << ", " << source_pair.second << "]" << std::endl;
    //Or alternatively could use std::get<0>(source_pair) and std::get<1>(source_pair)
}

//Mechanical approach to finding the min and max elements in a vector
template <typename T>
auto calculate_MinMaxMechanical = [] (const std::vector<T>& source_vector)
{
    if(source_vector.empty()){
        throw std::out_of_range("Source vector is empty");
    }

    T min_element = source_vector[0];
    T max_element = source_vector[0];

    for(const auto& element: source_vector)
    {
        if(element < min_element) { min_element = element;}
        if(element > max_element) { max_element = element;}
    }

    return std::make_pair(min_element, max_element);
};



//Return type (-> std::pair<T1, T2>) is deduced by the calling of the std::make_pair function 
//WITHOUT USING std::minmax_element
template <typename T>
auto calculate_MinMaxNoStd = [](const std::vector<T>& source_vector) 
{
    if (source_vector.empty()) {
        throw std::out_of_range("Source vector is empty");
    }

    auto min_element = std::min_element(source_vector.begin(), source_vector.end());    //std::min_element and std::max_element in <algorithm> header
    auto max_element = std::max_element(source_vector.begin(), source_vector.end());
    return std::make_pair(*min_element, *max_element);
};

//Using std::minmax_element
template <typename T>
auto calculate_MinMaxStd = [](const std::vector<T>& source_vector)   
{
    if (source_vector.empty()) {
        throw std::out_of_range("Source vector is empty");
    }

    auto [min_element, max_element] = std::minmax_element(source_vector.begin(), source_vector.end());
    return std::make_pair(*min_element, *max_element);
};


int main()
{

//PART A. 

    //Alternative initialization: double vector1[5] = {2.2, 3.3, 4.4, 5.5, 6.6};
    std::vector<double> vector1 = {2.2, 3.3, 4.4, 5.5, 6.6};  //Creating an vector of 5 integer elements using STL vector container
    std::vector<double> vector2(vector1);                     //Second vector using default copy constructor // I AM NOT USING MOVE CONSTRUCTORS YET
    double multiplier = 4.0;                                  //Multiply each element in vector by this number, which will be captured in lambda function
    
    //PRINTING vectorS PRIOR TO CALLING LAMBDAS:
    std::cout << "ORIGINAL VECTORS 1 and 2" << std::endl;
    std::cout << "Vector 1" << std::endl;
    print_vector(vector1);

    std::cout << "Vector 2" << std::endl;
    print_vector(vector2);


    //COPY-BY-VALUE.
    //Could alternatively be [&multiplier], as we capturing only one variable; I specify the return type here although there is only one in this instance
    //APalley requires defining the lambda function by creating a function object, rather than doing so inline

    //INLINE: std::for_each(vector1.begin(), vector1.end(), [&](double element) -> double {return element *= multiplier;});    
    auto f1= [&](double element) -> double {return element *= multiplier;};
    std::for_each(vector1.begin(), vector1.end(), f1);


    //COPY-BY-REFERENCE

    //INLINE: std::for_each(vector2.begin(), vector2.end(), [&](double& element) -> double {return element *= multiplier;});
    auto f2 = [&](double& element) -> double {return element *= multiplier;};
    std::for_each(vector2.begin(), vector2.end(), f2);



//PART B.
    std::cout << "TRANSFORMED vector 1, by value. (it will be identical to original one)" << std::endl;
    print_vector(vector1);
    std::cout << "TRANSFORMED vector, by reference." << std::endl;
    print_vector(vector2);


//PART C: lambda function to find min and max within a vector using std::min_element and std::max_element

    std::cout << "NOT Using std::minmax_element but std::min_element and std::max_element approach!" << std::endl;

    auto result_vector1 = calculate_MinMaxNoStd<double>(vector1);       //Vector 1 is untransformed, whereas vector2 is transformed.
    auto result_vector2 = calculate_MinMaxNoStd<double>(vector2);       //Vector 2 is transformed

    print_pair(result_vector1);
    print_pair(result_vector2);

    //Using mechanical approach to the computation of min and max elements in a vector

    std::cout << "NOT Using std::minmax_element but MECHANICAL approach!" << std::endl;
    auto result_vector3 = calculate_MinMaxNoStd<double>(vector1);       //Vector 1 is untransformed: using MECHANICAL approach
    auto result_vector4 = calculate_MinMaxMechanical<double>(vector2);  //Vector2 is transformed: using MECHANICAL approach

    print_pair(result_vector3);
    print_pair(result_vector4);

//PART D: using std::minmax_element

    std::cout << "Using std::minmax_element !" << std::endl;

    auto result_vector5 = calculate_MinMaxStd<double>(vector1); //Vector 1 is untransformed, whereas vector2 is transformed.
    auto result_vector6 = calculate_MinMaxStd<double>(vector2); //Vector 2 is transformed,

/*
    IMPORTANT: 

    In this instance, I decided to create a lambda function 'calculate_MinMaxStd'.
    I could have also simply done the following, but would then need to write this implementation every time.

    auto [min, max] = std::minmax_element(vector1.begin(), vector1.end());
    std::cout << "[" << *min << ", " << *max << std::endl;
*/
    
    print_pair(result_vector5);
    print_pair(result_vector6);

/*Comment: 

- I have also added a mechanical implementation of the min max function without using std::min_element and std::max_element. 
- In terms of reuse of the code, what I could point out is that I could also bring it to a higher level of abstraction by calling a templated container 
  rather than taking specifically vectors to find the min and max elements. In as, I would use template <typename T> and then 
  "auto calculate_MinMaxNoStd = [](const T& source_container).
  Overall, however, I do get the same output, and std::minmax_element is more concise than the alternative implementations in 1.1.c) .

*/


    return 0;
};