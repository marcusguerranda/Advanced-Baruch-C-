//SynchronizingQueue.cpp

#ifndef SYNCHRONISINGQUEUE_CPP
#define SYNCHRONISINGQUEUE_CPP
#include "SynchronizingQueue.hpp"


//Enqueuing function
template<typename T, typename comparator>
void SynchronizingQueue<T,comparator>::Enqueue(const T& new_element) 
{
	std::unique_lock<std::mutex> m_lock(m_mutex);   //Unique lock
	m_sync_queue.push(new_element);                 //Add new element by calling push()
	m_cond.notify_one();                            //Notify next waiting thread (and not caling .notify_all())
}

//Dequeuing function
template<typename T, typename comparator>
T SynchronizingQueue<T,comparator>::Dequeue() 
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


//Getter function for m_flag
template<typename T, typename comparator>
bool SynchronizingQueue<T,comparator>::GetFlag() const
{
    return m_flag;
}

//Setter function for m_flag
template<typename T, typename comparator>
void SynchronizingQueue<T,comparator>::ToggleFlag()
{
    std::unique_lock<std::mutex> m_lock(m_mutex);
    m_flag = !m_flag;           //Toggle the flag between true and false
    m_lock.unlock();            //Unlock the mutex to notify all waiting threads
    m_cond.notify_all();        //Notify all waiting threads to check the flag and exit if necessary
}
	
#endif //SYNCHRONISINGQUEUE_CPP