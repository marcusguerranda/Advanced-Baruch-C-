//3.2/3.3) C++ Concurrency: 3. Active Objects

/*Purpose:
    An active object is one that executes in its own thread of control. One advantage of creating/using active 
    objects is that it results in a one-to-one correspondence between an object and a thread. C++ does not 
    directly support active objects. It only supports passive objects that are acted on by other objects. 
    In this chapter we create an adapter class called ActiveObject that is composed of a thread. The 
    requirements are:
        • ActiveObject has a reference to an instance of an std::thread instance.
        • It has an explicit constructor accepting a thread with associated thread function. The active object 
          starts computing as soon as it is instantiated (in principle).
        • In the destructor of ActiveObject we check if the thread is joinable and if it is we then join it.
        • Check that the thread has an associated thread function; use try and catch blocks in client code.
*/

//Author: Andrew Guerrand

//Modification dates: 6/8/2023

//PART A) Create a thread and a function that will be its thread function.
//PART B) Create an active object based on a thread with no associated thread function.
//PART C) Implement thread functions using function objects and lambda functions.
//PART D) Test the code.

//Adapter class ActiveObject importation
#include "ActiveObject.hpp"
#include <exception>

//Thread function
void ThreadFunction() 
{
    std::cout << "Thread function being used." << std::endl;
};

//Function object
struct FunctionObject
{
    void operator () ()
    {
        std::cout << "Function object used." << std::endl;
    };
};

auto stored_lambda = [](){std::cout << "Stored lambda function used." << std::endl;};


int main() 
{
    try{
//PART A: Create a thread and a function that will be its thread function.

    std::cout << "\nPART A: Create a thread and a function that will be its thread function." << std::endl;
    //Create a thread and associate it with the thread function
    std::thread thread1(ThreadFunction);
    //Wait for the thread to finish its execution
    thread1.join();

//PART B:

    std::cout << "\nPART B: Create an active object based on a thread with no associated thread function." << std::endl;
    std::thread thread2;
    ActiveObject a_object1(thread2);
    }
    catch (const std::invalid_argument& error) 
    {
        std::cout << "Thread has no associated thread function: " << error.what() << std::endl;
    }
    catch (const std::system_error& error) 
    {
        std::cout << "System error occurred: " << error.what() << std::endl;
    }
    catch (const std::exception& ex) 
    {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
    catch (...) 
    {
        std::cout << "Unknown exception occurred." << std::endl;
    }

//PART C) Implement thread functions using function objects and lambda functions.

    std::cout << "\nPART C) Implement thread functions using function objects and lambda functions." << std::endl;

    //Function object
    FunctionObject myfunction1;
    std::thread thread3(myfunction1);
    ActiveObject a_object2(thread3);

    //Stored lambda
    std::thread thread4(stored_lambda);
    ActiveObject a_object3(thread4);

    std::cout << std::endl;
    return 0;
}