//Producer.hpp

//Purpose :Producer class producing data and sending to buffer (here a std::queue)

//Author: Andrew Guerrand

//Modification dates: 6/7/2023

#ifndef Producer_hpp
#define Producer_hpp

#include "Queue.hpp"
#include <chrono>

//Producer class producing the data that will be sent to the queue
class Producer
{
private:

    int m_id;                       //ID of producer
    Queue<std::string>* m_queue;    //Pointer to queue to produce data to

public:
    //Overloaded constructor
    Producer(int id, Queue<std::string>* queue); 

    //Operator () overloading
    void operator () ();
};

#endif //Producer_hpp


