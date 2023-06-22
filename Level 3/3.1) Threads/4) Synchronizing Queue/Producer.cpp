//Producer.cpp

#include "Producer.hpp" //Importing header file

//Overloaded constructor
Producer::Producer(int id, Queue<std::string>* queue): m_id(id), m_queue(queue){}; 

//Operator () overloading
void Producer::operator () ()
{
    int data = 0;
    while (true)
    {   
        //Produce a string and store in the queue
        std::string str = "Producer #: "+ std::to_string(m_id); 
        m_queue-> Queue::Enqueue(str); //aAd adding it to queue
        data++;
        std:: cout << "Added -> " << str << " Number of Producers so far: " << data << std::endl;; 

        //Sleep for a set amount of time (could be milliseconds, seconds, etc.)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}