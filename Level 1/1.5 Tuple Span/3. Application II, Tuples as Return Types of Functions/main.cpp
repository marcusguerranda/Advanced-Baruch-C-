
//main.cpp

//Purpose: Application II, tuples as return types of functions

//Author: Andrew Guerrand

//Modification date: 4/13/2023


#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <boost/numeric/ublas/vector.hpp>
#include <unordered_map>



//Templated structure which calls two functions:
//  -> CalculateA (for PART A calculations) returns the mean, mean deviation, range, stand dev and variance of the elements within a numeric vector
//  -> CalculateC (for PART C calculations) returns the median of a sorted vector, and the mode 

//  typename T for the type of data at hand: float, double, int, etc.
//  typename Vector to handle two cases: namely std::vector and boost::numeric::ublas::vector
//  typename Tuple to define what tuple will be outputed: example -> std::tuple<double, double, double, double, double, ...>

template <typename T, typename Vector, typename Tuple>
struct Statistical_Properties
{
    //PART ACalculateA() is a static member function which calculates relevant statistics for a given vector (mean, mean deviation, range, std.dev, variance)
    static Tuple CalculateA(const Vector& source_vector) 
    {
        //Checking whether source_vector is empty
        if (source_vector.size() == 0) {throw std::runtime_error("Error: vector is empty");}

        else
        {
            //MEAN of the elements in the vector (Sum/ # elements)
            T vector_Mean = (std::accumulate(source_vector.begin(), source_vector.end(), 0.0)) / static_cast<T>(source_vector.size());

            //Comment: mean deviation and variance require both the computation of the difference between the mean and each element. For  
            // performance reasons, I believe it would make sense to store these differences into a vector, and use these for our relevant computations.
            
            //Create vector where I will store the differences
            Vector DeviationsFromMean(source_vector.size());    
            //std::transform with lambda function computing the absolute differences (it is both convenient for the mean deviation, and variance/std dev)
            std::transform(source_vector.begin(), source_vector.end(), DeviationsFromMean.begin(), 
            [=](const T& elements){return std::abs(elements - vector_Mean);});  

            //MEAN DEVIATION calculation (as the mean of absolute differences between each element and the mean of the vector)
            T vector_MeanDeviation = std::accumulate(DeviationsFromMean.begin(), DeviationsFromMean.end(), 0.0)/static_cast<T>(source_vector.size());

            //VARIANCE
            /* ALTERNATIVE 1:
                // SQUARE DEVIATIONS FROM MEAN calculation
                std::transform(DeviationsFromMean.begin(), DeviationsFromMean.end(), DeviationsFromMean.begin(),
                            [](const T& element) { return element * element; }); //square each element of DeviationsFromMean

                // VARIANCE calculation
                T vector_Variance = std::accumulate(DeviationsFromMean.begin(), DeviationsFromMean.end(), T{}) / static_cast<T>(source_vector.size());*/
            
            // ALTERNATIVE 2:
            //I eventually came across std::inner_product when looking into the <numeric> header file. Much more convenient here...
            T vector_Variance = (std::inner_product(DeviationsFromMean.begin(), DeviationsFromMean.end(), DeviationsFromMean.begin(), 0.0)) / static_cast<T>(DeviationsFromMean.size());

            //STANDARD DEVIATION:
            T vector_StandardDev = std::sqrt(vector_Variance);

            //Range (std::pair will be called up)
            auto minmax = std::minmax_element(source_vector.begin(), source_vector.end());
            T vector_Range = *minmax.second - *minmax.first;

            //Returning a tuple of the statistics of interest
            return std::make_tuple(vector_Mean, vector_MeanDeviation, vector_Range, vector_Variance, vector_StandardDev);
        }
    };


    //PART C function returning a tuple consisting of a median of a sorted vector and a mode
    static Tuple CalculateC(const Vector& source_vector)
    {
        //Checking whether source_vector is empty
        if (source_vector.size() == 0) {throw std::runtime_error("Error: vector is empty");}

        //Check whether vector is sorted or not. If not then sort it
        if (!std::is_sorted(source_vector.begin(), source_vector.end()))
        {
            Vector sorted_vector = source_vector;
            std::sort(sorted_vector.begin(), sorted_vector.end());
            return CalculateC(sorted_vector);
        }

        //MEDIAN
        T vector_Median;
        if (source_vector.size() % 2 == 0)
        {
            //Even number of elements, compute arithmetic mean of middle two elements
            size_t middle = source_vector.size() / 2;
            vector_Median = (source_vector[middle] + source_vector[middle + 1]) / 2.0;
        }
        else
        {
            //Odd number of elements, take middle element
            size_t middle = source_vector.size() / 2;
            vector_Median = source_vector[middle];
        }

        //MODE
        //NOTE: If there are two modes with the same frequency, the one with the smaller value will be 
        //      assigned to vector_Mode since it is encountered first in the unordered map.
        std::unordered_map<double, size_t> frequencies;
        for (const auto& elements : source_vector)
        {
            frequencies[elements]++;
        }
        T vector_Mode = 0;
        size_t max_frequency = 0;
        T smallest_mode_value = std::numeric_limits<T>::max(); // Initialize to largest possible value
        for (const auto& [value, frequency] : frequencies)
        {
        if (frequency > max_frequency)
        {
            max_frequency = frequency;
            vector_Mode = value;
            smallest_mode_value = value;
        }
        else if (frequency == max_frequency && value < smallest_mode_value)
        {
            smallest_mode_value = value;
            vector_Mode = value;
        }
    }

        //Use std::ignore to discard the unused elements in the tuple
        if constexpr (std::tuple_size_v<Tuple> == 2) {
            return std::make_tuple(vector_Median, vector_Mode);
        } else if constexpr (std::tuple_size_v<Tuple> == 5) {
            return std::make_tuple(vector_Median, vector_Mode, 0.0, 0.0, 0.0);
        }
    };
};


//TUPLE PRINT function to print out tuple results
template<typename Tuple>
void printStatistics(const Tuple& stats_tuple)
{
    //std::tuple_size<Tuple> will calculate the size of the tuple
    static_assert(std::tuple_size<Tuple>::value > 0, "Error: tuple is empty");   //See below on notes for std::logic_error 
    std::cout << "\nMean: " << std::get<0>(stats_tuple) 
              << "\nMean deviation: " << std::get<1>(stats_tuple)
              << "\nRange: " << std::get<2>(stats_tuple)
              << "\nVariance: " << std::get<3>(stats_tuple)
              << "\nStandard deviation: " << std::get<4>(stats_tuple) << "\n" << std::endl;
};



int main()
{

//PART A: testing out the code


//STD::VECTOR

    std::vector<double> emptyVector;    //Empty vector
    std::vector<double> vector1{1.2, 3.2, 10, 34.1, 22.2, 56.3, 1, 3, 5, 7};
    
    using doubleTuple = std::tuple<double,double,double,double,double>;

    //doubleTuple emptystats = Statistical_Properties<double, std::vector<double>, doubleTuple>::Calculate(emptyVector);
    //WILL THROW AN ERROR, GIVEN THE VECTOR IS EMPTY. My error guards work.
    
    doubleTuple stats1 = Statistical_Properties<double, std::vector<double>, doubleTuple>::CalculateA(vector1);
    printStatistics(stats1);


//BOOST::NUMERIC::UBLAS::VECTOR

    boost::numeric::ublas::vector<double> vector2(10);
    //NOTE TO SELF: brace initialization in boost::numeric::ublas::vector is not allowed as the {} operator is not defined... 
    //I have tried multiple different ways and this seems to be one of the few
	for (int i=0; i < vector2.size(); ++i) 
    {
		vector2[i] = static_cast<double>(i)*2;      // 0, 2, 4, 6, 8, ....
	};

    doubleTuple stats2 = Statistical_Properties<double, boost::numeric::ublas::vector<double>, doubleTuple>::CalculateA(vector2);
    printStatistics(stats2);

//PART B: using std::tie and std::ignore

    double mean, meandv, range, variance, stddv;    
    std::tie(mean, meandv, range, variance, stddv) = stats2;    //Tieing statistics for vector2 
    //NOTE TO SELF: SEE MORE ON STD::TIE BELOW

    std::cout << "For vector 2, I will reprint all statistics but with the std::tie that ties stats into a tuple of reference.\n" 
    << "Mean: " << mean << "\nMean deviation: " << meandv << "\nRange: " << range << "\nVariance: " << variance << "\nStandard Deviation: "
    << stddv << std::endl;

    //Using std::ignore just for the sake of it
    std::tie(mean, std::ignore, range, std::ignore, stddv) = stats1;  //Tieing certain elements of tuple from stats1
    std::cout << "\nSTATS1 using std::tie, generating a tuple of references:\nMean: " << mean << "\nRange: " << range << "\nStandard deviation: " 
    << stddv << std::endl;



//PART C: Computations of the median and mode of a sorted vector

    //Testing on empty vector will throw an error, as anticipated
    //doubleTuple stats3 = Statistical_Properties<double, std::vector<double>, doubleTuple>::CalculateC(vector1);

    double median, mode;    //Declaring median and mode as double values
    doubleTuple stats3 = Statistical_Properties<double, std::vector<double>, doubleTuple>::CalculateC(vector1);

    //Since doubleTuple is defined as: std::tuple<double,double,double,double,double>;
    std::tie(median, mode, std::ignore,std::ignore,std::ignore) = stats3;    

    std::cout << "\nThe median for vector1, using CalculateC() is: " << median << ", and the mode (minimizing for the value if there are multiple numbers with the same frequency) is: " << mode << std::endl;



    //Testing for boost::numeric::ublas::vector   vector2, which has already been defined
    doubleTuple stats4 = Statistical_Properties<double, boost::numeric::ublas::vector<double>, doubleTuple>::CalculateC(vector2);

    //Since doubleTuple is defined as: std::tuple<double,double,double,double,double>;
    std::tie(median, mode, std::ignore,std::ignore,std::ignore) = stats4;

    std::cout << "\nThe median for vector2, using CalculateC() is: " << median << ", and the mode (minimizing for the value if there are multiple numbers with the same frequency) is: " << mode << std::endl;

    return 0;
};










/*
Answer the following questions:

    a) Create a function that returns the following statistical properties of a numeric vector as a tuple: 
    -mean, 
    -mean deviation, 
    -range (the difference between the largest and smallest numbers in the vector), 
    -standard deviation and 
    -variance.

    b) Test the function from part a). In order to make the code more readable you can use tied variables and 
    std::ignore.

    c) Write a function that computes the median of a sorted vector (the median is either the middle value or 
    the arithmetic mean of the two middle values) and the mode which is the value that occurs with the 
    greatest frequency.
        When there are two or more values that are candidates to be the mode, then the smallest value will be 
        chosen. For example, the time between eruptions of Old Faithful geyser (in minutes, to nearest 
        minute) on 1 August 1978 were: {78,74,68,76,80,84,50, 93,55,76,58,74,75}. Both values 74 and 76 are 
        candidates for mode, so we choose the smaller value, namely 74.
*/



/*  std::logic_error

It is an error thrown when a function is called with arguments that violate the function's preconditions,
or in cases where the function is called when it is not expected to be called.
*/



/*  std::tie

    std::tie is a function template in C++ that creates a tuple of references. The function takes a number of lvalue references 
    as arguments and returns a tuple of references to those arguments.
*/




