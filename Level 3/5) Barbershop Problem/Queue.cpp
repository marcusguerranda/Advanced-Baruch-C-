#include "Queue.hpp"
#include <stdexcept>

//Constructor; m_queue will be created automatically when an instance of the Queue class is created
Queue::Queue(const int& numChairs):m_queue()
{
    if (numChairs < 1) 
    {
        throw std::invalid_argument("Number of chairs in salon must be greater than 0.");
    }
    max_size = numChairs;
    SalonChecker();
}

//Copy constructor
Queue::Queue(const Queue& other)
{
    std::lock_guard<std::mutex> lock(other.q_mutex);
    m_queue = other.m_queue;
    max_size = other.max_size;
}

//Copy assignment operator
Queue& Queue::operator=(const Queue& other)
{
    if (this == &other)
        return *this;

    std::lock(q_mutex, other.q_mutex);
    std::lock_guard<std::mutex> selfLock(q_mutex, std::adopt_lock);
    std::lock_guard<std::mutex> otherLock(other.q_mutex, std::adopt_lock);

    m_queue = other.m_queue;
    max_size = other.max_size;

    return *this;
}

//Move constructor
Queue::Queue(Queue&& other) noexcept
{
    std::lock_guard<std::mutex> lock(other.q_mutex);
    m_queue = std::move(other.m_queue);
    max_size = other.max_size;
}

//Move assignment operator
Queue& Queue::operator=(Queue&& other) noexcept
{
    if (this == &other)
        return *this;

    std::unique_lock<std::mutex> selfLock(q_mutex, std::defer_lock);
    std::unique_lock<std::mutex> otherLock(other.q_mutex, std::defer_lock);
    std::lock(selfLock, otherLock);

    m_queue = std::move(other.m_queue);
    max_size = other.max_size;

    return *this;
}

// Queue class that has thread synchronization
void Queue::Enqueue(const std::string& data)
{
    m_queue.push(data);     // Add data to the queue
    SalonChecker();         // Function that checks for the size of the queue and sets atomic flags plus notifies conditional variables 
    // Lock release here
}

// Get the data from the queue. Wait for data if not available
std::string Queue::Dequeue()
{
    std::string res = m_queue.front();  // Retrieve the data from the front of the queue
    m_queue.pop();                      // Remove the data from the queue
    SalonChecker();                     // Function that checks for the size of the queue and sets atomic flags plus notifies conditional variables
    return res;
    // Lock release here
}

// Get the current size of the queue
int Queue::Size() const
{
    return m_queue.size();
}

// Get the maximum size of the queue
int Queue::MaxSize() const
{
    return max_size;
}

// Getter function for atomic flag -> Empty
bool Queue::IsEmpty() const
{
    return m_flagEmpty.test();
}

// Getter function for atomic flag -> Full
bool Queue::IsFull() const
{
    return m_flagFull.test();
}

// Function to access condition variable m_condEmpty
// Once IsEmpty() is 'false', therefore that !IsEmpty() is 'true', then no longer waiting
void Queue::WaitnotEmpty() {
    std::unique_lock<std::mutex> lock(q_mutex);
    m_condnotEmpty.wait(lock, [this]() { return !IsEmpty(); });
}

// Function to access condition variable m_condFull
void Queue::WaitnotFull() {
    std::unique_lock<std::mutex> lock(q_mutex);
    m_condnotFull.wait(lock, [this]() { return !IsFull(); });
}

// Function that checks for the size of the queue and sets atomic flags plus notifies conditional variables
void Queue::SalonChecker()
{
    //If queue is full
    if (Size() == max_size)
    {
        m_flagFull.test_and_set();  //Set atomic flag to 'true'
        m_flagEmpty.clear();        //Set atomic flag to 'false'
        m_condnotEmpty.notify_one();//Cond. variable 'notEmpty' notifying one threads waiting
    }
    //If queue is empty
    else if (Size() == 0)
    {
        m_flagFull.clear();         //Set atomic flag to 'false'
        m_flagEmpty.test_and_set(); //Set atomic flag to 'true' 
        m_condnotFull.notify_one(); //Cond. variable 'notFull' notifying one threads waiting
    }
    //If queue is not empty nor full
    else {
        m_flagFull.clear();         //Set atomic flag to 'false'
        m_flagEmpty.clear();        //Set atomic flag to 'false' 
        m_condnotFull.notify_one(); //Cond. variable 'notFull' notifying one threads waiting
        m_condnotEmpty.notify_one();//Cond. variable 'notEmpty' notifying one threads waiting
    }
}   

