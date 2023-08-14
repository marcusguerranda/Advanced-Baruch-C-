//3.4) C++11 Tasks

//Purpose: Process the computation of a concurrent computation more than once. Especially when multiple threads are running and to this end, we 
//         use std::shared_future so that we can make multiple calls to get().

//Author: Andrew Guerrand

//Modification dates: 6/17/2023


#include <iostream>
#include <future>
#include <chrono>

int CalculateSquare(int x)
{
    return x*x;
}

void Printer()
{
    std::cout << "Printer() function called." << std::endl;
}

void Printer2(std::future<int>&& future) {
  int result = future.get();
  std::cout << "Printer2() called. Square: " << result << std::endl;
}


//Part D: Infinite loop
void InfiniteLoop()
{
    whie(true){}    //Simulating infinite loop
}

int main()
{
//PART A and B:
//NOTE TO SELF: all this functionalities are templated, and thus you need to define the return type expected when .get() 'ing' the value from the future/shared future
    std::cout << "\n PARTS A AND B " << std::endl;
    std::future<void> future1(std::async(Printer));

    //Default instance
    std::shared_future<void> shared1;

    //As a shared future that shares the same state as another shared state.
    // + share state from normal future to shared future
    std::shared_future<void> shared2 = future1.share();   //Sharing from future instance
    std::shared_future<void> shared3{shared2};            //Shared future that shares the same state as shared future 'shared2'

    //Transfer shared state from a ‘normal’ future to a shared future. -> Use std::promise! -> provides a facility to store a value or exception that is later acquired asynchronousl via a std::future object
    std::cout << std::boolalpha;
    std::cout << "shared3 is valid: " << shared3.valid() << std::endl;
    shared3.get();          //Ensures that the program waits for the completion of the task and retrieves the result, if any.
    
//PART C: Test what happens when you call get() twice on a shared future.

    shared3.get();          //Nothing happens.       

//PART D: Create a shared future that waits for an infinite loop to finish (which it never does). 
//        To this end, use 'wait_for' and 'wait_until' to trigger a time out.
    
    //->Note,std::async returns an rvalue std::future. An rvalue cannot be directly shared with another std::future, so state must be shared to shared_future
    std::shared_future<void> sharedFuture = std::async(std::launch::async, InfiniteLoop).share();
    std::future_status status = sharedFuture.wait_for(std::chrono::seconds(2));

    if (status == std::future_status::ready) {
        std::cout << "Infinite loop completed within the timeout." << std::endl;
    } else if (status == std::future_status::timeout) {
        std::cout << "Timeout occurred. Infinite loop did not complete." << std::endl;
    }


    return 0;
}


/* NOTE to self:

Here are a few cases where you may not need to use std::promise:

1.  When using std::async:
    If you're using the std::async function to perform asynchronous computations, 
    you don't necessarily need to create a std::promise explicitly. std::async 
    returns a std::future that represents the result of the asynchronous computation. 
    You can directly retrieve the result from the std::future without using a promise EXPLICITLY.

                #include <iostream>
                #include <future>

                int CalculateSum(int a, int b) {
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    return a + b;
                }

                int main() {
                    std::future<int> future = std::async(std::launch::async, CalculateSum, 3, 4);
                    int sum = future.get();
                    std::cout << "Sum: " << sum << std::endl;
                    return 0;
                }

    In this example, std::async is used to perform the CalculateSum computation asynchronously. 
    The function returns a std::future that holds the result of the computation. You can directly call get() on 
    the std::future to retrieve the result without explicitly using a std::promise


2.  When using other synchronization mechanisms

    When using other synchronization mechanisms:

    std::promise and std::future provide a specific way of communicating data between threads. However, there are other
    synchronization mechanisms like mutexes, condition variables, and atomic variables that may be more appropriate for
    certain scenarios. In such cases, you may not need to use std::promise at all.

                #include <iostream>
                #include <thread>
                #include <mutex>

                int sharedData = 0;
                std::mutex mtx;

                void IncrementData() {
                    std::lock_guard<std::mutex> lock(mtx);
                    sharedData++;
                }

                int main() {
                    std::thread thread1(IncrementData);
                    std::thread thread2(IncrementData);

                    thread1.join();
                    thread2.join();

                    std::cout << "Final value: " << sharedData << std::endl;

                    return 0;
                }

    In this example, a mutex (std::mutex) is used to synchronize access to the sharedData variable between two threads.
    There is no need for a std::promise because the threads are not waiting for a specific result to be fulfilled. 
    Instead, they synchronize their access using the mutex.

*/

/*Check the member function from std::future that are also applicable to std::future

Important: This shared state can be associated to a future object by calling member get_future. After the call, both objects share the same shared state:
- The promise object is the asynchronous provider and is expected to set a value for the shared state at some point.
- The future object is an asynchronous return object that can retrieve the value of the shared state, waiting for it to be ready, if necessary.

std::future:
    -(constructor)
    -(destructor)
    -operator =
    -.share() -> transfers the shared_state from *this to a std::shared_future AND returns it
    -.get() -> returns the result
    -.valid() -> checks if the future has a shared state
    -.wait() -> waits for the result to become available
    -.wait_for() -> waits for the result, returns if it is not available for the specified timeout duration
    -.wait_until() -> waits for the result, returns if it is not available until specified time point has been reached

std::shared_future

    --> all functionalities are the same...

*/



