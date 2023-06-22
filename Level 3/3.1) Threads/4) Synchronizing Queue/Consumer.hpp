//Consumer.hpp

#ifndef Consumer_hpp
#define Consumer_hpp

#include <chrono>
#include "Queue.hpp"

class Consumer
{
private:
    int m_id;                       //ID of consumer
    Queue<std::string>* m_queue;    //Pointer to queue to use/consume from

public:

    //Overloaded constructor
    Consumer(int id, Queue<std::string>* queue);

    //Operator () overloading
    void operator () ();
};


#endif //Consumer_hpp



