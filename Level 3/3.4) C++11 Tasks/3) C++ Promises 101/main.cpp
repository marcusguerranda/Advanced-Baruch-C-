//3.4) C++11 Tasks. 3) Promises

//Purpose: A promise is the counterpart of a future object. Both are able to temporarily hold a shared state. Thus, a promise is a general mechanism to
//         allow values and exceptions to be passed out of threads. A promise is the "push" end of the promise-future communication channel.

//Author: Andrew Guerrand

//Modification dates:6/19/2023


//See video from CPPNuts: https://www.youtube.com/watch?v=XDZkyQVsbDY&ab_channel=CppNuts


#include <iostream>
#include <future>
#include <thread>

void FunctionPartC(std::future<double>& future)
{
    double value = future.get();
    std::cout << "FunctionPartC and thread called/used." << std::endl;

}


int main()
{
//PART A) Create a default promise, a promise with an empty shared state and a promise based on the move constructor.
//      See cppreference.com for relevant information
    std::cout << std::endl;


    //Default promise
    std::promise<void> promise1;

    //A promise with an empty shared state
    //Allocators are used in the C++ STL to handle the allocation and dealloaction of elements stored in containers
    std::promise<void> promise2(std::allocator_arg_t, std::allocator<void>());   

    //Promise based on the move constructor
    std::promise<void> promise3{std::move(promise1)};

//Part B: Create a promise with 'double' as stored value. Then create a future that is associated with the promise
    std::promise<double> promise4;
    std::future<double> future1 = promise4.get_future();

//PART C) Start a thread with the new future from part b). Create a thread function that uses the value of the 
//shared data. 
    std::thread thread1(FunctionPartC, std::ref(future1));
    promise4.set_value(11.11);

    thread1.join();

//PART D) Use the promise to set the value of the shared data.

    
    std::cout << std::endl;
    return 0;
}




/* The class template std::promise provides a facility to store a value or an exception that is later acquired asynchronously 
via a std::future object created by the std::promise object. Note that the std::promise object is meant to be used only once.

Each promise is associated with a shared state, which contains some state information and a result which may be not yet evaluated, 
evaluated to a value (possibly void) or evaluated to an exception. A promise may do three things with the shared state:

    - make ready: the promise stores the result or the exception in the shared state. Marks the state ready and unblocks any thread waiting 
    on a future associated with the shared state.

    - release: the promise gives up its reference to the shared state. If this was the last such reference, the shared state is destroyed. 
    Unless this was a shared state created by std::async which is not yet ready, this operation does not block.

    - abandon: the promise stores the exception of type std::future_error with error code std::future_errc::broken_promise, makes the shared 
    state ready, and then releases it.




SEE EXCELLENT NOTE BELOW:

 NOTES:
 1. std::promise
      a. Used to set values or exceptions.
 2. std::future
      a. Used to get values from promise.
      b. Ask promise if the value is available.
      c. Wait for the promise.

// PROGRAM:
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>
using namespace std;
using namespace std::chrono;
typedef long int ull;

void findOdd(std::promise<ull>&& OddSumPromise, ull start, ull end) {
    ull OddSum = 0;
	for (ull i = start; i <= end; ++i){
		if (i & 1){
			OddSum += i;
		}
	}
    OddSumPromise.set_value(OddSum);
}

int main() {
	
	ull start = 0, end = 1900000000;

	std::promise<ull> OddSum;
    std::future<ull> OddFuture = OddSum.get_future();
    
    cout << "Thread Created!!" << endl;
    std::thread t1(findOdd, std::move(OddSum), start, end);
    
    cout << "Waiting For Result!!" << endl;

	cout << "OddSum : " << OddFuture.get() << endl;
    
    cout << "Completed!!" << endl;
	t1.join();
	return 0;
}

*/