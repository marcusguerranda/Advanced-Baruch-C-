//4.2) STL Algorthms 3) Classifying and Implementing Algorithms

/*Purpose:
Consider a general sequence container for example, std∷list. To which categories do the following 
algorithms belong and which specific algorithm would you use in each case?
    a) Scale all values by a given factor.
    b) Count the number of elements whose values are in a given range.
    c) Find the average, minimum and maximum values in a container.
    d) Find the first element that is (that is not) in a range.
    e) Search for all occurrences of ‘3456’ in the container.
    f) Determine if the elements in two ranges are equal.
    g) Determine if a set is some permutation of ‘12345’.
    h) Is a container already sorted?
    i) Copy a container into another container.
    j) Move the last 10 elements of a container to the front.
    k) Swap two ranges at a given position.
    l) Generate values in a container based on some formula.
    m) Replace all uneven numbers by zero.
    n) Remove all elements whose value is less than 100.
    o) Shuffle a container randomly (pre- and post-C++11 versions).
    p) Compute one-sided divided differences of the values in a container.

        - C1: NONMODIFYING. Designed to operate on containers without modifying the elements themselves. 
                            These algorithms typically perform queries, searches, comparisons, or computations 
                            on the elements and return information or results without altering the container. 
                            Examples of nonmodifying algorithms include std::find, std::count, std::all_of, std::any_of, etc

        - C2: MODIFYING.    Change the contents of the container by performing specific operations on the elements. These 
                            algorithms can modify, replace, or transform the values in the container. Examples of modifying algorithms 
                            include std::copy, std::transform, std::fill, std::replace, etc.

        - C3: REMOVING.     remove elements from the container based on certain conditions. The removal is usually done by shifting the 
                            elements and returning an iterator pointing to the new logical end of the range. Examples of removing algorithms 
                            include std::remove, std::remove_if, std::unique, etc.

        - C4: MUTATING.     Alter the properties or structure of the container itself. These algorithms can change the size, order, or 
                            arrangement of the elements. Examples of mutating algorithms include std::reverse, std::rotate, std::shuffle, std::partition, etc.

        - C5: SORTING.      Arrange the elements of the container in a specific order, such as ascending or descending. These algorithms reorder the elements
                            based on a comparison function or default ordering. Examples of sorting algorithms include std::sort, std::partial_sort, 
                            std::stable_sort, etc.

        - C6: SORTED-RANGE. Designed to operate on containers that are already sorted. They take advantage of the sorted order to perform efficient operations 
                            like searching or merging. Examples of sorted-range algorithms include std::binary_search, std::merge, std::includes, etc.
        
        - C7: NUMERIC.      Specialized for numerical computations. These algorithms perform mathematical operations on the elements, such as summation, product,
                            accumulation, etc. Examples of numeric algorithms include std::accumulate, std::inner_product, std::partial_sum, std::iota, etc.

*/
//NOTE FOR SELF: go check <algorithm> library on cppreference for all the defined functions for a variety of purposes
//               (e.g. searching, sorting, counting, manipulating) that operates on ranges of elements.

//SEE BELOW FOR ANSWERS TO PART A:

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <random>

//Function object to use with std::generate
int f(){
    static int i;
    return ++i;
}



int main()
{
    std::cout<<std::endl;
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.11, 12.32};
    double scaleFactor = 2.5;

    //QUESTION A. Scaling
    //Modifying
    std::transform(vec1.begin(), vec1.end(), vec1.begin(), [&scaleFactor](double& value) { return value * scaleFactor; });

    //Print the scaled values of vector vec1
    for (const auto& value : vec1) 
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // vec1 = [2.5 5 7.5 10 12.5 15 17.5 20 22.5 25 27.775 30.8] , after scaling

    //QUESTION B. Count the number of elements whose values are in a given range.
    //Non-modifying
    //Here, counting the number of elements within range 1.5 and 3.4
    //std::count_if returns iterator / std::count returns number of elements

    int numElements = std::count_if(vec1.begin(), vec1.end(), [](double value) 
    {
        return value >= 1.5 && value <= 3.4;
    });

    std::cout << "\n 2.Number of elements in vector vec1 that are within the range 1.0-4.0: " << numElements << std::endl;

    //QUESTION C. Find the average, minimum and maximum values in a container
    
    int min = *std::min_element(vec1.begin(), vec1.end());  //Returns an iterator -> DEREFERENCE!  / nonmodifying
    int max = *std::max_element(vec1.begin(), vec1.end());  //                                       nonmodifying
    int avg = (std::accumulate(vec1.begin(), vec1.end(), 0.0)) / vec1.size(); //                     numeric

    std::cout << "\n 3.Minimum is: " << min << ", maximum is: " << max << ", and average is: " << avg << std::endl;



    //QUESTION D. Find the first element that is, and that is NOT, in a range.
    //Non-modifying
        //Note: return an iterator to the first element in the range [first, last) for which the predicate return true. If NO such element is found, the 
        //      function returns 'last'
        //See lines 164 of notes on std::find, std::find_if, and std::find_if_not

        //auto it_find = std::find(vec1.begin(), vec1.end(), 9.0);    //--> uses == operator to search for value
        //int index = std::distance(vec1.begin(), it_find);

    //std::find_if is very similar to std::find but uses a predicate to search for a value with a more precise ask/predicate
    //Searches for element for which predicate p returns 'true'
    //Return type: returns the first iterator it in the range [first, last) satisfying the condition p(*it) that is 'true'
    //Searching for first element that is within range 1.5-3.4
    auto it = std::find_if(vec1.begin(), vec1.end(), [](const double& val){return (val>-1.0) && (val<3.4);});
    int it_index = std::distance(vec1.begin(), it);
    std::cout << "\n 4.First element in vector vec1 that is within range 1.5-3.4 is element: " << *it << " at index: " << it_index << std::endl;

    //First element that is NOT in range 0.0-7.5.
    //Searches for element for which predicate p return 'false'
    //Return type: returns the first iterator it in the range [first, last) satisfying the condition q(*it) that is 'false'
    it = std::find_if_not(vec1.begin(), vec1.end(), [](const double& val){return (val>0.0) && (val<7.5);});
    it_index = std::distance(vec1.begin(), it);
    std::cout << "\nFirst element in vector vec1 that is NOT within range 0.0-7.5 is element: " << *it << " at index: " << it_index << std::endl;

    //QUESTION E. Search for all occurrences of numbers '3456' in the container
    //Non-modifying

    /*std::search -> searches for a range of elements
    OF FORM:
            first, last	-	the range of elements to examine
            s_first, s_last	-	the range of elements to search for
            policy	-	the execution policy to use. See execution policy for details.
            searcher	-	the searcher encapsulating the search algorithm and the pattern to look for
            p	-	binary predicate which returns ​true if the elements should be treated as equal.
    */
    //std::search_n -> searches a range for a number of consecutive copies of an element

    std::vector<double> numbers3456{3.0, 4.0, 5.0, 6.0};
    int counter = 0;
    while ((vec1.begin() = std::search_n(vec1.begin(), vec1.end(), numbers3456.size(), numbers3456.front())) != vec1.end()) 
    {
        //Found an occurrence
        counter++;
        vec1.begin() += numbers3456.size();
    }
    std::cout << "Number of occurrences of elements 3.0, 4.0, 5.0, and/or 6.0 in the vector is: " << counter << std::endl;

    /*QUESTION F. Determine if the elements in two ranges are equal
    Non-modifying -> std::equal. Two ranges are considered equal if they have the same number of elements and, for every iterator i in the range
                                 [first1,last1), i* equals *(first2+ (i-first1)). operator == is used.
    --> See the many possible forms on cppreference
            first1, last1	-	the first range of the elements to compare
            first2, last2	-	the second range of the elements to compare
            policy	-	the execution policy to use. See execution policy for details.
            p	-	binary predicate which returns ​true if the elements should be treated as equal.
    */
    std::cout << std::boolalpha;
    std::cout << "\nIs the first suggested two ranges equal? " << std::equal(vec1.begin(), vec1.begin()+3, vec1.begin()+3, vec1.end());     //FALSE
    std::cout << "\nIs the second suggested two ranges equal? "<< std::equal(vec1.begin(), vec1.begin()+3, vec1.begin(), vec1.begin()+3);  //TRUE

    /*QUESTION G. Determine is a set is some permutation of 12345
    NON-MODIFYING
            first1, last1	-	the range of elements to compare
            first2, last2	-	the second range to compare
            p	-	binary predicate which returns true if the elements should be treated as equal.
            The signature of the predicate function should be equivalent to the following: bool pred(const Type &a, const Type &b);
    */

    std::vector<double> permutation_set{1.0,2.0,3.0,4.0,5.0};
    std::cout << "\n\nIs vec1 a permutation of set '12345': " << std::is_permutation(vec1.begin(), vec1.end(), permutation_set.begin());


    /*QUESTION H. Is a container already sorted?
    Sorting --> std::is_sorted
    */
    std::cout << "\nvec1 is sorted: " << std::is_sorted(vec1.begin(), vec1.end()) << std::endl;

    /*QUESTION I. Copy a container into another container
        MODIFYING -> std::copy / std::copy_if (using defined predicate and while predicate keeps returning true)

        Copies all elements in the range [first, last) starting from first and proceeding to last - 1. 
        The behavior is undefined if d_first is within the range [first, last). In this case, std::copy_backward may be used instead.
    */
    std::vector<double> copy_vec;
    std::copy(vec1.begin(), vec1.end(), std::back_inserter(copy_vec));
    std::cout << "Printing elements copied from vec1 to copy_vec:"<<std::endl;
    for(auto&elem:copy_vec){std::cout << elem << " ";};


    /*QUESTION J. Move the last 10 elements of a container to the front
    MUTATING
                std::rotate swaps the elements in the range [first, last) in such a way that the elements in [first, middle) are placed 
                after the elements in [middle, last) while the orders of the elements in both ranges are preserved.
    RETURNS AN ITERATOR!

    template< class ExecutionPolicy, class ForwardIt >
    ForwardIt rotate( ExecutionPolicy&& policy,
                    ForwardIt first, ForwardIt middle, ForwardIt last );
                
            first	-	the beginning of the original range
            middle	-	the element that should appear at the beginning of the rotated range
            last	-	the end of the original range
            policy	-	the execution policy to use. See execution policy for details.
    */
    std::cout << "\n\nRotating previously created vector copy_vec such that I move the first 10 elements to the front" <<std::endl;
    std::rotate(copy_vec.begin(), copy_vec.end()-10, copy_vec.end());
    for(auto&elem:copy_vec){std::cout << elem << " ";};

    /*QUESTION K. Swap two ranges at a given position
    MUTATING
        std::swap_ranges ->  Exchanges elements between range [first1, last1) and another range starting at first2.
                             Precondition: the two ranges [first1, last1) and [first2, last2) do not overlap, 
                             where last2 = std::next(first2, std::distance(first1, last1)).
                first1, last1	-	the first range of elements to swap
                first2	-	beginning of the second range of elements to swap
                policy	-	the execution policy to use. See execution policy for details.
    
        template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
        ForwardIt2 swap_ranges( ExecutionPolicy&& policy, ForwardIt1 FIRST1, ForwardIt1 LAST1, ForwardIt2 FIRST2);
    */

    std::cout << "\n\nElements in copy_vec: "; for(auto&elem:copy_vec){std::cout << elem << " ";};
    std::cout << "\nElements in vec1: "; for(auto&elem:vec1){std::cout << elem << " ";};
    //Swapping elements between copy_vec and vec1
    std::swap_ranges(vec1.begin(), vec1.end(), copy_vec.begin());
    std::cout << "\nElements NOW in copy_vec: "; for(auto&elem:copy_vec){std::cout << elem << " ";};
    std::cout << "\nElements NOW in vec1: "; for(auto&elem:vec1){std::cout << elem << " ";};


    /*QUESTION L. Generate values in a container based on some formula
    MODIFYING
        std::generate:
            template< class ExecutionPolicy, class ForwardIt, class Generator >
            void generate( ExecutionPolicy&& policy, ForwardIt FIRST, ForwardIt LAST, Generator G );
        
                first, last	-	the range of elements to generate
                policy	-	the execution policy to use. See execution policy for details.
                g	-	generator function object that will be called.
                The signature of the function should be equivalent to the following:

                Ret fun();
                The type Ret must be such that an object of type ForwardIt can be dereferenced and assigned a value of type Ret.​
    
    */
   std::vector<int> vec_generated(5);
   std::generate(vec_generated.begin(), vec_generated.end(), f);
   std::cout << "\n\nElements generated into 'vec_generated' are: "; for(auto&elem:vec_generated){std::cout << elem <<" ";};


    /*QUESTION M. Replace all uneven numbers by 
    MODIFYING

        template< class ExecutionPolicy, class ForwardIt, class T >
        void std::REPLACE( ExecutionPolicy&& policy, ForwardIt FIRST, ForwardIt LAST, const T& OLD_VALUE, const T& NEW_VALUE); 
            --> replaces all elements that are equal to old value


        template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate, class T >
        void std::REPLACE_IF( ExecutionPolicy&& policy, ForwardIt FIRST, ForwardIt LAST, UnaryPredicate P, const T& NEW_VALUE);
            --> replaces all elements for which predicate p return 'true'
    */

    std::replace_if(vec_generated.begin(), vec_generated.end(), [](const int& elem){return elem % 2 !=0;}, 0);
    std::cout << "\n\nPrint 'vec_generated' after having replaced all uneven elements with 0: "; for(auto&elem:vec_generated){std::cout << elem <<" ";};

    /*QUESTION N. Remove all elements who value is less than 100
    MODIFYING   

        template< class ExecutionPolicy, class ForwardIt, class T>
        ForwardIt STD::REMOVE( ExecutionPolicy&& policy, ForwardIt FIRST, ForwardIt LAST, const T& VALUE);
            --> Removes all elements that are equal to 'value' (using operator==).

        template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
        ForwardIt STD::REMOVE_IF( ExecutionPolicy&& POLICY, ForwardIt FIRST, ForwardIt LAST, UnaryPredicate P);
            --> Removes all elements for which predicate p returns 'true'.
    */
    vec_generated.erase(
        std::remove_if(vec_generated.begin(), vec_generated.end(), [](const int& elem) { return elem < 100; }),
        vec_generated.end()
    );
    std::cout << "\n\n Given the previous output for elements in 'vec_generated', size of the vector should now be 0 since all other elements were stricly less than 100" << std::endl;
    std::cout << vec_generated.size() << std::endl;

    /*QUESTION O: Shuffle a container randomnly (pre- and ost C++11 versions)

        Pre C+11: std::random_shuffle s.t:
            template< class RandomIt, class RandomFunc >
            void STD::RANDOM_SHUFFLE( RandomIt first, RandomIt last, RandomFunc& r );   -> The source of randomness is the object r
    
        Post C++11:
            template< class RandomIt, class URBG>
            void STD::SHUFFLE( RandomIt FIRST, RandomIt LAST, URBG&& g);                -> The source of randomness is the object g
    */

   std::cout << "\n\nElements in vec1, prior to shuffling: "; for(auto&elem:vec1){std::cout << elem << " ";};
   std::mt19937 engine;
   std::shuffle(vec1.begin(), vec1.end(), engine);
   std::cout << "\n\nElements in vec1, after shuffling: "; for(auto&elem:vec1){std::cout << elem << " ";}; 

    /*QUESTION P: compute one-sided divided differences of the values in a container
        std::adjacent_difference: If [first, last) is not empty, computes the differences between the second and the first of each adjacent pair of its elements and writes the differences to the range beginning at d_first + 1. 

            template< class InputIt, class OutputIt >
            constexpr OutputIt adjacent_difference( InputIt first, InputIt last, OutputIt d_first );     

            first, last	-	the range of elements
            d_first	-	the beginning of the destination range
            policy	-	the execution policy to use. See execution policy for details.
            op	-	binary operation function object that will be applied.
    
    */

    std::adjacent_difference(vec1.begin(), vec1.end(), vec1.begin());
    std::cout << "\n\nElements in vec1, after adjacent differences: "; for(auto&elem:vec1){std::cout << elem << " ";}; 

    std::cout << std::endl;
    return 0;
}









//-----------------------------------------------------   PART A: 

/*
a) Scaling all values by a given factor:
    Category: MODIFYING algorithms.
    Algorithm: 
        - std::transform() with a lambda or function object that multiplies each value by the factor.
        

b) Counting the number of elements whose values are in a given range:
    Category: Non-modifying algorithms.
    Algorithm: std::count_if with a lambda or function object that checks if each value is within the given range.
c) Finding the average, minimum, and maximum values in a container:
    Category: Non-modifying algorithms.
    Algorithm:
    Average: Calculate the sum of all elements with std::accumulate and then divide by the number of elements.
    Minimum: std::min_element.
    Maximum: std::max_element.

d) Finding the first element that is (or is not) in a range:
    Category: Non-modifying algorithms.
    Algorithm:
    First element in range: std::find with the given range.
    First element not in range: std::find_if_not with the given range.

e) Searching for all occurrences of '3456' in the container:
    Category: Non-modifying algorithms.
    Algorithm: std::search with the sequence '3456' as the pattern to find.

f) Determining if the elements in two ranges are equal:
    Category: Non-modifying algorithms.
    Algorithm: std::equal with the two ranges.

g) Determining if a set is some permutation of '12345':
    Category: Non-modifying algorithms.
    Algorithm: std::is_permutation with the set and the sequence '12345'.

h) Checking if a container is already sorted:
    Category: Non-modifying algorithms.
    Algorithm: std::is_sorted or std::is_sorted_until to check if the container is sorted or find the first unsorted element, respectively.

i) Copying a container into another container:
    Category: Modifying algorithms.
    Algorithm: std::copy to copy the elements from one container to another.

j) Moving the last 10 elements of a container to the front:
    Category: Modifying algorithms.
    Algorithm: std::rotate with the appropriate iterator positions to move the last 10 elements to the front.

k) Swapping two ranges at a given position:
    Category: Modifying algorithms.
    Algorithm: std::swap_ranges with the two ranges to swap.
*/




/*                                                              NOTES FOR SELF
-----------------------------------------------------------------------------------------------------------

    STD::FIND, and variants: 
        Searches for the first occurrence of a value in a sequence. It's commonly used for searching or checking if an element exists in a container.
            template< class ExecutionPolicy, class ITER, class T >
            ITER find( ExecutionPolicy&& policy, ITER FIRST, ITER LAST, const T& VALUE );
        -> First, last : range of elements to examine
        -> Value: value to compare the elements to
        -> policy: unary predicate that returns true for the require element 
        Return type: returns the first iterator it in the range [first, last) satisfying the condition (*it == value) OR 'last' if there is no such iterator

    STD::FIND_IF: 
        Searches for element for which predicate p returns 'true'
            template< class InputIt, class UnaryPredicate >
            InputIt find_if( InputIt first, InputIt last, UnaryPredicate p );
        Return type: returns the first iterator it in the range [first, last) satisfying the condition p(*it) that is 'true'

    STD::FIND_IF_NOT:
        Searches for element for which predicate p return 'false'
            template< class InputIt, class UnaryPredicate >
            InputIt find_if_not( InputIt first, InputIt last, UnaryPredicate q );
        Return type: returns the first iterator it in the range [first, last) satisfying the condition q(*it) that is 'false'


    STD::COUNT: 
        Counts the number of occurrences of a value in a sequence. It's useful for determining the frequency of an element in a container.
            template< class InputIt, class T >
            constexpr typename iterator_traits<InputIt>::difference_type COUNT( InputIt first, InputIt last, const T& value );
                E.g.
                                int main()
                                {
                                    constexpr std::array v {1, 2, 3, 4, 4, 3, 7, 8, 9, 10};
                                
                                    // determine how many integers match a target value.
                                    for (const int target: {3, 4, 5})
                                    {
                                        const int num_items = std::count(v.cbegin(), v.cend(), target);
                                        std::cout << "number: " << target << ", count: " << num_items << '\n';
                                    }
                                }
                        Output: number: 3, count: 2
                                number: 4, count: 2
                                number: 5, count: 0
    STD::COUNT_IF:
        Counts elements for predicate p return 'true'
            template< class InputIt, class UnaryPredicate >
            typename iterator_traits<InputIt>::difference_type
            count_if( InputIt first, InputIt last, UnaryPredicate p );

    STD::ALL_OF, STD::ANY_OF, STD::NONE_OF: 
        These algorithms check whether all, any, or none of the elements in a sequence satisfy a predicate. They are helpful for performing conditional checks on container elements.
        ALL_OF --> if unary predicte p returns 'true' for ALL elements in the range [first, last)
        ANY_OF --> if unary predicate p returns 'true' for AT LEAST one element in the range [first, last)
        NONE_OF --> if unary predicate p returns 'true' for NO elements in the range [first, last)]


    STD::ACCUMULATE: 
        Computes the sum, product, or other, of the given value init and the elements in the range [first, last). Optionality to specify binary operator
                template< class InputIt, class T, class BinaryOperation >
                constexpr T accumulate( InputIt first, InputIt last, T init, BinaryOperation op );


    STD::MIN_ELEMENT, STD::MAX_ELEMENT: 
        Find the minimum and maximum elements in a sequence, using < or > operators
                template< class ForwardIt>
                constexpr ForwardIt min_element(ForwardIt first,ForwardIt last );

    STD::SEARCH: 
        Searches for a subsequence within a sequence. It can be used to find occurrences of a specific pattern or subsequence in a container.
        Searches for the first occurrence of the sequence of elements [s_first, s_last) in the range [first, last)., using == operator
                template< class ExecutionPolicy,
                class ForwardIt1, class ForwardIt2, class BinaryPredicate >
                ForwardIt1 search(ExecutionPolicy&& policy, ForwardIt1 FIRST, ForwardIt1 LAST, ForwardIt2 S_FIRST, ForwardIt2 S_LAST, BinaryPredicate PREDICATE );

    STD::EQUAL: 
        Determines if two sets of elements are the same
        Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), and false otherwise.
                template<class ExecutionPolicy,class ForwardIt1, class ForwardIt2 >
                bool equal(ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2 );

    STD::IS_SORTED: 
        Checks whether a range is sorted into ascending order. Possibility of defining a comparator, but not necessary
            template< class ForwardIt, class Compare>
            bool is_sorted( ForwardIt first, ForwardIt last, Compare comp );

    STD::TRANSFORM: 
        Applies a function to range of elements, storing results in a destination range
        Two forms:

        1.  template<class InputIt, class OutputIt, class UnaryOperation>
            OutputIt transform( InputIt first1, InputIt last1, OutputIt d_first, UnaryOperation unary_op );
            -> The unary operation unary_op is applied to the range defined by [first1, last1).

        2.  template< class InputIt1, class InputIt2, class OutputIt, class BinaryOperation >
            OutputIt transform( InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOperation binary_op );
            -> The binary operation binary_op is applied to pairs of elements from two ranges: one defined by [first1, last1) and the other beginning at first2.


-------------------------------------------------------------MODIFYING------------------------------------------------------------------------
    
    STD::COPY  / STD::COPY_IF       --> OR :   STD::MOVE (moves a range of elements to a new location)
        Copies a range of elements to a new location
            template< class InputIt, class OutputIt >
            OutputIt COPY( InputIt first, InputIt last, OutputIt d_first );

            template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class UnaryPredicate >
            ForwardIt2 COPY_IF( ExecutionPolicy&& policy, ForwardIt1 FIRST, ForwardIt1 LAST, ForwardIt2 D_FIRST, UnaryPredicate PREDICATE );

    STD::FILL 
        Copy-assigns the given value to EVERY element in a range
            template<class ForwardIt, class T>
            void FILL( ForwardIt first, ForwardIt last, const T& value );

    STD::FILL_N
        Copy-assigns the given value to N elements in a range

    STD::GENERATE
        Assigns the results of successive function calls to EVERY element in a range, where g is a function object that can be called
            template< class ForwardIt, class Generator >
            void generate( ForwardIt first, ForwardIt last, Generator g );

    STD::GENERATE_N
        Assigns the results of successive function calls to N elements in a range
            template< class OutputIt, class Size, class Generator >
            OutputIt generate_n( OutputIt first, Size count, Generator g ); 

    STD::REMOVE / STD::REMOVE_IF
        Replaces all values satisfying specific criteria with another value

    STD::REPLACE / STD::REPLACE_IF
        Replaces all values satisfying specific criteria with another value


    STD::SORT (see additional algorithms in Sorting operations)
        Sorts a range into ascending order

    STD:::REVERSE
        Reverses the order of elements in a range

    STD::UNIQUE
        Removes consecutive duplicate elements in a range

    STD::SHUFFLE
        Randomly re-orders elements in a range
*/