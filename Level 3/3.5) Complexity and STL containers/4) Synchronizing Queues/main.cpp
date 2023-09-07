//3.5.5) Synchronizing queue

/*
    Purpose:

    We have already discussed synchronising (thread-safe) FIFO queues. In this exercise we create our own 
    generic synchronising queue having an embedded STL priority queue (both the latter’s container type and 
    comparator are generic). 
    Answer the following questions:
        a) Implement this template class, in particular its template parameters and functions for queueing and 
        dequeuing.
        b) Add locking mechanisms to functions for synchronisation effects.
        c) Add notification mechanisms to allow thread notification.
        d) Test the new class.
*/

//Author: Andrew Guerrand

//Modification dates: 7/19/2023

#include "SynchronizingQueue.hpp"
#include <thread>

int main() {
    //SynchronizingQueue of integers with std::greater comparator
    SynchronizingQueue<int, std::greater<int>> queue1;

    //Enqueue some elements
    queue1.Enqueue(30);
    queue1.Enqueue(10);
    queue1.Enqueue(50);
    queue1.Enqueue(20);

    //Create two threads to dequeue elements concurrently
    std::thread thread1([&](){
        for(int i = 0; i < 2; ++i) {
            int element = queue1.Dequeue();
            std::cout << "Thread 1 dequeued: " << element << std::endl;
        }
    });

    std::thread thread2([&](){
        for(int i = 0; i < 2; ++i) {
            int element = queue1.Dequeue();
            std::cout << "Thread 2 dequeued: " << element << std::endl;
        }
    });

    //Join both threads when they are done
    thread1.join();
    thread2.join();

    return 0;
}