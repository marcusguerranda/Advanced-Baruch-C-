//3.2/3.3) C++ Concurrency: 4. My First Master-Worker Pattern in C++11

/*Purpose: 
A common problem in parallel programming is how to balance the computational load among a set of processing elements within a parallel computer. 
For task parallel programs with no communication between tasks (or infrequent but well-structured, anonymous communication) an effective solution 
with “automatic dynamic load balancing” is to define a single master to manage the collection of tasks and collect results. Then a set of workers 
grab a task, do the work, send the results back to the master, and then grab the next task. This continues until all the tasks have been computed.
    
    Create a simple application consisting of one master and one worker. The worker is responsible for the updating of a shared resource 
    (in this case, a string) on behalf of the master. Some hints on the design of this exercise are:
        • The master initiates the computation and sets up the problem.
        • Then the master creates a bag of tasks (in our case just one worker).
        • The master waits until the job is done, consumes the results and then shuts down
*/

//Author: Andrew Guerrand

//Modification dates: 6/9/2023


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <string>
#include <sstream>


/*
a) We start with the following global data that is needed in order to implement this pattern:
    1: The resource that the worker updates.
    2: A mutex to synchronise access to the resource.
    3: A condition variable for thread notification.
    4: Two atomic Booleans to model the status of the master and worker.
*/

//Types and data needed
std::string data;   //Shared data between master and worker
std::mutex m;       //Ensures no race condition

//Synchronisation between master and worker
std::condition_variable cv;

    //Initial state of worker and master
//std::atomic<bool> workerReady = false;
//std::atomic<bool> masterReady = false;

std::atomic_flag workerReady = ATOMIC_FLAG_INIT;    //Atomic boolean-type -> guaranteed to be lock-free. Does not provide load or store operations
std::atomic_flag masterReady = ATOMIC_FLAG_INIT;    //"ATOMIC_FLAG_INIT" -> initial state is 'false'. See more information below 


/*PART B:) Create the thread function: it updates the resource by acquiring the lock, waiting on the worker ready 
           flag to be set, updating the resource and then finally notifying the master.
*/

void workerThreadFunction()
{
    std::istringstream iss(data);
    std::string word;

    while (iss >> word)
    {
        //Acquire the lock
        std::unique_lock<std::mutex> lock(m);

    //Wait for the master to set the master ready flag
        //cv.wait(lock, [] { return masterReady.load(); });     //Using atomic booleans -> std::atomic<bool>::load() -> atomically obtains the value of the atomic object
        cv.wait(lock, []{ return masterReady.test(); });        //std::atomic_flag::test() -> atomically returns the value of the flag
                                                                

        //Print the word
        std::cout << "Worker: " << word << std::endl;

    //Notify the master
        //masterReady.store(false);                             //Using atomic booleans -> std::atomic<bool>::store() -> atomically replaces the value of the atomic object with a non-atomic argument
        masterReady.clear();                                    //std::atomic_flag::clear()  -> atomically sets flag to 'false'
        cv.notify_one();
    }
}


//PART C) Create the code that implements the master’s duties. Test the code.
void masterDuties(const std::string& input)
{
    //Set the data to the user input
    data = input;

    //Create the worker thread
    std::thread workerThread(workerThreadFunction);

    std::istringstream iss(data);
    std::string word;

    while (iss >> word)
    {
        //Acquire the lock
        std::unique_lock<std::mutex> lock(m);

    //Set the master ready flag
        //masterReady.store(true);
        masterReady.test_and_set();

        //Notify the worker
        cv.notify_one();

    //Wait for the worker to print the word
        //cv.wait(lock, [] { return !masterReady.load(); });        //std::atomic<bool>::wait() -> 	blocks the thread until notified and the atomic value changes
        cv.wait(lock, [] { return !masterReady.test();});   
    }

    //Join the worker thread
    workerThread.join();
}


/*PART D) We now replace atomic Booleans by class std::atomic_flag which is a bare-bones lock-free data 
type. It does not provide load nor store operations. It has functions to set and clear. Modify the code 
accordingly and test again.
*/



int main()
{
    std::cout << "Enter text: ";
    std::string userInput;
    std::getline(std::cin, userInput);      // Format: std::getline(input_stream, string_variable, delimiter);  -> read an entire line of input until a delimiter

    masterDuties(userInput);
    
    return 0;
}


/*

PART C:
Enter text: Hello, this is my first attempt using the master worker pattern

Worker: Hello,
Worker: this
Worker: is
Worker: my
Worker: first
Worker: attempt
Worker: using
Worker: the
Worker: master
Worker: worker
Worker: pattern

*/



/*      STD::ATOMIC_FLAG

    std::atomic_flag (...)
constructs an atomic_flag

    std::atomic_flag::operator =
the assignment operator

    std::atomic_flag::clear()
atomically sets flag to false

    std::atomic_flag::test_and_set()
atomically sets the flag to 'true' and obtains its previous value.
    -If the previous value returned by test_and_set() is true, it means the flag was already set (true) before the call.
    -If the previous value returned by test_and_set() is false, it means the flag was not set (false) before the call, 
     and it has been atomically set to true by the function.

    std::atomic_flag::test()
atomically returns the value of the flag

    std::atomic_flag::wait()
blocks the thread until notified and the atomic value changes

    std::atomic_flag::notify_one()
notifies at least one thread waiting on the atomic object

    std::atomic_flag::notify_all()
notifies all threads blocked waiting on the atomic object
(public member function)


Lock-free guarantee: std::atomic_flag is guaranteed to be lock-free, which means that its operations are implemented without locks 
or other synchronization primitives. This can result in better performance and scalability in concurrent programs, as it avoids 
contention and the overhead of acquiring and releasing locks.

Compact representation: std::atomic_flag is a very lightweight atomic type compared to other specializations of std::atomic. 
It doesn't provide load or store operations, which means it doesn't need to store a value and can be implemented with a single 
hardware-supported atomic operation.

Simplicity: std::atomic_flag has a minimal interface, providing only two member functions: test_and_set() and clear(). This 
simplicity can make the code easier to reason about and reduces the chances of introducing subtle concurrency bugs.

Semaphore-like behavior: std::atomic_flag can be used as a simple binary semaphore. The test_and_set() function acts as a 
lock acquisition, attempting to set the flag and returning its previous value. If the flag was already set, it indicates 
that another thread holds the lock. The clear() function acts as a lock release, clearing the flag to allow other threads to acquire the lock


*/



/*  ERROR-LOG AND SOLUTIONS IMPLEMENTATION

ERROR 1: 

These two lines are not equivalent!
-> load() when using std::atomic<bool>
-> test() when using std::atomic_flag  

        cv.wait(lock, [] { return masterReady.load(); });     //Using atomic booleans -> std::atomic<bool>::load() -> atomically obtains the value of the atomic object
        cv.wait(lock, []{ return masterReady.test(); });        //std::atomic_flag::test() -> atomically returns the value of the flag

The first line, cv.wait(lock, [] { return masterReady.load(); }), uses the load() member function of std::atomic<bool> to atomically 
obtain the value of the atomic object masterReady. It waits on the condition variable cv until the value of masterReady is true.

The second line, cv.wait(lock, []{ return masterReady.test(); }), uses the test() member function of std::atomic_flag to atomically 
obtain the value of the flag masterReady. However, the test() function of std::atomic_flag returns the previous value of the flag and 
simultaneously sets it to true. It does not return the current value of the flag.

So, in the second line, cv.wait(lock, []{ return masterReady.test(); }), the condition masterReady.test() will always evaluate to true, 
and the thread will wait indefinitely on the condition variable cv. This behavior is not equivalent to the first line, 
cv.wait(lock, [] { return masterReady.load(); }), where the thread waits until the value of masterReady becomes true.



*/