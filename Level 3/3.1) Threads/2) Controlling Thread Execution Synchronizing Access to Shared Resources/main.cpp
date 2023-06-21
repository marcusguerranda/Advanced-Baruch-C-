//3.1) Threads: 2. Controlling Thread execution: Synchronizing access to shared resources

/*Purpose:
    Synchronise access to the shared resource that is the console. In this 
    exercise we use synchronising mechanisms to make the code thread-safe and hence avoid race conditions. 
    In short, we use locking mechanisms to ensure that only one thread can access the console at one time.  
*/

//Author: Andrew Guerrand

//Modification dates: 6/4/2023

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>


//Mutual exclusion to synchronize console access
std::mutex console_mutex;

//Free function using .lock() and .unlock()
void FreeFunction_Lock()
{
    console_mutex.lock();
    std::cout << "NORMAL LOCK used." << std::endl;
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
    console_mutex.unlock();

    //Obviously, if I print the thread IDs outside of the locks, I get overlapping prints because threads are so fast. 
    //Including so within locks guarantees protection from race conditions, deadlocks, etc.
}


//Free function but now using try_lock(). See below for personal notes on the usefulness of try_lock()
void FreeFunction_TryLock()
{
    if (console_mutex.try_lock())
    {
        std::cout << "TRY_LOCK used." << std::endl;
        std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
        console_mutex.unlock();
    }
    else
    {
        std::cout << "Thread ID " << std::this_thread::get_id() << " failed to acquire the lock." << std::endl;
    }
}


int main()
{
    //Store threads in a vector
    std::vector<std::thread> threads_normallock;
    std::vector<std::thread> threads_trylock;



//NORMAL LOCKS
    //Measure processing time
    auto start = std::chrono::system_clock::now();

    //Emplace_back threads into appropriate vectors. I do so so that I can join them easier later on. It is the same as creating threads everytime, giving a name, and then joining manually...
    for(int i=0; i<5; i++)
    {
        threads_normallock.emplace_back(FreeFunction_Lock);
    }

    //Join all threads
    for (auto& thread : threads_normallock) {
        thread.join();
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Finished computation within: " << elapsed_seconds.count() << "s.\n";


//TRY-LOCKS
    //Measure processing time
    start = std::chrono::system_clock::now();

    for(int i=0; i<5; i++)
    {
        threads_trylock.emplace_back(FreeFunction_TryLock);
    }

    for (auto& thread : threads_trylock) {
        thread.join();
    }

    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Finished computation within: " << elapsed_seconds.count() << "s.\n";

//COMMENT: as one can see, using try_lock is extremely messy as threads are contending for the lock asynchronously. I would be adding 
//         additional synchronization primitives in order to ensure proper access the console, but it is not specified in the exercise.
//         Therefore, I assume this is the goal of the exercise in showing that try_lock is a method available, but imperfect.


//PART C: runtime error because of deadlock
    return 0;
}



