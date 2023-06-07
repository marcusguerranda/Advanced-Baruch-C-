//main.cpp

//Purpose: Adapters for STL algorithms
/*
	We need to use adapters because there is an interface mismatch between what we want (integral indexes) while STL works with iterators. 
	This means that the output of STL algorithms will be in terms of iterators, but we want the output to be in terms of integral indices. 
	By creating adapters, we can modify the output of the STL algorithms to match our desired output.

	For example, to solve the first problem of finding the first index i such that v[i] <= x < v[i+1], we can create an adapter function 
	that takes the vector and the target value as input and returns the index i. This adapter function would use std::find to find the iterator 
	to the first element greater than or equal to x, and then use std::distance to calculate the distance between the beginning of the vector 
	and the iterator. The adapter function would return this distance as the integral index i.
*/


//Author: Andrew Guerrand

//Last modified: 4/16/2023

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <iomanip>		//For std::setprecision(x)
#include <iterator>



//PART A: firstIndex() function, searching first index i such that v[i] <= x < v[i + 1], is part of indexFinger struct. 
template <typename Vector>
struct indexFinder
{
	static int firstIndex(const Vector& source_vector, const double& target_value)
	{
		//Vector needs to contain at least two elements
		if(source_vector.size() < 2) {throw std::logic_error("Vector must contain as least two elements.");}

		//Creating a copy of the sorted vector here to perform computations
		Vector new_vector = source_vector;	

		//Creating a copy of the sorted vector here to perform computations
		//Checking if the vector is sorted or not. Sorting is more computationally intensive than checking for whether it is sorted or not, and then sorting.
		// std::is_sorted has a complexity of O(N)
		// std::sort is of complexity O(N log N)
		if(!std::is_sorted(source_vector.begin(), source_vector.end()))
		{
			//If not sorted, then sort
			std::sort(new_vector.begin(), new_vector.end());
		}

		//Find iterator position where target value is first found. Returns 'last', if target value is not found
		auto it = std::find(new_vector.begin(), new_vector.end(), target_value);

		//Distance between initial index and supposed target value
    	int distance_iterator = std::distance(new_vector.begin(), it);	

		//Return index if it's not returning 'last' index, which would indicate subscases otherwise
		if(distance_iterator != (new_vector.size())){return distance_iterator;}			
		else
		{	//If the target value is within range such that:  lowest val. <= value < largest val, then we need to adjust for rounding a double value
			//Since if target_value == largest value, then we still get an out of bounds given condition: v[i] <= x < v[i+1]
			if (target_value >= new_vector.front() && target_value < new_vector.back()) 
			{
				//Find 'num' index where target_value < num and where num is closest to target_value. Decrement by one the index and return.
				auto num = std::lower_bound(new_vector.begin(), new_vector.end(), target_value);
				distance_iterator = std::distance(new_vector.begin(), num);
				return distance_iterator;
			}
			else { return 999;}	
			//Return 999 when target value is not within range first_value <= target < last_value, and that 'last' is initially thrown (). Indeed, I use std::find first,
			//which takes care of the subcase where we have multiple same 'last_value' at the end of the vector.
		};
	};

};





//PART B: finding the absolute and relative error, as well as maximum error, between two vectors in a given index range [i;j] 
template<typename Vector, typename Lambda>
struct errorFinder
{
	static void errorCalculator(const Vector& v1, const Vector& v2, Lambda& lambda_func)
	{
		Vector vec_differences;	//Vector holding absolute or relative differences
		lambda_func(v1, v2, vec_differences);
		double diff = *std::max_element(vec_differences.begin(), vec_differences.end());
		size_t index = std::distance(vec_differences.begin(), std::max_element(vec_differences.begin(), vec_differences.end()));
		std::tuple<size_t, double> results = std::make_tuple(index, diff);	//Tuple which contains the index at which the max is (absolute or relative), and the max error of interest

		std::tie(index, diff) = results;
		std::cout << "The index at which the error of interest is highest is at: " << index << ". The relevant error is: " << diff << std::endl;
	};
};




int main() 
{
//PART A:  Given a sorted numeric vector v and a target value  x, find the first index i such that v[i] <= x < v[i + 1]. Determine the return type.

//std::vector<double> vector1 = {1, 4, 1, 2, 8, 14, 3, 5, 15, 15};  
//							  -> SORTED: {1,1,2,3,4,5,8,14,15,15}
//CASES:
//	--> if target value is 18 (above upper bound), the return index is 'last' (here: 9, and returns thus: 999) in [first, last)
//	--> if target value is -4 (below lower bound), the return index is 'last' (here: 9) in [first, last)
//	--> if target value is IN between upper and lower, such as x = 2.3, the return index will be 2, as index[2] <2.3 < index[3]
//	--> if target value is 1, return index will be 0.
//	--> if target value is 15 , return index will be 8 (last elements index)





    using Vector = std::vector<double>;
    using Lambda = std::function<void(const Vector& v1, const Vector& v2, Vector& vec_differences)>;

	Vector vector1 = {1, 4, 1, 2, 8, 14, 3, 5, 15, 15};					//{1, 1, 2, 3, 4, 5, 8, 14, 15, 15} (In order)
	std::cout << "\nBest index is: " << indexFinder<Vector>::firstIndex(vector1, 3.45) << std::endl;
	
//PART B:


	//Lambda function for absolute errors calculation
	Lambda abs_Differences = [](const Vector& v1, const Vector& v2, Vector& abs_diff) -> void
	{
		if(v1.size() != v2.size()){throw std::logic_error("Vectors are not of same size...");};
		abs_diff.resize(v1.size());
		std::transform(v1.begin(), v1.end(), v2.begin(), abs_diff.begin(), [](const double& a, const double& b) 
		{ return std::abs(a - b);});
	};

	//Lambda function for relative errors calculation
	Lambda relative_Differences = [](const Vector& v1, const Vector& v2, Vector& rel_diff) -> void 
	{
		if(v1.size() != v2.size()){throw std::logic_error("Vectors are not of same size...");};
		rel_diff.resize(v1.size());
		std::transform(v1.begin(), v1.end(), v2.begin(), rel_diff.begin(), [](const double& a, const double& b) 
		{ return std::abs(a - b)/b; });
	};


//Recall: 	
//  Vector vector1 = {1, 4, 1, 2, 8, 14, 3, 5, 15, 15};					//10 elements
	Vector vector2 = {2, 3, 1, 3, 12, 4.3, 10, 11.1, 2.3, 5.5};			//10 elements
	Vector vector3 = {2, 3, 1, 3, 12, 4.3, 10, 11.1, 2.3, 5.5, 4.4}; 	//11 elements


	errorFinder<Vector, Lambda>::errorCalculator(vector1, vector2, abs_Differences);		
	errorFinder<Vector, Lambda>::errorCalculator(vector1, vector2, relative_Differences);
   

	//errorFinder<Vector, Lambda>::errorCalculator(vector1, vector3, abs_Differences);	
	//Will throw logic error because vectors are not of same size.


	return 0;	

};





















/*
	QUESTIONS:


To this end, we use the functionality in STL (in particular, std::find and std::distance). However, 
there is an interface mismatch between what we want (integral indexes) while STL works with iterators.
We morph the STL algorithms by creating adapters. 
	
	Answer the following questions:

	a) Given a sorted numeric vector v and a target value x, find the first index i such that v[i] <= x < v[i + 1]. Determine the return type.
	b) Find the maximum error between two vectors v1 and v2 in a given index range[i; j ]. We wish to compute the difference in some (customisable) norm, 
	specifically the ABSOLUTE error, RELATIVE error and the INDEX VALUES where these errors occur.

Ideally, you should use the following C++ functionality if possible:

	• Move semantics instead of copy constructors.
	• Smart pointers (if applicable).
	• Function objects and lambda functions.
	• Use as much of STL Algorithms as you can (investigate what’s in the library).

*/

/*
PART A:

std::find works with iterators. When matching the target value, it returns the iterator of the first occurrence. I wish to know the index
at which this iterator is, and thus using std::distance is useful here.

In instances where the target value is bounded by two integer values within the container, using std::upper_bound and std::lower_bound 
will be of use here.

Recall that std::find returns the first element in the range [first, last) that satisfies the underlying criteria.

std::upper_bound returns an iterator pointing to the first element in the range [first, last) that is greater than value
std::lower_bound returns an iterator pointing to the first element in the range [first, last) that is not less than (i.e. greater or equal to) value.


PART B:

ABSOLUTE ERROR is the difference (a-b)
RELATIVE ERROR is the difference (a-b)/a
-> the maximum would be the max error (of either absolute or relative) between the two vectors

The (customisable) error-finding error that you create should be customizable to return the different error types: i.e., absolute or relative.
*/














/*															QUANTNET POSTS THAT MIGHT BE USEFUL

You still need to return a value even if x is out of bounds.


std::find does not return an error when x is not found -- it returns the end iterator which could give you a run time error if you try to dereference it.

You can use if-else to handle all different cases, e.g. if (found) ..., else ...

std::find returns the iterator of the first occurrence. Your function needs to return the index of that occurrence based on the iterator that was returned.
You'd need std::distance for that

We need to use std::find and std::distance to find index "i" such that v [ i ] <= x < v[i+1].
std::find, std::find_if, std::find_if_not - cppreference.com

A few examples may help to clarify:
v = 1,2,3,4,5; x = 3; i should be index 2;
v = 1,1,2,3,4; x = 1; i should be index 1;
v = 1,3,5,8,9; x = 6; i should be index 2;
v = 1,2,3,4,5; x = 8; i should be index 5 or 999(not found);

For case 3 and 4, I think it may be hard to find "i" using just std::find? @APalley

But you will actually extend this exercise on Level 4 and use other STL algorithms which will make it easier to solve case 3 and 4.


Look into std::upper_bound and std::lower_bound with sorted arrays could be an option



ABSOLUTE ERROR is the difference (a-b)
RELATIVE ERROR is the difference (a-b)/a
-> the maximum would be the max error (of either absolute or relative) between the two vectors


"
	vectors are like v = (v1, ...,vn) etc. v2 = (y1, ...,yn)

	z = v1 - v2 = (v1-y1, ..., vn-yn)

	Then take norm of vector z.
	L^1-Norm -- from Wolfram MathWorld
"


"The largest difference between two values in two one dimensional arrays {1,2,3} and {2,3,5} would be {1,1,2}, and we'd return 2."

"Please explain what does the customisable mean here?
It means that the error-finding method that you create should be customizable to return the different error types: I.e., absolute or relative."

"
	That's right. This is the max norm (see Dr. Duffy's post above).
	Sorry, I want to know whether I understand it correctly:

	first, we have [x0,x1,...,x9],[y0,y1,...,y9], in given range, ie.[x2,x3,x4] and [y2,y3,y4], get the difference[abs(x2-y2),abs(x3-y3),abs(x4-y4)].

	then determine which one is the max, ie. abs(x3-y3) is the maximum.

	absolute error is abs(x3-y3), relative error is abs(x3-y3)/x3(or y3?), index is 3.
	

if x is less than the minimum value in the vector, then return -1,

if x is no less than the maximum value in the vector, then return v.size()-1,

for other circumstances, it should return in range[0,v.size()-1),

so the return type is int, and I may make some annotations on the return value.



"
	ie. v={1,2,3,4}

	if x=0 return 4,
	if x=4 return 4?,
	if x=5 return 4,

	Is this correct?

Yes, should all return 4 since you can't find an index such that: v[i] <= x < v[i+1]

			-> 	Yeah, and I think it could never return v.size()-1,

				If so, then exists v[v.size()-1]<=x<v[v.size()], and v[v.size()] is out of bounds.

				So the result is [0,v.size()-1) plus v.size()?
				not consistent with the one [0,v.size()-1] plus v.size() as you mentioned above.

"

"
	The question asks you to find the first index such that v < x < v[i+1], so if in your sorted vector you have duplicates or numbers 
	or higher multiplicity, it won't matter if you are using std::find.
	Recall that std::find returns the first element in the range [first, last) that satisfies the underlying criteria.

	std::upper_bound returns an iterator pointing to the first element in the range [first, last) that is greater than value
	std::lower_bound returns an iterator pointing to the first element in the range [first, last) that is not less than (i.e. greater or equal to) value.

"
*/





/*					ON STD::FIND, std::FIND_IF, and std::FIND_IF_NOT

Returns an iterator to the FIRST element in the range [first, last) that satisfies specific criteria (OR 'LAST' if there is no such iterator):

1,2) find searches for an element equal to value (using operator==)
3,4) find_if searches for an element for which predicate p returns true
5,6) find_if_not searches for an element for which predicate q returns false


The first iterator it in the range [first, last) satisfying the following condition or last if there is no such iterator:

RETURN VALUE:
1,2) *it == value is true
3,4) p(*it) != false is true
5,6) q(*it) == false is true
*/


/*			STD::DISTANCE

The number of increments needed to go from first to last. The value may be negative if random-access iterators are used and first is reachable from last

#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
    std::cout << "distance(first, last) = "
              << std::distance(v.begin(), v.end()) << '\n'
              << "distance(last, first) = "
              << std::distance(v.end(), v.begin()) << '\n';		
               //the behavior is undefined (until C++11)

}

RESULTS

distance(first, last) = 3
distance(last, first) = -3



	RECALL: An iterator is an object that points to an element in a container, such as a vector or an array. When iterating over a container, it is common
	to use a loop that iterates from the beginning of the container to one past the end of the container.

		Why? -> iterating from the beginning of the container to one past the end of the container ensures that all the elements in the container are visited,
		and that the loop terminates correctly. If the loop did not iterate to one past the end of the container, it would miss the last element in the container, 
		and the loop would not terminate correctly.

		IMPORTANT: it is important to note that dereferencing an iterator that points to one past the end of the container is undefined behavior, and can 
		cause a runtime error. Therefore, it is important to use the end() function or the equivalent iterator to indicate the end of the container, and not 
		to dereference an iterator that points to one past the end.
*/






/*
	APPROXIMATION ERROR: ABSOLUTE ERROR AND RELATIVE ERROR

The approximation error in a data value is the discrepancy between an exact value and some approximation to it. 
This error can be expressed as an absolute error (the numerical amount of the discrepancy) or as a relative error
(the absolute error divided by the data value).


In words, the ABSOLUTE error is the magnitude of the difference between the exact value and the approximation. 
The RELATIVE error is the absolute error divided by the magnitude of the exact value.
*/


/*	
	EUCLIDEAN DISTANCE IN HIGHER DIMENSIONS:


For points given by Cartesian coordinates in n-dimensional Euclidean space, the distance is:

d(p,q) = sqrt ( (p1-q1)^2 + (p2-q2)^2 + ... + (pn-qn)^2)

It may also be expressed more compactly as the norm of the Euclidean vector difference  (see: https://mathworld.wolfram.com/VectorNorm.html)

--> 


*/