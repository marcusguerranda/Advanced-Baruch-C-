//Functions.hpp

//Purpose: Interface Iprint(const std::string& s, int count) that prints a number of times on the console

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <functional>


/*PART A: Create as many callable objects as you can (free functions, stored lambda function, 
function object, binded member function, static member function) that all call the interface 
Iprint
*/

void Iprint(const std::string& s, int count)
{
    for(int i=0; i< count; i++){
        std::cout << s << std::endl;
    }

    //PART E: Print the thread ID of each thread in each implementation of Iprint
    std::cout << "Thread ID is: " << std::this_thread::get_id() << std::endl;
}


//Function testing code's processing time
void TestChrono()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    // Do something heavy here/insert code 
    // Introduce delay to simulate a heavy algorithm
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Finished computation at " << "elapsed time: " << elapsed_seconds.count() << "s\n";
}


//Free function
void FreeFunction(const std::string& s, int count)
{
    Iprint(s, count);
}


//Lambda function
auto LambdaFunction = []()->void {Iprint("Stored lambda function used.", 4); };

//Function object
struct FunctionObject
{ 
    void operator () (){
        Iprint("Function object used.", 4);
    }

    //Static member function
    static void StaticFunction(){
        Iprint("Static member function used.", 4);
    };
};

//Binded member function
auto BindedFunction = std::bind(Iprint, "Binded function used", 4);

