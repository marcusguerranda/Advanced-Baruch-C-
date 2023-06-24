//ActiveObject.hpp

//Purpose: Adapter class called ActiveObject that is composed of a thread. 

/*
    • 1) ActiveObject has a reference to an instance of an std::thread instance.
    • 2) It has an explicit constructor accepting a thread with associated thread function. The active object 
         starts computing as soon as it is instantiated (in principle).
    • 3) In the destructor of ActiveObject we check if the thread is joinable and if it is we then join it.
    • 4) Check that the thread has an associated thread function; use try and catch blocks in client code.
*/

//Note: APalley: " The bare minimum needed in this exercise (NO copy ctor, copy assignment operator, move ctor, move assignment operator..)
//                 APalley - Correct."

#ifndef ActiveObject_hpp
#define ActiveObject_hpp

#include <iostream>
#include <thread>
#include <chrono>

//Adapter class ActiveObject
class ActiveObject
{
private:
    //Condition 1: ActiveObject has a reference to an instance of an std::thread instance.
    std::thread& active_thread;

public:

    //Explicit constructor, preventing implicit conversion (important) when initializing ActiveObject instance
    explicit ActiveObject(std::thread& source_t);

    //Condition 3: In the destructor of ActiveObject we check if the thread is joinable and if it is we then join it.
    ~ActiveObject();

};


#endif //ActiveObject_hpp

