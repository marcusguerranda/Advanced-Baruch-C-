//ActiveObject.cpp

#include "ActiveObject.hpp"

//Explicit constructor, preventing implicit conversion (important) when initializing ActiveObject instance
ActiveObject::ActiveObject(std::thread& source_t): active_thread{source_t}
{
    //Check if the thread has an associated thread function
    if (!active_thread.joinable())
    {
        throw std::invalid_argument("Invalid argument.");
    }
    std::cout << "Overloaded constructor in ActiveObject used." << std::endl;
}


//Condition 3: In the destructor of ActiveObject we check if the thread is joinable and if it is we then join it.
ActiveObject::~ActiveObject()
{
    //Condition 4 has to be met in client code, or in 'main', not here (ref. QN)
    if(active_thread.joinable()){
        active_thread.join();
    }
}

