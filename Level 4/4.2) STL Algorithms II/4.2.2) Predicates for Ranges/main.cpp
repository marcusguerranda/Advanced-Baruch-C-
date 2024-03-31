//4.2) STL Algorithms II 2) Predicates for Ranges

/*Purpose:
        Some STL algorithms only work properly with sorted containers. Since C++11 we have functionality to test 
        if all (part of) a range is sorted. There are four algorithms, one of which is:

        Vector vec8{ 1.0, 2.0, 3.0, -4.0, 10.0 }; // Not ordered
        auto pos = std::is_sorted_until(vec8.begin(), vec8.end());
        std::cout << "bad value: " << *pos << std::endl;

        Answer the following questions:
            PART A) Apply the other three algorithms to this container while experimenting with various binary predicate arguments.
            PART B) Test the efficiency of the code in this question.
*/

/*
    The four  algorithms that check if all, or part of, a range is sorted are:

        --> See below for IMPLEMENTATIONS of each STL function! :)

        - std::IS_SORTED()                                      -> checks if ENTIRE range is sorted in ascending order
            template< class ForwardIt >
            bool is_sorted( ForwardIt first, ForwardIt last );

        - std::IS_SORTED()    
            template< class ForwardIt >                         -> Finds the iterator to the first element that is out of order in the range
            ForwardIt is_sorted_until( ForwardIt first, ForwardIt last,  );

        - std::IS_SORTED_UNTIL()                                -> checks if ENTIRE range is sorted based on a PREDICATE
            template< class ForwardIt >
            bool is_sorted( ForwardIt first, ForwardIt last, );

        - std::IS_SORTED_UNTIL()    
            template< class ForwardIt >                         -> Finds the iterator to the first element THAT SATISFIES PREDICATE
            ForwardIt is_sorted_until( ForwardIt first, ForwardIt last,  );

*/

/*  
    USEFUL FUNCTION OBJECTS THAT CAN BE USED AS PREDICATES FOR THE TWO OVERLOADED VERSIONS:

            std::EQUAL_TO()<>                   -> function object implementing x == y

            std::NOT_EQUAL_TO()<>               -> function object implementing x != y

            std::GREATER()<>                    -> function object implementing x > y

            std::LESS()<>                       -> function object implementing x < y

            std::GREATER_EQUAL()<>              -> function object implementing x >= y

            std::LESS_EQUAL()<>                 -> function object implementing x <= y
*/

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <chrono>

using Vector = std::vector<double>;

int main()
{
    std::cout << std::boolalpha << std::endl;

    //Given
    Vector vec8{ 1.0, 2.0, 3.0, -4.0, 10.0 }; //Not ordered

//STD::IS_SORTED(ForwardIt first, ForwardIt last)
    auto start = std::chrono::high_resolution_clock::now();
    bool result1 = std::is_sorted(vec8.begin(), vec8.end());
    std::cout << "std::is_sorted() bool result: " << result1 << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds timer = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Timer: " << timer.count() << " microseconds" << std::endl;

//STD::IS_SORTED(ForwardIt first, ForwardIt last, Compare comp)
    start = std::chrono::high_resolution_clock::now();
    bool result2 = std::is_sorted(vec8.begin(), vec8.end(), std::greater<double>());
    std::cout << "std::is_sorted(), using std::greater<double>() PREDICATE bool, result: " << result2 << std::endl;
    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Timer: " << timer.count() << " microseconds" << std::endl;

//STD::IS_SORTED_UNTIL(ForwardIt first, ForwardIt last)
    start = std::chrono::high_resolution_clock::now();
    auto pos = std::is_sorted_until(vec8.begin(), vec8.end());
    if (pos != vec8.end()){
        std::cout << "std::is_sorted_until() found unsorted value: " << *pos << std::endl;
    }
    else{
        std::cout << "std::is_sorted_until() reached the end of the range without finding unsorted values." << std::endl;
    }
    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Timer: " << timer.count() << " microseconds" << std::endl;

//STD::IS_SORTED_UNTIL(ForwardIt first, ForwardIt last, Compare comp)
    start = std::chrono::high_resolution_clock::now();
    auto pos2 = std::is_sorted_until(vec8.begin(), vec8.end(), std::greater<double>());
    if (pos2 != vec8.end()){
        std::cout << "std::is_sorted_until(), using std::greater<double>() PREDICATE, found unsorted value: " << *pos2 << std::endl;
    }
    else{
        std::cout << "std::is_sorted_until(), using std::greater<double>() PREDICATE, reached the end of the range without finding unsorted values." << std::endl;
    }
    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Timer: " << timer.count() << " microseconds" << std::endl;

    std::cout << std::endl;
    return 0;
}


//STRANGELY ENOUGH, both sorts algorithms with predicates are faster than their version without predicates


/*
1.          std::is_sorted()
                                                    template<class ForwardIt>
                                                    bool is_sorted(ForwardIt first, ForwardIt last)
                                                    {
                                                        return std::is_sorted_until(first, last) == last;
                                                    }

2.          std::is_sorted_until()
                                                    template <typename ForwardIt>
                                                    ForwardIt is_sorted_until(ForwardIt first, ForwardIt last) {
                                                        ForwardIt it = first;
                                                        if (it != last) {
                                                            while (++it != last) {
                                                                if (*it < *first) {
                                                                    return it;
                                                                }
                                                                first = it;
                                                            }
                                                        }
                                                        return last;
                                                    }


3.          std::is_sorted(), with predicate
                                                    template <typename ForwardIt, typename Compare>
                                                    bool is_sorted(ForwardIt first, ForwardIt last, Compare comp) {
                                                        if (first != last) {
                                                            ForwardIt next = first;
                                                            while (++next != last) {
                                                                if (comp(*next, *first)) {
                                                                    return false;
                                                                }
                                                                first = next;
                                                            }
                                                        }
                                                        return true;
                                                    }



4.          std::is_sorted_until(), with predicate
                                                    template <typename ForwardIt, typename Compare>
                                                    ForwardIt is_sorted_until_descending(ForwardIt first, ForwardIt last, Compare comp) {
                                                        ForwardIt it = first;
                                                        if (it != last) {
                                                            while (++it != last) {
                                                                if (!comp(*it, *first)) {
                                                                    return it;
                                                                }
                                                                first = it;
                                                            }
                                                        }
                                                        return last;
                                                    }
*/