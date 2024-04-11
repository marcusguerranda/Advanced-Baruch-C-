//4.2.4) Nonmodifying algorithms

//Purpose: Using some non-modifying algorithms

//Author: Andrew Guerrand

//Modification dates: 7/2/2023



#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <limits>
#include <tuple>
#include <functional>


//PART B: computing minimum, maximum, sum, and average of the values of the elements in a container of numeric values. The output is a tuple with four fields
template <typename T>
std::tuple<T, T, T, double> Statistics(const std::vector<T>& source) 
{
    //Minimum element
    T min = *std::min_element(source.begin(), source.end());

    //Maximum element
    T max = *std::max_element(source.begin(), source.end());

    //Sum of elements
    T sum = std::accumulate(source.begin(), source.end(), T(0));

    //Average
    double average = static_cast<double>(sum) / source.size();

    return std::make_tuple(min, max, sum, average);
}


int main()
{
/*QUESTION A:   Count the frequency of each value in a container. For example, for {1,2,4,5,4,1} we get the output 
                {{1,2}, {2,1}, {4,2}, {5,1}}. There are different ways to model the output depending on your 
                requirements.
*/

    std::vector<int> vec1(100);

    //Generate random values between 1 and 50
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 50);

    std::generate(vec1.begin(), vec1.end(), [&]() {return distribution(generator);});

    std::unordered_map<int, int> frequencies_map;   //Create an unordered map to store frequencies
    std::vector<std::pair<int, int>> vector_pairs;  //Construct the output structure

    //Count frequencies
    for (const auto& elem : vec1) 
    {
        frequencies_map[elem]++;
    }

    //Constructing output structure
    std::vector<std::pair<int, int>> output;

    for (const auto& entry : frequencies_map) 
    {
        output.emplace_back(entry.first, entry.second);
    }

    //Print stored outputs
    for (const auto& pair : output) 
    {
        std::cout << "{" << pair.first << "," << pair.second << "} ";
    }
    std::cout << std::endl;

//QUESTION B:

    std::tuple<int,int,int, double> results1 = Statistics(vec1);
    std::cout << "\nMinimum in vec1 is: " << std::get<0>(results1) << ", max is: " << std::get<1>(results1) << ", sum is: " 
    << std::get<2>(results1) << ", and avg: " << std::get<3>(results1) << std::endl;

/*QUESTION C:   Consider the container S = {1,2,-3,4,5,5,5,6}. Use an STL algorithm to find the first occurrence of the 
                value 5. Now use:
                - std::bind2nd()
                - std::bind()
                - Lambda expression
                    to find the position of the first even number in S.
*/

    std::vector<int> container{1,2,-3,4,5,5,5,6};

//Using STL algorithm
    auto it = std::find(container.begin(), container.end(), 5);
    if (it != container.end()) std::cout << "First occurrence of value 5 found at index: " << std::distance(container.begin(), it) << std::endl;
    else {std::cout << "Value 5 not found in vector" << std::endl;}

//Using std::bind2nd()

/*  DEPRECATED!
    auto it2 = std::find_if(container.begin(), container.end(), std::bind2nd(std::equal_to<int>(), 5));
    if (it2 != container.end())std::cout << "First occurrence of value 5 found at index: " << std::distance(container.begin(), it2) << std::endl;
    else {std::cout << "Value 5 not found in vector" << std::endl;}
*/


//Using std::bind()
    auto it3 = std::find_if(container.begin(), container.end(), std::bind(std::equal_to<int>(), std::placeholders::_1, 5));
    if (it3 != container.end()) {std::cout << "First occurrence of value 5 found at index: " << std::distance(container.begin(), it3) << std::endl;}
    else {std::cout << "Value 5 not found in vector" << std::endl;}

//Using lambda expression

    auto it4 = std::find_if(container.begin(), container.end(), [](const auto& value) {return value == 5;});
    if (it4 != container.end()) {std::cout << "First occurrence of value 5 found at index: " << std::distance(container.begin(), it4) << std::endl;} 
    else {std::cout << "Value 5 not found in vector" << std::endl;}


//QUESTION D: 

    std::vector<int> container2{1,2,5,5,-3,4,5,5,5,6,3,4,5};
    
    //Return the position of the first three consecutive elements having the value 5
    auto it5 = std::search_n(container2.begin(), container2.end(), 3, 5);
    if (it5 != container2.end()) {std::cout << "Position of the first three consecutive elements with value 5: " << std::distance(container2.begin(), it5) << std::endl;} 
    else {std::cout << "No three consecutive elements with value 5" << std::endl;}

    //Return the position of the first element of the first subrange matching {3,4,5}
    std::vector<int> subrange1{3, 4, 5};
    auto it6 = std::search(container2.begin(), container2.end(), subrange1.begin(), subrange1.end());
    if (it6 != container2.end()) {std::cout << "Position of the first element of the first subrange matching {3, 4, 5}: " << std::distance(container2.begin(), it6) << std::endl;} 
    else {std::cout << "Subrange {3, 4, 5} not found." << std::endl;}

    //Return the position of the first element of the last subrange matching {3,4,5}
    auto it7 = std::find_end(container2.begin(), container2.end(), subrange1.begin(), subrange1.end());
    if (it7 != container2.end()) {std::cout << "Position of the first element of the last subrange matching {3, 4, 5}: " << std::distance(container2.begin(), it7) << std::endl;} 
    else {std::cout << "Subrange {3, 4, 5} not found." << std::endl;}

//Question E: Find the first element in S that has a value equal to the value of the following element
    auto it8 = std::adjacent_find(container2.begin(), container2.end());
    if (it8 != container2.end()) {std::cout << "Position of the first element that has a value equal to the following element: " << std::distance(container2.begin(), it8) << std::endl;} 
    else {std::cout << "Question E has no answer." << std::endl;}


//Question F: Determine whether the elements in subrange2 are equal to the elements in container2.

    std::vector<int> subrange2{1,2,5};
    bool result = std::equal(container2.begin(), container2.end(), subrange2.begin());
    std::cout << std::boolalpha << "Elements in subrange2 are equal to the elements in container2: " << result << std::endl;


    std::cout << std::endl;
    return 0;
}