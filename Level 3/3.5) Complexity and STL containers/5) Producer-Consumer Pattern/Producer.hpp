//Producer.hpp

#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include <iostream>
#include "Command.hpp"
#include "SynchronizingQueue.hpp"

template <typename T, typename comparator>
class Producer
{
private:
    SynchronizingQueue<T, comparator>* m_queue; //Pojnter to member queue such that the producer can .... (drumroll) producer/enqueue from m_queue
    int ID;                                     //ID of producer
    static int m_counter;                       //Acts as counter to track number of producers
    std::function<T(void)> m_func;              //C

public:

    Producer(SynchronizingQueue<T, comparator>* queue, std::function<T(void)> func); //Overloaded constructor
    void operator() ();                                                             //Operator () overloading
};

template <typename T, typename comparator>
int Producer<T, comparator>::m_counter = 1; //Start static counter from 1

#ifndef PRODUCER_CPP
#include "Producer.cpp"
#endif //PRODUCER_CPP

#endif //PRODUCER_HPP
