
#ifndef CONSUMER_CPP
#define CONSUMER_CPP

#include "Consumer.hpp"
#include <chrono>

//Overloaded constructor
template <typename T, typename comparator>
Consumer<T, comparator>::Consumer(SynchronizingQueue<T, comparator>* queue) : m_queue(queue), ID(m_counter++){}
//IMPORTANT NOTE: note that I am incrementing statically the m_counter, so that I can keep track of the number of consumers


//Operator () overloading
template <typename T, typename comparator>
void Consumer<T, comparator>::operator()(const double& x)
{
    //While the bool flag is still 'true'
    while (m_queue->GetFlag())
    {   
        T elem = m_queue->Dequeue();
        std::cout << "Consumer " << ID << " consumed!";
        elem.Execute(x);          //Execute algorithm stored in Command.hpp: "FunctionType algo" stored as a Function wrapper
        std::this_thread::yield();  //Yield thread to other threads waiting
    }
}

#endif //CONSUMER_CPP