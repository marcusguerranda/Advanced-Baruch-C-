//3.1)Threads: 4) Synchronizing Queues

//Purpose: We implement a synchronizing (thread-safe) FIFO queue in C++11. In this exercise, we create our own
//         generic synchronizing queue having an embedded STL queue.

//Author: Andrew Guerrand

//Modification dates: 6/5/2023

/*
    A) Implement this template class, in particular its template parameters and functions for queuing and 
       dequeing.
    B) Add locking mechanisms to functions for synchronisation effects.
    C) Add notification mechanisms to allow thread notification (use condition variables for notification).
    D) Test the queue by creating producer and consumer threads.

*/


/*  NOTES FROM SLIDES

APalley: You should STL when possible

1) Create a producer/consumer class with the synchronized queue
2) yes adapt the example in the lecture
3) Your code should for any number of producer and consumer

Yes, just like the sample code --
b) use lock and mutex so that only one thread can enqueue or dequeue at a time(i.e. no race conditions)
c) use condition variable to handle the case of dequeuing an empty queue (allow other threads to enqueue so it can eventually dequeue an item)


1) Can I use vector<std::thread> instead of thread_group? -> YES
2) I read in some posts that in order to stop the program, we can use atomic boolean, however to 
my surprise my program works fine just by using a simple global bool variable which is initially true, 
and setting this to false after some time in main, program stops. I have not expected it would work, 
because threads operates independently and are not aware of changements made on the global variables during run-time. 
Please correct me if am wrong. Is my approach enough at this stage?
    Answer:2.   2 threads will access the same global variable, the issue is the race condition, for example, if you have 
                a global int i=0, and then 2 threads doing i++ for 1 million times each, the final result will most likely not be 2 million. 
                But if you have a atomic<int>, it will always be 2 million.
3)

*/


#include "Producer.hpp"
#include "Consumer.hpp"
//#include <boost\thread.hpp>


int main()
{
    const int np = 3, nc = 3;
    Queue<std::string> queue;

    std::vector<std::thread> producers;
    for (int i = 0; i < np; i++)
    {
        Producer p(i, &queue);
        producers.emplace_back(std::move(p));
    }

    std::vector<std::thread> consumers;
    for (int i = 0; i < nc; i++)
    {
        Consumer c(i, &queue);
        consumers.emplace_back(std::move(c));
    }

    for (auto& producer : producers)
    {
        producer.join();
    }

    for (auto& consumer : consumers)
    {
        consumer.join();
    }

    return 0;
}


    /*  USING BOOST FUNCTIONALITIES
    const int np = 3, nc = 3;
    Queue<std::string> queue;
    
    boost::thread_group producers;
    for (int i = 0; i < np; i++)
    {
        Producer p(i, &queue);
        producers.create_thread(p);
    }
    
    boost::thread_group consumers;
    for (int i = 0; i < nc; i++)
    {
        Consumer c(i, &queue);
        consumers.create_thread(c);
    }

    producers.interrupt_all(); producers.join_all();
    consumers.interrupt_all(); consumers.join_all();
*/


















/*  IMPLEMENTATION 1: source: 'Producer and Consumer Problem' (Cppnuts, Youtube)

// THE PROBLEM STATEMENT:
// 1. Producer will produce and consumer will consume with synchronization of a common buffer.
// 2. Until producer thread produces any data consumer thread can't consume.
// 3. Threads will use condition_variable to notify each other.
// 4. We need mutex if we use condition_variable because CV waits on mutex.
// 5. This is one of the example of producer consumer there are many.

// PRODUCER thread steps:
// 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
// 2. check if buffer is full and if it is full then unlock mutex and sleep, if not then go ahead and produce.
// 3. insert item in buffer.
// 4. unlock mutex. 
// 5. notify consumer.

// CONSUMER thread steps:
// 1. lock mutex, if success then go ahead and consume otherwise wait for mutex to get free.
// 2. check if buffer is empty and if it is, then unlock the mutex and sleep, if not thean go ahead and consume.
// 3. consume item from buffer.
// 4. unlock mutex.
// 5. notify producer.

// IMP:
// If you are talking about producer consumer then they have to notify each other.

#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
using namespace std;

std::mutex mu;
std::condition_variable cond;
deque<int> buffer;
const unsigned int maxBufferSize = 50;

void producer(int val) {
     while (val) {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){return buffer.size() < maxBufferSize;});
        buffer.push_back(val);
        cout << "Produced: " << val << endl;
        val--;
        locker.unlock();
        cond.notify_one();
    }
}

void consumer(){
    while (true) {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){return buffer.size() > 0;});
        int val = buffer.back();
        buffer.pop_back();
        cout << "Consumed: " << val << endl;
        locker.unlock();
        cond.notify_one();
    }
}

int main() {

    std::thread t1(producer, 100);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
}



IMPLEMENTATION 2: (MVORBRODT on github -> source: Youtube tutorial)

#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <queue>
#include <memory>
#include <vector>
#include <utility>
#include <functional>
#include <condition_variable>
#include <stdexcept>
#include <ctime>
#include <cstdlib>

template<typename T>
class unbounded_queue
{
public:
	unbounded_queue() = default;
	~unbounded_queue()
	{
		done();
	};

	void push(const T& item)
	{
		{
			std::unique_lock guard(m_queue_lock);
			m_queue.push(item);
		}
		m_condition.notify_one();
	}

	void push(T&& item)
	{
		{
			std::unique_lock guard(m_queue_lock);
			m_queue.push(std::move(item));
		}
		m_condition.notify_one();
	}

	bool pop(T& item)
	{
		std::unique_lock guard(m_queue_lock);
		m_condition.wait(guard, [&]() { return !m_queue.empty() || m_done; });
		if(m_done == true)
			return false;
		item = std::move(m_queue.front());
		m_queue.pop();
		return true;
	}

	std::size_t size() const
	{
		std::unique_lock guard(m_queue_lock);
		return m_queue.size();
	}

	bool empty() const
	{
		std::unique_lock guard(m_queue_lock);
		return m_queue.empty();
	}

	void done()
	{
		{
			std::unique_lock guard(m_queue_lock);
			m_done = true;
		}
		m_condition.notify_all();
	}

private:
	using queue_t = std::queue<T>;
	queue_t m_queue;
	mutable std::mutex m_queue_lock;
	std::condition_variable m_condition;
	bool m_done = false;
};



template<typename T>
class bounded_queue
{
public:
	bounded_queue(std::size_t max_size) : m_max_size{ max_size }
	{
		if(!m_max_size)
			throw std::invalid_argument("bad queue max-size! must be non-zero!");
	}

	~bounded_queue()
	{
		done();
	};

	bool push(const T& item)
	{
		{
			std::unique_lock guard(m_queue_lock);
			m_condition_push.wait(guard, [&]() { return m_queue.size() < m_max_size || m_done; });
			if(m_done)
				return false;
			m_queue.push(item);
		}
		m_condition_pop.notify_one();
		return true;
	}

	bool push(T&& item)
	{
		{
			std::unique_lock guard(m_queue_lock);
			m_condition_push.wait(guard, [&]() { return m_queue.size() < m_max_size || m_done; });
			if(m_done)
				return false;
			m_queue.push(std::move(item));
		}
		m_condition_pop.notify_one();
		return true;
	}

	bool pop(T& item)
	{
		{
			std::unique_lock guard(m_queue_lock);
			m_condition_pop.wait(guard, [&]() { return !m_queue.empty() || m_done; });
			if(m_done == true)
				return false;
			item = std::move(m_queue.front());
			m_queue.pop();
		}
		m_condition_push.notify_one();
		return true;
	}

	std::size_t size() const
	{
		std::unique_lock guard(m_queue_lock);
		return m_queue.size();
	}

	bool empty() const
	{
		std::unique_lock guard(m_queue_lock);
		return m_queue.empty();
	}

	void done()
	{
		{
			std::unique_lock guard(m_queue_lock);
			m_done = true;
		}
		m_condition_push.notify_all();
		m_condition_pop.notify_all();
	}

private:
	using queue_t = std::queue<T>;
	queue_t m_queue;
	mutable std::mutex m_queue_lock;
	std::condition_variable m_condition_push;
	std::condition_variable m_condition_pop;
	std::size_t m_max_size;
	bool m_done = false;
};



class thread_pool
{
public:
	explicit thread_pool(std::size_t thread_count = std::thread::hardware_concurrency())
	{
		if(!thread_count)
			throw std::invalid_argument("bad thread count! must be non-zero!");

		m_threads.reserve(thread_count);

		for(auto i = 0; i < thread_count; ++i)
		{
			m_threads.push_back(std::thread([this]()
			{
				while(true)
				{
					work_item_t work{};
					m_queue.pop(work);
					if(!work)
						break;
					work();
				}
			}));
		}
	}

	~thread_pool()
	{
		for(auto& t : m_threads)
			m_queue.push(work_item_t{});
		for(auto& t : m_threads)
			t.join();
	}

	using work_item_t = std::function<void(void)>;

	void do_work(work_item_t wi)
	{
		m_queue.push(std::move(wi));
	}

private:
	using threads_t = std::vector<std::thread>;
	threads_t m_threads;

	using queue_t = unbounded_queue<work_item_t>;
	queue_t m_queue;
};



int main()
{
	using namespace std;

	bounded_queue<int> q{ 5 };

	thread t{ [&]
	{
		while(true)
		{
			int i{};
			bool r = q.pop(i);
			if(!r)
				return;
			cout << "value: " << i << "\tsize: " << q.size() << endl;
		}
	}};

	for(int i = 1; i <= 50; ++i)
	{
		q.push(i);
	}

	this_thread::sleep_for(100ms);
	q.done();
	t.join();
}










*/