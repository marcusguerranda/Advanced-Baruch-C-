//SynchronizingQueue.hpp


#ifndef SYNCHRONISINGQUEUE_HPP
#define SYNCHRONISINGQUEUE_HPP

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

//Where T is the data type of elements queue and dequeued, and 'comparator' is an STL comparator such as std::greater, 
//std::less_equal/std::less, std::greater_equal, etc.
template<typename T, typename comparator>   
class SynchronizingQueue 
{
private:
    std::priority_queue<T, std::vector<T>, comparator> m_sync_queue;   //PART A: Member priority queue
	std::mutex m_mutex;                                 //PART B: Mutex...
	std::condition_variable m_cond;                     //PART C: Condition to notify other waiting threads


public:
    //Enqueuing function
	void Enqueue(const T& new_element) 
    {
		std::unique_lock<std::mutex> m_lock(m_mutex);   //Unique lock
		m_sync_queue.push(new_element);                 //Add new element by calling push()
		m_cond.notify_one();                            //Notify next waiting thread (and not caling .notify_all())
	}

    //Dequeuing function
	T Dequeue() 
    {
		std::unique_lock<std::mutex> m_lock(m_mutex);   //Unique lock
		
        //Verify whether the queue is empty. If so, then wait 
		while (m_sync_queue.size() == 0)
        {
            m_cond.wait(m_lock);
        }

		T result = m_sync_queue.top();                  //First, store temporarily element at top of FIFO priority queue
		m_sync_queue.pop();                             //Then remove/pop it

		return result;                                  //Return result, of type T
	}
};

#endif //SYNCHRONISINGQUEUE_HPP