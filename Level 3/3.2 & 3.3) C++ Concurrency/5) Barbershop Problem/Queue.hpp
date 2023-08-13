//Queue.hpp

//Purpose: Buffer storing data between producer and consumer

//Author: Andrew Guerrand

//Modification dates: 6/7/2023


#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
#include <queue>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

class Customer; //Forward declaration
class SalonManager;

class Queue
{
private:
    std::queue<std::string> m_queue;            //Use stl queue to store data
    mutable std::mutex q_mutex;                 //Mutex to synchronize on

    std::atomic_flag m_flagEmpty;               //Atomic flag to wait for empty queue       
    std::atomic_flag m_flagFull;                //Atomic flag to wait for not-full 

    std::condition_variable m_condnotEmpty;     //Condition variable not empty
    std::condition_variable m_condnotFull;      //Condition variable not full

    int max_size;                               //Number of n chair available within a specific barber salon

public:

    //Constructor
    Queue(const int& numChairs);

    //Copy constructor
    Queue(const Queue& other);   

    //Copy assignment operator
    Queue& operator=(const Queue& other);

    //Move constructor
    Queue(Queue&& other) noexcept;

    // Move assignment operator
    Queue& operator = (Queue&& other) noexcept;

    //Queue class that has thread synchronization
    void Enqueue(const std::string& data);

    //Get the data from the queue. Wait for data if not available
    std::string Dequeue();

    //Get the current size of the queue
    int Size() const;

    //Get the maximum size of the queue
    int MaxSize() const;

    //Getter function for atomic flag -> Empty
    bool IsEmpty() const;
    
    //Getter function for atomic flag -> Full
    bool IsFull() const;

    //Function to access condition variable m_condEmpty
    //Once IsEmpty() is 'false', therefore that !IsEmpty() is 'true', then no longer waiting
    void WaitnotEmpty();

    //Function to access condition variable m_condFull
    void WaitnotFull();

    //Function that checks for the size of the queue and sets atomic flags plus notifies conditional variables
    void SalonChecker();

    //Destructor will be default, as not defined
};


#endif //Queue_hpp


