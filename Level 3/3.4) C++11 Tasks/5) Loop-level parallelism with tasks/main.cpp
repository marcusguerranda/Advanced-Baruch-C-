//3.4+ C++11 Tasks. 5) Loop-Level Parallelism with tasks

/*Purpose: Compute reduction/aggregated variables relating to numerical array. In orderto scope the problem, we focus on summing the values of numeric arrays
         -using 'accumulate' function.

        Main requirements:
        - speedup improvements
        - serial equivalence (multi-threaded solutions gives the same results as the single-threaded solution)

*/     

//Author: Andrew Guerrand

//Modification dates: 6/19/2023

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <numeric>
#include <future>
#include <omp.h>
#include <execution>

//Algorithm usesa divide-and-conquer approach, splitting the range into smaller subranges until the size of the subrange is small enough to be process
//directly or until the base case size <= 1000 is reached. Goal is to use multiple threads to process different parts of the array/vector simultaneously.
int FunctionB(std::vector<int>& vector, std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    //Last case: checking if the size of the array is less than 1,000, we then side-track parallel processing by calling std::accumulate() directly
    //Most importantly, it is crucial to account for the non-possibility of dividing further the said-array in two 
    //-> check if division between ((end - start)/2 < start). If so, then just std::accumulate
    //Example -> range from 0 to 3 divided in two gives the midpoint 1. 
    //If such is the case, then division does 
    if (std::distance(begin, end) < 1000)
    {
        //Use std::accumulate for small arrays
        return std::accumulate(begin, end, 0);
    }
    else
    {
        //Divide the range and process left half recursively while running the right half asynchronously
        auto mid = begin + std::distance(begin, end) / 2;

        //Note: crucial to use std::ref(). std::async expects for its arguments to be copyable or movable. So std::ref() is a reference wrapper, and ensures
        //that the vector object is correctly accessed and modified by the parellel recursive calls.
        auto right_handle = std::async(std::launch::async, FunctionB, std::ref(vector), mid, end);  

        return FunctionB(std::ref(vector), begin, mid) + right_handle.get();    //Leftss + Right's
    }
}


//PART F: Write parallel code that uses std::accumulate() with a binary function as last parameter. Test the algorithm by computing the product of the elements of
//        an array
//        Binary functions -> takes two arguments and produce a result. Could be function objects, lambdas, or STL function objects (divides(), multiplies(), plus(), minus()...)
//        Here, we are asked for the product of the elements in the array.
int ParallelProduct(const std::vector<int>& vec)
{

    std::packaged_task<int(const std::vector<int>&, int)> task1([](const std::vector<int>& vec, int initial) 
    {
        return std::accumulate(vec.begin(), vec.end(), initial, std::multiplies<int>());
    });
    
    std::future<int> future = task1.get_future();

    std::thread thread(std::move(task1), std::cref(vec),1);

    int product = future.get();
    thread.join();

    return product;
}



int main()
{
//Part A: Create a huge numeric array and sum its elements using std::accumulate. Measure processing time.
    std::cout << "\nPART A: Using std::accumulate. Measure processing time.\n" << std::endl;;
    const int size = 10'000'000;

    std::vector<int> vector1;
    for(int i=0; i < size; i++)
    {
        vector1.push_back(1);
    }

    //Start timer
    auto start = std::chrono::high_resolution_clock::now();         //Start timer
    int sum = std::accumulate(vector1.begin(), vector1.end(), 0);   //Accumulating algorithm using single-thread -> DON'T FORGET initial value as third argument!!
    auto end = std::chrono::high_resolution_clock::now();           //End timer
    

    //Important: cast time 
    double timer = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();  //-> explicitly casts the duration to a specific unit of measurement
    //double difference = end-start;    -> will match the type of the time points, preserving the precision nd units of the original time point representation

    std::cout << "Aggregating vector of 10,000,000 1s is equal to: " << sum << " , and the time it takes to calculate such a sum is: " << timer << " ms." << std::endl;

//PART B: Creating code to parallelise the code in part a). To this end, we split the index space into two halves;
//        the right half is run in an asynchronous task while the left part constitutes a recursive call to the algorithm for the appropriate
//        index range.
//        If the size of the array is less than 1,000, we then sie-track parallel processing by calling std::accumulate() directly.

/*

    std::cout << "\nPART B/C: See instructions in comment." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    sum = FunctionB(vector1, vector1.begin(), vector1.end());     //Recall that the .end() iterator will go one past the last element... ;)
    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
*/

//PART C: measuring the speed of the code in part B.        
    std::cout << "Aggregating vector of 10,000,000 1s is equal to: " << sum << " , and the time it takes to calculate such a sum is: " << timer << " ms." << std::endl;
    //Seems quite slow. I would definitely load balance if asked. The recursive calling is cumbersome I suspect



//PART D: Using OMP (part of Visual Studio)
/*
    std::cout << "\nPart D: Using OMP" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    omp_set_num_threads(2);
    int sumParallel=0;
    #pragma omp parallel for reduction (+:sumParallel)
    for (long i = 0; i < vector1.size(); ++i)
    {
        sumParallel += vector1[i];
    }
    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout << "Aggregating vector of 10,000,000 1s is equal to: " << sumParallel << " , and the time it takes to calculate such a sum is: " << timer << " ms." << std::endl;
*/

//PART F: Write parallel code that use std::accumulate() with a binary function as last parameter. Test the algorithm by computing the product of the elements of an array.

    //Create new vector and emplace back first 100 elements in container
    std::vector<int> vector2;
    for(int i =1; i<= 100; i++)
    {
        vector2.emplace_back(i);
    }

    int product_result = ParallelProduct(vector2);
    std::cout<< "\nPART F: Product of elements in vector2 is equal to: " << product_result << std::endl;

//PART G: Compare performance improvements by using the new parallel features in C++. We focus on three STL algorithms 
//         (or algorithms of your choice) as applied to std::vector, namely: std::transform, std::sort, std::find.

    //Results output
    std::vector<int> outputs;
    outputs.resize(100);

//WITH PARALLELIZATION:
    start = std::chrono::high_resolution_clock::now();
    std::transform(std::execution::par, vector2.begin(), vector2.end(), outputs.begin(), [](int x) {return x *3; });
    std::sort(std::execution::par, vector2.begin(), vector2.end());
    auto it = std::find(std::execution::par, vector2.begin(), vector2.end(), 50);
    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    std::cout << "STD::TRANSFORM using parallelization, final time: " << timer << " nanoseconds" << std::endl;

// SEQUENTIAL/WITHOUT PARALLELIZATION:
    start = std::chrono::high_resolution_clock::now();
    std::transform(vector2.begin(), vector2.end(), outputs.begin(), [](int x) {return x *3; });
    std::sort(vector2.begin(), vector2.end());
    it = std::find(vector2.begin(), vector2.end(), 50);
    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    std::cout << "No parallelization/sequential, final time: " << timer << " nanoseconds" << std::endl;
    
    //using parallelization, final time:    11200 nanoseconds, or 11.2 microseconds
    //Sequential, final time:               12200 nanoseconds, or 12.2 microseconds


    std::cout<<std::endl;
    return 0;
}
