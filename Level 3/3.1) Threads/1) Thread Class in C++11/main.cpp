//3.1 MultiThreading

/*Purpose: Get experience with multi-threading in C++11. It can be seen as transition from Boost Thread library.

Specifically, we define a number of threads that print textual information on the system console. We wish to use the folowing features:

    • Creating and launching instances of std::thread.
    • Using various kinds of callable objects as a thread’s start function.
    • Waiting on threads to complete; has a thread finished executing code, but has not yet been joined?
    (use joinable()).
    • Creating threads that run in the background (detached/daemon threads).
    • Passing arguments to a thread function.

The threads you create all call a function that prints a string a number of times on the console. 
A typical interface is Iprint(const std::string& s, int count)
*/

//Author: Andrew Guerrand

//Modification dates: 6/4/2023


#include "Functions.hpp" //Includes all libraries of interest to us


//PART C AND D 
//Join threads together, but making sure they are joinable in the first place...
void ThreadJoiner(std::thread& source_thread)
{
    if(source_thread.joinable())
    {
        try{
            source_thread.join();
        }
        catch (const std::system_error& error) 
        {
        //Handle the specific system_error exception
        std::cout << "Error occurred while joining the thread: " << error.what() << std::endl;
        } 
        catch (...) 
        {
            //Handle any other exceptions
            std::cout << "An unknown exception occurred while joining the thread." << std::endl;
        }
    }
    else
    {
        std::cout << "Thread not joinable." << std::endl;
    }
};




int main()
{
//PART A: See Function.hpp

	//PART F
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();


    std::thread free_func{FreeFunction, "Using free function!", 4};
    //NOTE TO SELF: and not-> std::thread free_func{FreeFunction("Using free function!", 4)};
    std::thread lambda_func{LambdaFunction};
    std::thread object_func{FunctionObject()};
    std::thread static_func{FunctionObject::StaticFunction};
    std::thread binded_func{BindedFunction};

    //free_func detached -> won't be able to join it!
    //I'm basically telling the thread to run independently in the background without
    //being joined.
    free_func.detach(); 

//PART C AND D: I combine these sections because we must test whether the threads are 
//              joinable before even joining all of them together.
//              See free function above 'ThreadJoiner' for this, using try-catch 
//              blocks.

    ThreadJoiner(free_func);
    ThreadJoiner(lambda_func);
    ThreadJoiner(object_func);
    ThreadJoiner(static_func);
    ThreadJoiner(binded_func);

//At this point, I notice that the threads were executed in a mish mash and that I have
//messages printed out to the console everywhere. 
//
//This is normal. Since each thread executes independently and there is no synchronization
//mechanism in place to control the order of output, the messages from different threads
//can interleave.
//If I needed printing in a specific order, I would most likely use other synchronization
//methods.

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Finished computation within: " << elapsed_seconds.count() << "s.\n";
    
    return 0;
}



