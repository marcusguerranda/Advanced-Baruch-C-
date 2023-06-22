//Queue.hpp

//Purpose: Buffer storing data between producer and consumer

//Author: Andrew Guerrand

//Modification dates: 6/7/2023


#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>


template <typename T> 
class Queue
{
private:
    std::queue<T> m_queue;          //Use stl queue to store data
    std::mutex m_mutex;             //Mutex to synchronize on
    std::condition_variable m_cond; //Condition to wait for to allow thread notification

public:
    //Queue class that has thread synchronization
    void Enqueue(const T& data)
    {
        std::unique_lock<std::mutex> lock(m_mutex); //Acquire lock on queue
        m_queue.push(data);                         //Add data to queue
        m_cond.notify_one();                        //Notify others that data is ready
        //Lock release here
    }

    //Get the data from qthe queue. Wait for data if not available
    T Dequeue()
    {
        std::unique_lock<std::mutex> lock(m_mutex); //Acquire lock on queue
                
        //When there is no data, wait till someone fills it
        //Lock is automatically released in the wait and active again after the wait
        while (m_queue.size() == 0) 
            m_cond.wait(lock);

            //Retrieve the data from the queue
            T res = m_queue.front(); 
            m_queue.pop(); //Get data from the front of the queue, then remove it
            return res;
    }
};


#endif //Queue_hpp


