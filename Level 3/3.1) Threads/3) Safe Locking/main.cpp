//3.1) Threads: 3.Safe locking

/*
Purpose:

    We continue with the code in exercise 2 by using two special lock mechanisms:
        •   The class std::lock_guard: a mutex wrapper that provides a convenient RAII-style mechanism for 
            owning a mutex or several mutexes (since C++17) for the duration of a scoped block.

        •   The class std::unique_lock: a general-purpose mutex ownership wrapper allowing deferred 
            locking, time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use 
            with condition variables.

    In other words, std::unique_lock provides more flexibility than std::lock_guard by relaxing 
    invariants; the former does not necessarily own the mutex that it is associated with.
*/

//Author: Andrew Guerrand

//Modification dates: 5/7/2023

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

//Counter variable initialized with 0 and brace initializers
int count_lockguard{0};

//Define global mutexes such that critical section of each function are properly synchronized and avoids potential contention between different tasks
//Note to self: define mutexes as global function rather than within scope, s.t threads need to acquire this said-mutex to access locks
std::mutex mutex_lock;                      //Global mutex for FreeFunction_Lock
std::mutex mutex_trylock;                   //Global mutex for FreeFunction_TryLock
std::timed_mutex mutex_timed_trylockfor;    //Global timed mutex for FreeFunction_TryLockFor
std::timed_mutex mutex_timed_trylockuntil;  //Global timed mutex for FreeFunction_TryLockUntil


//PART A: using std::lock_guard
//Free function using .lock() and .unlock()
void FreeFunction_Lock()
{
    //Lock guard wrapper around mutex providing a mechanism for owning a mutex (or several) for the duration of a scoped block.
    std::lock_guard<std::mutex> lockguard(mutex_lock);
    std::cout << "NORMAL LOCK used." << std::endl;
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
    count_lockguard++;

    //The lock_guard will automatically unlock when it goes out of scope
};


//PART C: Function using std::unique_lock::try_lock
//NOTE FOR SELF: see https://cplusplus.com/reference/mutex/unique_lock/
void FreeFunction_TryLock()
{
    std::unique_lock<std::mutex> uniqueLock(mutex_trylock);

    try
    {
            //uniqueLock.try_lock(); --> IMPORTANT: results in a deadlock because uniqueLock already owns the lock.
            std::cout << "TRY_LOCK used." << std::endl;
            std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;

            //Note: while ::try_lock() is more richly defined than lockguards, contrarily to lockguards, we need to unlock() when done dealing with shared resource at risk 
            uniqueLock.unlock();
    }
    catch (const std::system_error& error)
    {
        if(error.code() == std::errc::operation_not_permitted) {std::cout << "ERRROR: Operation not permitted." << std::endl;}
        else if(error.code() == std::errc::resource_deadlock_would_occur){std::cout << "ERROR: acquiring the lock would result in a deadlock situation."<< std::endl;}
        else if (error.code() == std::errc::resource_unavailable_try_again){std::cout << "ERROR: mutex temporarily unavailable." << std::endl;}
        else{//Handle other exceptions
        std::cout << "An unknown exception occurred." << std::endl;}
    }
    catch (...)
    {
        //Handle other exceptions
        std::cout << "An unknown exception occurred." << std::endl;
    }
}


//PART D: using try_lock_for 

//Function using std::unique_lock::try_lock_for
//NOTE FOR SELF: See -> https://cplusplus.com/reference/mutex/unique_lock/
void FreeFunction_TryLockFor()
{

    std::unique_lock<std::timed_mutex> lock_for(mutex_timed_trylockfor, std::defer_lock);

    try
    {
            lock_for.try_lock_for(std::chrono::milliseconds(10));
            std::cout << "TRY_LOCK_FOR used." << std::endl;
            std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
            
            //PART E
            lock_for.unlock();
    }
    catch (const std::system_error& error)
    {
        if(error.code() == std::errc::operation_not_permitted) {std::cout << "ERRROR: Operation not permitted." << std::endl;}
        else if(error.code() == std::errc::resource_deadlock_would_occur){std::cout << "ERROR: acquiring the lock would result in a deadlock situation."<< std::endl;}
        else if (error.code() == std::errc::resource_unavailable_try_again){std::cout << "ERROR: mutex temporarily unavailable." << std::endl;}
        else{//Handle other exceptions
        std::cout << "An unknown exception occurred." << std::endl;}
    }
    catch (...)
    {
        //Handle other exceptions
        std::cout << "An unknown exception occurred." << std::endl;
    }
}


//PART F:
//Function using std::unique_lock::try_lock_until
//NOTE FOR SELF: See -> https://cplusplus.com/reference/mutex/unique_lock/try_lock/
void FreeFunction_TryLockUntil()
{
    std::unique_lock<std::timed_mutex> lock_until(mutex_timed_trylockuntil, std::defer_lock);

    try
    {       
            //With try_lock_until, I need to specify the time point until which the lock should be attempted 
            auto timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(200);

            lock_until.try_lock_until(timeout);
            std::cout << "TRY_LOCK_FOR used." << std::endl;
            std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;

            //Note: while ::try_lock() is more richly defined than lockguards, contrarily to lockguards, we need to unlock() when done dealing with shared resource at risk 
            
            //PART E
            lock_until.unlock();
    }
    catch (const std::system_error& error)
    {
        if(error.code() == std::errc::operation_not_permitted) {std::cout << "ERRROR: Operation not permitted." << std::endl;}
        else if(error.code() == std::errc::resource_deadlock_would_occur){std::cout << "ERROR: acquiring the lock would result in a deadlock situation."<< std::endl;}
        else if (error.code() == std::errc::resource_unavailable_try_again){std::cout << "ERROR: mutex temporarily unavailable." << std::endl;}
        else{//Handle other exceptions
        std::cout << "An unknown exception occurred." << std::endl;}
    }
    catch (...)
    {
        //Handle other exceptions
        std::cout << "An unknown exception occurred." << std::endl;
    }
}



int main()
{

//PART A: USING LOCK_GUARD NOW and creating a function that increments a counter by multiple threads.
    std::cout << "\nPART A: Using std::lock_guard" << std::endl;

    //Store threads in a vector
    std::vector<std::thread> vec_thr_lockguard;
    std::vector<std::thread> vec_thr_trylock;
    std::vector<std::thread> vec_thr_trylockfor;
    std::vector<std::thread> vec_thr_trylockuntil;

//LOCK GUARDS
    //Measure processing time
    auto start = std::chrono::system_clock::now();

    //Emplace_back threads into appropriate vectors. I do so so that I can join them easier later on. It is the same as creating threads everytime, giving a name, and then joining manually...
    for(int i=0; i<5; i++)
    {
        vec_thr_lockguard.emplace_back(FreeFunction_Lock);
    }

    //Join all threads
    for (auto& thread : vec_thr_lockguard) {
        thread.join();
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Finished computation within: " << elapsed_seconds.count() << "s.\n";

    std::cout << "Counter using lock guard, given 5 streams, is: " << count_lockguard << std::endl;
    

//PART C:

//TRY_LOCK
    std::cout << "\nPART C: Using std::unique_lock::try_lock() " << std::endl;

    //Measure processing time
    start = std::chrono::system_clock::now();

    //Emplace_back threads into appropriate vectors. I do so so that I can join them easier later on. It is the same as creating threads everytime, giving a name, and then joining manually...
    for(int i=0; i<5; i++)
    {
        vec_thr_trylock.emplace_back(FreeFunction_TryLock);
    }

    //Join all threads
    for (auto& thread : vec_thr_trylock) {
        thread.join();
    }

    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Finished computation within: " << elapsed_seconds.count() << "s.\n";


//PART D:

//TRY_LOCK_FOR
    std::cout << "\nPART D: Using std::unique_lock::try_lock_for() " << std::endl;
    
    //Measure processing time
    start = std::chrono::system_clock::now();

    //Emplace_back threads into appropriate vectors. I do so so that I can join them easier later on. It is the same as creating threads everytime, giving a name, and then joining manually...
    for(int i=0; i<5; i++)
    {
        vec_thr_trylockfor.emplace_back(FreeFunction_TryLockFor);
    }

    //Join all threads
    for (auto& thread : vec_thr_trylockfor) {
        thread.join();
    }

    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Finished computation within: " << elapsed_seconds.count() << "s.\n";


//PART F:

//TRY_LOCK_UNTIL
    std::cout << "\nPART F: Using std::unique_lock::try_lock_until() " << std::endl;
    
    //Measure processing time
    start = std::chrono::system_clock::now();

    //Emplace_back threads into appropriate vectors. I do so so that I can join them easier later on. It is the same as creating threads everytime, giving a name, and then joining manually...
    for(int i=0; i<5; i++)
    {
        vec_thr_trylockuntil.emplace_back(FreeFunction_TryLockUntil);
    }

    //Join all threads
    for (auto& thread : vec_thr_trylockuntil) {
        thread.join();
    }

    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Finished computation within: " << elapsed_seconds.count() << "s.\n";


/*PART G: Releasing an associated mutex without unlocking

    -> use std::unique_lock::release() function. This return a pointer to the managed object, releasing ownership over it.
    -> The function release the ownership of the associated mutex from the "std::unique_lock" object without unlocking it. The function 
       returns a pointer to the released mutex. The mutex REMAINS locked, but the std::unique_lock oject will no longer be associated       
       with any mutex.

Why use std::unique_lock::release()?
   - Transfer ownership: If you have two std::unique_lock objects and you want to transfer ownership of the mutex from one object to the other, 
     you can call release() on the first std::unique_lock object and then construct a new std::unique_lock object using the returned pointer.

   - Manual unlocking: If you need to perform some operations on the mutex that require it to be explicitly unlocked, you can call release() 
     to get a pointer to the mutex and then use that pointer to manually unlock the mutex when needed.
*/

    std::cout << std::endl;
    return 0;
}






/*
NOTES FOR SELF:

IN SUM: std::unique_lock is a more feature-rich version of std::lock_guard and provides additional functionalities and flexibility. While std::lock_guard is a 
simple RAII wrapper that acquires the lock on construction and releases it on destruction, std::unique_lock offers more control over the lock by providing 
features such as deferred locking, timed locking, and lock ownership transfer.

std::unique_lock: general-purpose mutex ownership wrapper allowing deferred locking, time-constrained attempts at locking, recursive locking, 
                  transfer of lock ownership, and use with condition variables.

Available functionalities include:
        •   std::unqiue_lock::lock():         locks (i.e., takes ownership of) the associated mutex
        •   std::unique_lock::try_lock():     tries to lock (i.e., takes ownership of) the associated mutex without blocking
        •   std::unique_lock::try_lock_for(): attempts to lock (i.e., takes ownership) of the associated TimedLockable mutex, returns if the mutex has been unavailable for the specified time duration
        •   std::unique_lock::unlock():       tries to lock the associated TimedLockable mutex, returns if the mutex has been unavailable until specified time point has been reached  

MODIFIERS:        
        •   std::unique_lock::swap():         swaps states with another std::unique_lock  
        •   std::unique_lock::release():      disassociates the associated mutex without unlocking it


------------------------------------------------------------------------------------------------------
std::mutex::try_lock


Lock mutex if not locked
Attempts to lock the mutex, without blocking:
    If the mutex isn't currently locked by any thread, the calling thread locks it (from this point, and until its member unlock is called, the thread owns the mutex).
    If the mutex is currently locked by another thread, the function fails and returns false, without blocking (the calling thread continues its execution).
    If the mutex is currently locked by the same thread calling this function, it produces a deadlock (with undefined behavior). See recursive_mutex for a 
    mutex type that allows multiple locks from the same thread.

This function may fail spuriously when no other thread has a lock on the mutex, but repeated calls in these circumstances shall succeed at some point.

All lock and unlock operations on the mutex follow a single total order, with all visible effects synchronized between the lock operations and previous unlock operations on the same object
------------------------------------------------------------------------------------------------------

Difference between std::unique_lock::try_lock_for and std::unique_lock::try_lock_until?

std::unique_lock::try_lock_for takes a duration as an argument and attempts to acquire the lock for that duration. 
It will keep trying to acquire the lock until either the lock is successfully acquired or the specified duration has elapsed. 
If the lock is acquired, the function returns true; otherwise, it returns false.
-> takes a std::chrono::duration argument

std::unique_lock::try_lock_until takes a time point as an argument and attempts to acquire the lock until that time point is reached.
It will keep trying to acquire the lock until either the lock is successfully acquired or the specified time point is reached.  
If the lock is acquired, the function returns true; otherwise, it returns false.
-> takes a std::chrono::time_point argument

std::chrono::duration and std::chrono::time_point differ in that:
    - std::chrono::duration represents a time duration or interval, while 
    - std::chrono::time_point represents a specific point in time. 
    
Durations measure the difference between two time points, while time points represent absolute moments in time.

*/