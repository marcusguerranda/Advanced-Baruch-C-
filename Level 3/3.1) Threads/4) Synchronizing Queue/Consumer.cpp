//Consumer.cpp

#include "Consumer.hpp"


//Overloaded constructor
Consumer::Consumer(int id, Queue<std::string>* queue): m_id(id), m_queue(queue){}


//Operator () overloading
void Consumer::operator () ()
{
    int data = 0;
    while (true)
    {   
        //Get the data from the queue
        std::string str = m_queue-> Queue::Dequeue();
        data++;
        //Print the consumed data
        std::cout << "Consumer # " << m_id << " consumed: " << str << std::endl;
        std::cout << "Number of Consumers so far: " << data << std::endl;
        
        //Allow other threads to run
        std::this_thread::yield();
    }
}
