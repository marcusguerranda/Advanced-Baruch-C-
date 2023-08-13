//3.2/3.3) C++ Concurrency: 5. Barbershop problem

/*Purpose:
    A barbershop consists of a waiting room with n chairs. There is one barber chair in the room. The barber 
    goes to sleep if there are no customers in the room. If a customer enters the barber shop and all chairs are 
    occupied then the customer leaves the shop. If the barber is busy and there are chairs available then the 
    customer occupies one of these free chairs. If the barber is asleep he is woken by a customer.”
*/

//Author: Andrew Guerrand

//Modification dates: 6/12/2023

/*
    A) Implement this template class, in particular its template parameters and functions for queuing and 
       dequeing.
    B) Add locking mechanisms to functions for synchronisation effects.
    C) Add notification mechanisms to allow thread notification (use condition variables for notification).
    D) Test the queue by creating producer and consumer threads.

*/

/* 
The main events in this example are:
    • Arrival of a client.
    • Starting of a service for a client.
    • Client leaves barber shop after having received service.
    • Client leaves the barber shop if it is full.
    • The barber waits (sleeps or does something else) if there are no clients waiting for service.

The objective of this exercise is to write a program to coordinate the barber and the customers using the 
Producer-Consumer pattern. 
*/

#include "Barber.hpp"
#include "Customer.hpp"
#include "Queue.hpp"

int main()
{
    int numChairs{6};
    int numBarbers{3};
    int simulation_minutes{2};
    std::cout << "\nNumber of chairs selected for our first and only barber salon will be 6.\n" << std::endl;

    Queue salon1(numChairs);
    std::shared_ptr<Queue> ptr_salon1 = std::make_shared<Queue>(salon1);

    SalonManager salonmanager1 (numBarbers, simulation_minutes, ptr_salon1);
    std::shared_ptr<SalonManager> ptr_manager1 = std::make_shared<SalonManager>(salonmanager1);

    std::cout << std::boolalpha;
    std::cout << "The salon is open: " << salonmanager1.IsOpen() << std::endl;
    std::cout << "The salon is open: " << ptr_manager1->IsOpen() << std::endl;
    
    //Now, let's run the salon!
    salonmanager1.Run(ptr_manager1);

    return 0;
}


/*  NOTE TO SELF:
Condition Variable: A condition variable is a synchronization primitive used to block a thread until 
a particular condition is met. It allows threads to wait for a specific event or state change. 
Condition variables are typically used in conjunction with a mutex to protect shared data. When a 
thread waits on a condition variable, it releases the associated mutex, allowing other threads to 
access the shared data. When the condition becomes true, another thread can notify the waiting thread, 
which then reacquires the mutex and continues execution.

*/