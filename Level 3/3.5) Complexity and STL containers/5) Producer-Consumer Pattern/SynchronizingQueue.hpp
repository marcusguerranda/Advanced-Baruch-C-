//SynchronizingQueue.hpp

//USE MY SUBMISSION FOR EXERCISE 3.5.4 HERE!

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
	std::atomic<bool> m_flag;							//Flag stating when to stop producing/consuming or not

public:
	//Default constructor
    SynchronizingQueue(): m_flag(true){}

    //Enqueuing function
	void Enqueue(const T& new_element);
	
    //Dequeuing function
	T Dequeue();

	//Getter function for m_flag
	bool GetFlag() const;

	//Setter function for m_flag
	void ToggleFlag();

};

#ifndef SYNCHRONISINGQUEUE_CPP
#include "SynchronizingQueue.cpp"
#endif //SYNCHRONISINGQUEUE_CPP

#endif //SYNCHRONISINGQUEUE_HPP

