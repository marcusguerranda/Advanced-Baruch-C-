//Consumer.hpp

#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include <iostream>
#include "Command.hpp"
#include "SynchronizingQueue.hpp"

template <typename T, typename comparator>
class Consumer
{
private:
    SynchronizingQueue<T, comparator>* m_queue; //Pojnter to member queue such that the consumer can .... (drumroll) consume/dequeue from m_queue
    int ID;                                     //ID of consumer
    static int m_counter;                       //Acts as counter to track number of consumers

public:

    Consumer(SynchronizingQueue<T, comparator>* queue); //Overloaded constructor

    void operator()(const double& x);                   //Operator () overloading
};

template <typename T, typename comparator>
int Consumer<T, comparator>::m_counter = 1; //Start static counter from 1

#ifndef CONSUMER_CPP
#include "Consumer.cpp"
#endif //CONSUMER_CPP

#endif //CONSUMER_HPP


