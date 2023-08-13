//3.4) C++11 Tasks. 1) Tasks 101: Running functions asynchronously

//Purpose: Understand C++11 futures, std::async, and thread/task launching policies/
//		   Involves running synchronous and asynchronous functions based on various launch policies.
//		   The objective is not in creating complex functions but in showing how the tasks execute and exchange information.

//Author: Andrew Guerrand

//Modification dates: 6/17/2023


#include <iostream>
#include <thread>
#include <future>

void func1()
{
	std::cout << "FUNC1 used.\n" << std::endl;
}

double func2(double a, double b)
{
	std::cout << "FUNC2 used.\n" << std::endl;
	return a + b;
}



int main()
{

//PART B: Use std::async (default settings) to launch func1 and func2. Get the results of the computations and print them when applicable. 
//	     Check the validity of the associated future before and after getting the result

	std::cout << "\nPARTS A, B, AND C: \n" << std::endl;

//VERY IMPORTANT NOTE FOR SELF: std::async requires a callable object as its first argument
	std::future<void> FutureVoid(std::async(func1));
	std::future<double> FutureDouble(std::async(func2,3,4));

//I am creating my lazy evaluation here for PART E. The task will be executed when calling .get() down below in Part E
	std::future<void> LazyVoid(std::async(std::launch::deferred, func1));


//Checking the validity -> Checking the validity of the associated future before getting the result means verifying if the future object is valid and can be used to retrieve the result.

	std::cout << std::boolalpha;
	std::cout << "Future function1 is valid " << FutureVoid.valid() << std::endl;
	std::cout << "Future function2 is valid " << FutureDouble.valid() << std::endl;

	FutureVoid.wait();
	std::cout << "Output from function1 -> \n"; FutureVoid.get();
	//Getting a std::future more than once
	//Calling more than once leads to throwing an instance of 'std::future_error': "No associated state"
	//std::cout << "Output from function1 -> \n"; FutureVoid.get();


	FutureDouble.wait();
	std::cout << "Output from function2 -> \n" << FutureDouble.get() << std::endl;

//-----------------------------------------------------------------------------------
//PART D: using std::launch::async
//NOTE TO SELF: std::launch:::async is used as an argument to std::async function to specify the launch policy for the asynchronous task.
//				It ensures asynchronous execution of the said task.

	std::cout << "\nPART D : \n";
	std::future<void> FutureVoid2(std::async(std::launch::async, func1));
	std::future<double> FutureDouble2(std::async(std::launch::async, func2, 3, 4));

//Checking the validity -> Checking the validity of the associated future before getting the result means verifying if the future object is valid and can be used to retrieve the result.

	std::cout << std::boolalpha;
	std::cout << "Future function1 is valid " << FutureVoid2.valid() << std::endl;
	std::cout << "Future function2 is valid " << FutureDouble2.valid() << std::endl;

	FutureVoid2.wait();
	std::cout << "Output from function1 -> \n"; FutureVoid2.get();
	FutureDouble2.wait();
	std::cout << "Output from function2 -> \n" << FutureDouble2.get() << std::endl;

//Notice: the real difference is that now, the async() functions is called and ensures asynchronous execution:
/*	OUTPUT:
			PARTS A, B, AND C: 

			Future function1 is valid true
			Future function2 is valid true
			FUNC2 used.

			FUNC1 used.

			Output from function1 -> 
			Output from function2 -> 
			7

			PART D : 
			Future function1 is valid true
			FUNC1 used.
			FUNC2 used.


			Future function2 is valid true
			Output from function1 -> 
			Output from function2 -> 
			7
*/

//PART E: using std::launch::deferred to asynchronously call a function at some time later in the client code (deferred/lazy evaluation)
	std::cout << "PART E: using lazy/deferred evaluation" << std::endl;
	LazyVoid.get();	//Calling std::launch::deferred as launch policy does as intentioned

	return 0;
}









/*	CODE EXAMPLE

double ParallelTaskGraphI(double a)
{ 	//Parallel with futures
	std::cout << "Parallel I \n";
	//double b = F1(a);
	std::future<double> b(std::async(F1, a));
	double c = F2(a);
	double d = F3(c);
	double f = b.get() + d;
	return f;
}

*/



/*	CPLUSPLUS.COM CODE for std::launch::async
// launch::async vs launch::deferred
#include <iostream>     // std::cout
#include <future>       // std::async, std::future, std::launch
#include <chrono>       // std::chrono::milliseconds
#include <thread>       // std::this_thread::sleep_for

void print_ten (char c, int ms) {
  for (int i=0; i<10; ++i) {
    std::this_thread::sleep_for (std::chrono::milliseconds(ms));
    std::cout << c;
  }
}

int main ()
{
  std::cout << "with launch::async:\n";
  std::future<void> foo = std::async (std::launch::async,print_ten,'*',100);
  std::future<void> bar = std::async (std::launch::async,print_ten,'@',200);
  // async "get" (wait for foo and bar to be ready):
  foo.get();
  bar.get();
  std::cout << "\n\n";

  std::cout << "with launch::deferred:\n";
  foo = std::async (std::launch::deferred,print_ten,'*',100);
  bar = std::async (std::launch::deferred,print_ten,'@',200);
  // deferred "get" (perform the actual calls):
  foo.get();
  bar.get();
  std::cout << '\n';

  return 0;
}



*/


/*			std::launch::deferred

Is another launch policy that can be used as an argument to the 'std::async' function. It specifies that the task shoud be executed lazily and deferred
until the result is needed.

-> Lazy evaluation: 
	When std::launch::deferred is specified, the task associated with std::async is not executed immediately. 
	Instead, it is deferred until the result is explicitly requested using the get() member function on the future. 
	This allows for lazy evaluation, meaning the task is executed only when the result is actually needed.

-> Synchronous Execution: 
	Unlike std::launch::async, which guarantees asynchronous execution in a separate thread, 
	std::launch::deferred executes the task synchronously within the same thread when the result is requested. 
	This can be useful in situations where you want to defer the execution and keep the computation within the calling thread.



*/