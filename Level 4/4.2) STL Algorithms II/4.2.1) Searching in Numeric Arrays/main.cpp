//4.2) STL Algorithms II. 1) Searching in Numeric Arrays

/*Purpose: Different scenarios to face:
    - S1: Does a sorted range contain a given value (std::binary_search)?
    - S2: Does a sorted range contain another sorted range (std::includes)?
    - S3: Locating first or last positions in a sorted range (std::lower_bound , std::upper_bound).
    - S4: Return a range containing all elements corresponding to a value in a sorted range
          (std::equal_range).
    - S5: Find the first occurrence of a value in a sorted range (std::find(), std::find_if(),
          std::find_if_not()). The last algorithm is since C++11.
    - S6: Some algorithms need sorted ranges as input, hence we need algorithms to test if they are sorted 
          (std::is_sorted , std::is_sorted_until) (since C++11).

IMPORTANT: most of the STL algorithms return an iterator to the target value that we wish to locate. However, we are interested in finding the 
           (integral) index in the sorted range corresponding to that value. 
           This entails that we must create user-friendly wrapper functions for the above STL algorithms.
*/

//Author: Andrew Guerrand

//Modification dates: 6/26/2023


#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>
#include <exception>

/* PART A:  All the search algorithms search for the location of a value xin a vector v. The return type is a nested 
            tuple consisting of a range that encloses xand a Boolean value that indicates success or failure:
*/
using Range = std::tuple<std::size_t, std::size_t>;
using Result = std::tuple<Range, bool>;
constexpr std::size_t InvalidIndex = std::numeric_limits<std::size_t>::max();   //Invalid index, rather than have 999 when a specific value is not found. It assumes 999
                                                                                //there is no 999 in a vector, which is of course ludicrous.

//Function to check if a vector is sorted
template<typename T>
bool is_sorted(const std::vector<T>& vec)
{
    return std::is_sorted(vec.begin(), vec.end());
}

//Function to generate random vector
template <typename T>
std::vector<T> generateVector(std::size_t size, const T& min, const T& max)
{
    //Generating data with random device and Mersenne Twister pseudo-random number generator
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<T> dis(min, max);

    std::vector<T> vec(size);
    for (std::size_t i = 0; i < size; ++i)
        vec[i] = dis(generator);

    return vec;
}

//Print results from Result instances...
void printResult(const Result& result)
{
    const Range& range = std::get<0>(result);
    bool success = std::get<1>(result);

    std::cout << "Result: ";

    if (success)
    {
        std::cout << "Indices: (" << std::get<0>(range) << ", " << std::get<1>(range) << ")";
    }
    else
    {
        std::cout << "Value not found";
    }

    std::cout << std::endl;
}

//Find_sequential_greater
template<typename T> 
Result find_sequential_greater(const std::vector<T>& vec, T x)
{
    //MODIFIED CODE, I added this part: Checking whether function is sorted or not
    if(!is_sorted(vec))
    {
        throw std::invalid_argument("Vector is not sorted, and therefore the function will not give appropriate results");}

    for (std::size_t j = 0; j < vec.size(); ++j)
    {
        //NOTE: the code that was given is flawed. It assumes that the vector is sorted, else it misses quite a few instances where (v[j]>x AND v[j+1]<=x).... 
        // Case 1, when looking for value 5.3   -> Values in vector are 4 and 6, then value is in between.
        // Case 2,          ''                  -> Values in vector are 6 and 4, then value is in between. But first implementation would have missed it...
        
        //Therefore, I will keep the code, but ASSUME it is indeed sorted, and give indices, in a tuple, when the referenced vector is indeed sorted.
        if (vec[j] <= x && vec[j+1] > x)
        {
            return std::make_tuple(std::make_tuple(j, j+1), true);
        }
    }
    return std::make_tuple(std::make_tuple(InvalidIndex, InvalidIndex), false);
}

//Find_sequential_greater, using std::find_if
template <typename T>
Result find_sequential_greater_find_if(const std::vector<T>& vec, T x) 
{
    //MODIFIED CODE, I added this part: Checking whether function is sorted or not
    if(!is_sorted(vec))
    {
        throw std::invalid_argument("Vector is not sorted, and therefore the function will not give appropriate results");
    }
    
    auto SearchX = [&](const T& value) {
        auto it = std::find(vec.begin(), vec.end(), value);
        if (it != vec.end() && std::distance(vec.begin(), it) < vec.size() - 1) {
            std::size_t index = std::distance(vec.begin(), it);
            return vec[index] <= x && vec[index + 1] > x;
        }
        return false;
    };

    auto it = std::find_if(vec.begin(), vec.end(), SearchX);

    if (it != vec.end()) 
    {
        std::size_t index = std::distance(vec.begin(), it);
        return std::make_tuple(std::make_tuple(index, index+1), true);
    }

    return std::make_tuple(std::make_tuple(InvalidIndex, InvalidIndex), false);
}


//PART B: using std::lower_bound and std::upper_bound
//Find_sequential_greater, using std::lower_bound
template <typename T>
Result find_sequential_greater_lower_bound(const std::vector<T>& vec, T x)
{
    //Check if the vector is sorted
    if (!is_sorted(vec))
    {
        throw std::invalid_argument("Vector is not sorted, and therefore the function will not give appropriate results");
    }

    auto it = std::lower_bound(vec.begin(), vec.end(), x);
    if (it != vec.end() && std::distance(vec.begin(), it) < vec.size() - 1)
    {
        std::size_t index = std::distance(vec.begin(), it);
        return std::make_tuple(std::make_tuple(index, index + 1), true);
    }

    return std::make_tuple(std::make_tuple(InvalidIndex, InvalidIndex), false);
}

//Find_sequential_greater, using std::upper_bound
template <typename T>
Result find_sequential_greater_upper_bound(const std::vector<T>& vec, T x)
{
    //Check if the vector is sorted
    if (!is_sorted(vec))
    {
        throw std::invalid_argument("Vector is not sorted, and therefore the function will not give appropriate results");
    }

    auto it = std::upper_bound(vec.begin(), vec.end(), x);
    if (it != vec.end() && std::distance(vec.begin(), it) < vec.size() - 1)
    {
        std::size_t index = std::distance(vec.begin(), it) - 1;
        return std::make_tuple(std::make_tuple(index, index + 1), true);
    }

    return std::make_tuple(std::make_tuple(InvalidIndex, InvalidIndex), false);
}

//PART C: using std::equal_range
// Find_sequential_greater, using std::equal_range
template <typename T>
Result find_sequential_greater_equal_range(const std::vector<T>& vec, T x)
{
    // Check if the vector is sorted
    if (!is_sorted(vec))
    {
        throw std::invalid_argument("Vector is not sorted, and therefore the function will not give appropriate results");
    }

    auto range = std::equal_range(vec.begin(), vec.end(), x);
    if (range.first != range.second && std::distance(vec.begin(), range.second) < vec.size() - 1)
    {
        std::size_t index = std::distance(vec.begin(), range.second);
        return std::make_tuple(std::make_tuple(index - 1, index), true);
    }

    return std::make_tuple(std::make_tuple(InvalidIndex, InvalidIndex), false);
}

int main()
{
    std::cout << "\nPART A: using find_sequential greater\n" << std::endl;
    //Random vector of size 20, with minimum value -10 and maximum value 34
    std::vector<int> vector1 = generateVector(20, -10, 34);
    
    //Print the vector
    std::cout << "Vector 'vector1': ";
    for (const auto& num : vector1)
        std::cout << num << " ";
    std::cout << std::endl;

    std::cout << std::boolalpha;
    std::cout << "'vector1' is sorted: " << is_sorted(vector1) << std::endl;
    
    //Sorting vector1 before calling appropriate functions
    std::sort(vector1.begin(), vector1.end());
    std::cout << "NOW, 'vector1' is sorted: " << is_sorted(vector1) << std::endl;

    // Call the functions and compare the results
    Result result1 = find_sequential_greater(vector1, 10);              //Will be found normally, because in between min and max
    Result result2 = find_sequential_greater_find_if(vector1, 10);      //Will be found normally, because in between min and max
    Result result3 = find_sequential_greater(vector1, 35);              //Will NOT be found -> above max value for vector generator
    Result result4 = find_sequential_greater_find_if(vector1, 35);      //Will NOT be found -> above max value for vector generator
    
    Result result5 = find_sequential_greater_lower_bound(vector1, 10);  //std::lower_bound used
    Result result6 = find_sequential_greater_upper_bound(vector1, 10);  //std::upper_bound used
    
    Result result7 = find_sequential_greater_equal_range(vector1, 10);  //std::equal_range used


    // Print the results
    std::cout << "\nResult using find_sequential_greater and value of 10: \n";
    printResult(result1);

    std::cout << "Result using find_sequential_greater_find_if and value of 10: \n";
    printResult(result2);

    std::cout << "\nResult using find_sequential_greater and value of 35, given max value for vector generator is 34...: \n";
    printResult(result3);

    std::cout << "Result using find_sequential_greater_find_if and value of 35, given max value for vector generator is 34...: \n";
    printResult(result4);

    std::cout << "\nResult using find_sequential_greater_lower_bound and value of 10: \n";
    printResult(result5);

    std::cout << "\nResult using find_sequential_greater_upper_bound and value of 10: \n";
    printResult(result6);

    std::cout << "\nResult using find_sequential_greater_equal_range and value of 10: \n";
    printResult(result7);


/*PART D: using std::find_if_not with an example of your choice.
/         I will simply iterate through vector1 and return the iterator position of the first element that is odd, and thus returns false from predicate

                template <typename InputIt, typename UnaryPredicate>
                InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p);
    
    Algorithm that is used to find the first element in a range for which a given unary predicate returns false. 
    It is the complement of std::find_if, which finds the first element for which the predicate returns true. It iterates over the range defined 
    by the iterators first and last, and applies the provided predicate to each element. The algorithm stops as soon as it encounters an element 
    for which the predicate returns false, and it returns an iterator pointing to that element. If no element satisfies the condition (i.e., the 
    predicate returns true for all elements), it returns the last iterator.
*/

    //std::find_if_not that returns the iterator position of the first number that is odd, or by consequence not-even
    auto it = std::find_if_not(vector1.begin(), vector1.end(), [](int& num){return num % 2 ==0;});
    if(it != vector1.end()){
        int number = *it;
        int index = std::distance(vector1.begin(), it);
        std::cout << "\nPART D: First number to not follow defined predicate in std::find_if_not is: " << number << " , with index: " << index << std::endl;
    }
    else{
        std::cout << "\nPART D: No odd number found in the vector." << std::endl;
    }
    std::cout << std::endl;
    return 0;
}