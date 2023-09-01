//3.4) C++11 Tasks. 6) Task Graphs: Implementation in C++11

//Purpose: Working with dependency graphs

//Author: Andrew Guerrand

//Modification dates: 6/20/2023

#include <iostream>
#include <future>
#include <chrono>
#include <cmath>

//IMPORTANT -----------------------------------> While some code may seem redundant, I believe that creating new integers, futures, etc. every time 
//                                               contributes to the proper comparing of performances between methods. 


//Four very basic functions.
int F1(int& num)
{
    return num+1;
}

int F2(int& num)
{
    return num*2;
}

int F3(int& num)
{
    return std::pow(num,3);
}

int F4(int& numa, int& numb)
{
    return numb - numa;
}

int main()
{

//PART A: single threaded
    auto start = std::chrono::high_resolution_clock::now();
    int a{4};
    int b = F1(a);
    int c= F2(a);
    int d = F3(c);
    int f = F4(b,d);
    auto end = std::chrono::high_resolution_clock::now();
    auto timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end -start);
    std::cout << "\nPART A time: " << timer.count() << " ns" << std::endl;


//PART B: using std::async and std::future
//  Not the most beautiful code, but this makes the most sense in terms of efficiency to avoid unnecessary dependencies, and sequential execution
    
    start = std::chrono::high_resolution_clock::now();
    std::future<int> futureB = std::async(std::launch::async, F1, std::ref(a));
    std::future<int> futureC = std::async(std::launch::async, F2, std::ref(a));
    int b_async = futureB.get();
    int c_async = futureC.get();
    std::future<int> futureD = std::async(std::launch::async, F3, std::ref(c_async));
    int d_async = futureD.get();
    int f_async = F4(b_async, d_async);
    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "PART B time: " << timer.count() << " ns" << std::endl;

//Surprisingly, part B is slower, but I am not entirely surprised. The reason is that std::async and std::future introduces additional overhead. 
//Given that the code is very simple here, the single-thread is much faster than the asynchronous execution.

//PART C: using promises. 
    //Start timer
    start = std::chrono::high_resolution_clock::now();

    //Instantiating promises
    std::promise<int> promiseB;
    std::promise<int> promiseC;
    std::promise<int> promiseD;

    //Defining appropriate futures
    std::future<int> a_futureB = promiseB.get_future();
    std::future<int> a_futureC = promiseC.get_future();
    std::future<int> a_futureD = promiseD.get_future();

    //Launch threads and set values from promises
    std::thread thread1([&promiseB, &a]() {
        promiseB.set_value(F1(a));
    });

    std::thread thread2([&promiseC, &a]() {
        promiseC.set_value(F2(a));
    });

    int c_prom = a_futureC.get();
    std::thread thread3([&promiseD, &c_prom]() {
        promiseD.set_value(F3(c_prom));
    });

    //Get values from futures
    int b_prom = a_futureB.get();
    int d_prom = a_futureD.get();
    int f_prom = F4(b_prom, d_prom);

    //Join threads
    thread1.join();
    thread2.join();
    thread3.join();

    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "PART C time: " << timer.count() << " ns" << std::endl;

//PART D: Using packaged tasks

    //Start time
    start = std::chrono::high_resolution_clock::now();

    //Instantiate packaged tasks
    std::packaged_task<int(int&)> task1(F1);
    std::packaged_task<int(int&)> task2(F2);
    std::packaged_task<int(int&)> task3(F3);

    //Futures and getting future value from packaged tasks
    std::future<int> p_futureB = task1.get_future();
    std::future<int> p_futureC = task2.get_future();
    std::future<int> p_futureD = task3.get_future();

    //Threads
    std::thread p_thread1(std::move(task1), std::ref(a));
    std::thread p_thread2(std::move(task2), std::ref(a));
    int c_packaged = p_futureC.get();
    std::thread p_thread3(std::move(task3), std::ref(c_packaged));

    int b_packaged = p_futureB.get();
    int d_packaged = p_futureD.get();
    int f_packaged = F4(b_packaged, d_packaged);

    p_thread1.join();
    p_thread2.join();
    p_thread3.join();

    end = std::chrono::high_resolution_clock::now();
    timer = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "PART D time: " << timer.count() << " ns" << std::endl;


//Conclusion: currently, performance, in decreasing order, is: single-tread, packaged tasks, promises, and finally std::async/std::future

    return 0;
}