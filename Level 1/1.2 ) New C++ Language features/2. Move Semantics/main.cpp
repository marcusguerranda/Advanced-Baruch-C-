//main.hpp 

//1.2.1 New C++ Language Features ("Improving your classes")
//2. Move Semantics 
//Author: Andrew Guerrand

//Purpose: Controlling for default creation of certain special member functions, using move semantics and rvalue references, and
//         creating move constructor and move operator

//Modification date: 4/7/2023

#include "C.hpp"     //Header file for C class
#include <vector>    //Header file to use vector library
#include <string>    //Header file for string class
#include <utility>   //Header file to use std::move, for example
#include <chrono>    //Header file to use std::chrono library

//Generic function to move contents from one container to another (of same type) and reporting the time it takes to perform such an operation
template<typename T>
double move_contents(T& source, T& target) 
{
    auto start = std::chrono::high_resolution_clock::now();
    target = std::move(source);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double>> (end - start).count();
}

//Generic function to print contents of many different types of data containers
template <typename Container>
void print_contents(const Container& c)
{
    std::cout << "Elements are: ";
    for (const auto& element : c)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

//User-defined code to swap two objects using COPY constructor
template <typename T>
void SwapCopyStyle(T& a, T& b)
{ // Swap a and b in copying way; temporary object needed
   T tmp(a);               // Copy constructor
   a = b;                  // Copy all elements from b to a
   b = tmp;                // Copy all elements from tmp to b
}

//User-defined code to swap two objects using MOVE semantics
//NOTE TO SELF: exercise asks specifically to use move semantics. So use && for parameters, and to make vectors as rvalues, pass them on with
//std::move!
template <typename T>
void SwapMoveStyle(T&& a, T&& b)
{
    T tmp(std::move(a));   // Move constructor
    a = std::move(b);      // Move all elements from b to a
    b = std::move(tmp);    // Move all elements from tmp to b
}

int main()
{

//PART A: 

   //Create initial string with some content in it, and a target string
   std::string initial_str = "Hello. I will be moving this string!";
   std::string target_str;                                               //Empty string, in which I'll move contents from initial_str

   //Print the contents of the initial and target string BEFORE the move

   std::cout << "Initial string content, before the move: " << initial_str << std::endl;
   std::cout << "Target string content should be empty before the move. Here is what it prints: " << target_str << std::endl;

   //Move the contents from initial string to target string
   target_str = std::move(initial_str);

   //Print the contents of the initial and target string AFTER the move
   std::cout << "Initial string content, after the move: " << initial_str << std::endl;
   std::cout << "Target string content should be empty. Here is what it prints: " << target_str << std::endl;



//PART B:

//Note: I found it tiring to have to reimplement moving contents, and measuring the time it took. I wrote a function to make this more systematic above.
// See moveContents() function

   //Create initial and target vectors
   std::vector<int> initial_vec = {1, 2, 3, 4, 5};    //Initial vector, which contains some integers
   std::vector<int> move_vec;                         //Move vector, which is empty

   //Check the contents in vectors PRIOR to moving content, using print_contents() function
   print_contents(initial_vec);                       
   print_contents(move_vec);

   //Calculate and print the time it took to move the vector
   //Note: the usage of std::move is counterintuitive to the implementation of move_contents() function.
   //      I could have simply called std::chrono in between the move operation and calculate the difference.
   //      However, I wanted to create a generic function that took any types of data containers, moved the contents, and calculated the time to perform
   //      such an operation. Obviously, such is done without using the move constructor and the move assignment operator. 
   double move_time = move_contents(initial_vec, move_vec);
   std::cout << "Time to move vector: " << move_time << " nanoseconds." << std::endl;

   //Check the contents in vectors AFTER moving content, using print_contents() function
   print_contents(initial_vec);                       
   print_contents(move_vec);

   //Calculate and print the time it takes to use a copy constructor
   auto start = std::chrono::high_resolution_clock::now();
   std::vector<int> copy_vector(initial_vec);
   auto end = std::chrono::high_resolution_clock::now();
   auto elapsed_seconds = end - start;
   std::cout << "Time to use copy constructor: " << elapsed_seconds.count() << " nanoseconds." << std::endl;

   //Calculate and print the time it takes to use a copy assignment statement
   start = std::chrono::high_resolution_clock::now();
   std::vector<int> copy_assignment_vector;
   copy_assignment_vector = initial_vec;
   end = std::chrono::high_resolution_clock::now();
   elapsed_seconds = end - start;
   std::cout << "Time to use copy assignment statement: " << elapsed_seconds.count() << " nanoseconds." << std::endl;

//Conclusion: moving content is much faster, if we specifically want to move the content and remove the content from initial container.


//PART C:

/*
   Answer:

   In the provided SwapCopyStyle function, three temporary copies are going to be created:
   one will be created when 'a' is copied to 'tmp', one when 'b' is copied to 'a', and one when 'tmp' is copied to 'b'.

   Time complexity of this function, in effect, is O(n), where n is the size of the object being swapped (in effect, it involves copying every 
   element of the object)

   IMPORTANT:

   I have thus created SwapMoveStyle, which is a function based on move semantics to swap two objects. It's time complexity will be O(1).
   Indeed, what is really happening is that it swaps pointers to the memory blocks that hold the objects' data, without copying anything.
*/
   std::cout << "PART C: MOVE SEMANTICS" << std::endl;

   std::vector<int> vector_move1(10000000, 3);   //Allocating 1000000 threes in first vector
   std::vector<int> vector_move2(10000000, 8);   //Allocating 1000000 eights in second vector

   //Timing the COPY-style swap
   auto start_copy = std::chrono::high_resolution_clock::now();
   SwapCopyStyle(vector_move1, vector_move2);
   auto end_copy = std::chrono::high_resolution_clock::now();


   // Time the move-style swap
   auto start_move = std::chrono::high_resolution_clock::now();
   SwapMoveStyle(std::move(vector_move1), std::move(vector_move2));
   auto end_move = std::chrono::high_resolution_clock::now();

   auto duration_copy = end_copy - start_copy;
   auto duration_move = end_move - start_move;
   double difference = std::chrono::duration_cast<std::chrono::microseconds>(duration_copy - duration_move).count() / 1000000.0;

   std::cout << "The difference between copy-style swap and move-style swap for moving 1000000 elements in two vectors is: " << difference << " seconds." << std::endl;

   return 0;  
};
