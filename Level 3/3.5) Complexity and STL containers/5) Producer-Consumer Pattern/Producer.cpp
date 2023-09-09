//Producer.cpp

#ifndef PRODUCER_CPP
#define PRODUCER_CPP

#include "Producer.hpp"
#include <chrono>

//Overloaded constructor
template <typename T, typename comparator>
Producer<T, comparator>::Producer(SynchronizingQueue<T, comparator>* queue, std::function<T(void)> func) : m_queue(queue), ID(m_counter++){}
//IMPORTANT NOTE: note that I am incrementing statically the m_counter, so that I can keep track of the number of Producers


//Operator () overloading
template <typename T, typename comparator>
void Producer<T, comparator>::operator()()
{
    //While the bool flag is still 'true'
    while (m_queue->GetFlag())
    {   
        m_queue->Enqueue(m_func());
        std::cout << "Producer " << ID << " produced/enqueued!";
        std::this_thread::yield();  //Yield thread to other threads waiting
    }
}

#endif //PRODUCER_CPP