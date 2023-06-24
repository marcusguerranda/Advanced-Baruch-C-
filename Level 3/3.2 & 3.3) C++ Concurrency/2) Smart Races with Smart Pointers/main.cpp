//3.2/3.3 C++ Concurrency: 2. Smart Races with Smart Pointers

/*Purpose:
    Show how we can simulate (undesirable) non-deterministic race conditions when multiple threads access 
    functions that use shared pointers. This is good to know if you are considering porting single-threaded
    code that makes (possibly extensive) use of smart pointers and we wish to avoid race conditions and non-deterministic values.
*/

//Author: Andrew Guerrand

//Modification dates: 6/8/2023


#include <iostream>
#include <memory>
#include <mutex>
#include <chrono>
#include <array>
#include <thread>
#include <random>


struct X
{
    double value;

    X(): value(0.0) {};

    void operator () ()
    {
        std::cout << value << std::endl;
    }
};

//C++11
template <typename T>
using GenericPointerType = std::shared_ptr<T>;
using PointerType = GenericPointerType<X>;


std::mutex global_mutex;    //Mutex to secure printing of values when using Modify()
//PART A: 
//Function that accepts a smart pointer and a new value for its state. The body should actually update the state 
//and we should introduce enough latency (delay) in order to trigger a race condition; for example, you generate 
//a uniform random number using C++ random library and then sleep for that amount of time.
void Modify(PointerType& p, double newVal)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(100,900);

    auto sleep_time = std::chrono::milliseconds(dis(gen));
    std::this_thread::sleep_for(sleep_time);

    p-> value= newVal;

    global_mutex.lock();
    std::cout << "Value at hand is: " << p->value << std::endl;
    global_mutex.unlock();

    //Note: what would create a race condition would be if multiple threads try to access and modify the shared state without proper synchronization. 
}


int main()
{
//PART B: Create an array of 100 threads, fire each one up (each one has a thread function Modify() and a given value that will be the new value 
//        of the instance of PointerType)

    std::vector<std::thread> vector100{100};
    int changingVal = 0; //Value which will be increment by one everytime. This will show cleary the race condition at hand

    for (auto& thread: vector100) 
    {
        PointerType x = std::make_shared<X>();
        thread = std::move(std::thread(Modify, std::ref(x), changingVal));
        changingVal++; //Increment changing value to notice race condition
    }

    for (auto& thread: vector100) 
    {
            thread.join();
    }

/*PART C: Output can be seen below. I notice that: 1. assignment of new value is all over the place (because not protected by synchronization primitives), and
that 2) the printing changes everytime I run my code. Race condition = multiple threads trying to modify the same value of Pointype instance x, leading
to inconsistent results.

Value at hand is: 37
Value at hand is: 37
Value at hand is: 0
Value at hand is: 0
Value at hand is: 75
Value at hand is: 33
Value at hand is: 33
Value at hand is: 33
Value at hand is: 33
Value at hand is: 33
Value at hand is: 42
Value at hand is: 95
Value at hand is: 95
Value at hand is: 77
Value at hand is: 77
Value at hand is: 77
Value at hand is: 49
Value at hand is: 49
Value at hand is: 49
Value at hand is: 49
Value at hand is: 49
Value at hand is: 26
Value at hand is: 26
Value at hand is: 56
Value at hand is: 52
Value at hand is: 67
Value at hand is: 67
Value at hand is: 65
Value at hand is: 65
Value at hand is: 55
Value at hand is: 55
Value at hand is: 55
Value at hand is: 54
Value at hand is: 25
Value at hand is: 25
Value at hand is: 25
Value at hand is: 86
Value at hand is: 86
Value at hand is: 86
Value at hand is: 86
Value at hand is: 86
Value at hand is: 41
Value at hand is: 41
Value at hand is: 41
Value at hand is: 41
Value at hand is: 14
Value at hand is: 14
Value at hand is: 22
Value at hand is: 22
Value at hand is: 22
Value at hand is: 94
Value at hand is: 94
Value at hand is: 94
Value at hand is: 99
Value at hand is: 99
Value at hand is: 44
Value at hand is: 44
Value at hand is: 32
Value at hand is: 32
Value at hand is: 32
Value at hand is: 31
Value at hand is: 31
Value at hand is: 4
Value at hand is: 4
Value at hand is: 3
Value at hand is: 3
Value at hand is: 58
Value at hand is: 58
Value at hand is: 58
Value at hand is: 34
Value at hand is: 34
Value at hand is: 68
Value at hand is: 21
Value at hand is: 51
Value at hand is: 96
Value at hand is: 96
Value at hand is: 96
Value at hand is: 12
Value at hand is: 12
Value at hand is: 11
Value at hand is: 11
Value at hand is: 36
Value at hand is: 36
Value at hand is: 36
Value at hand is: 7
Value at hand is: 16
Value at hand is: 16
Value at hand is: 16
Value at hand is: 40
Value at hand is: 40
Value at hand is: 81
Value at hand is: 81
Value at hand is: 90
Value at hand is: 90
Value at hand is: 90
Value at hand is: 29
Value at hand is: 98
Value at hand is: 13
Value at hand is: 13
Value at hand is: 57
*/




    return 0;
}