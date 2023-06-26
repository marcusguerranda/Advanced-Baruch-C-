//SallonManager.hpp

//Purpose: Header file for the SalonManager class, defining the implementation of one hair salon, with possibly multiple barbers at once.

//Author: Andrew Guerrand

//Modification dates: 6/13/2023

#ifndef SalonManager_hpp
#define SalonManager_hpp

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <atomic>
#include <cstdlib>
#include "Barber.hpp"
#include "Customer.hpp"
#include "Queue.hpp"

class Barber;   // Forward declaration
class Customer; // Forward declaration
class Queue;


//SalonManager class
//IMPORTANT: use std::enable_shared_from_this template class, to pass on this* SalonManager instance as a shared pointer that Barbers and Customers can
//           point back to!
class SalonManager
{
private:
    int m_Barbers;                            //Number of barbers in a salon
    int m_simTime;                            //Time the salon is open to new customers
    std::shared_ptr<Queue> m_queue;           //Pointer to Queue to hold incoming customers
    std::mutex m_mutex, open_mutex;           //Mutex for synchronization
    std::atomic_flag m_SalonOpen;             //Flag to signal end of simulation time and that salon is no longer accepting customers


public:

    //Overloaded constructor
    SalonManager(const int& numBarbers, const int& simulationTime, std::shared_ptr<Queue> queue);

    //Copy constructor
    SalonManager(const SalonManager& copy_manager);

    //Run the salon operation
    void Run(std::shared_ptr<SalonManager>& shared_manager);

    //Getter for atomic flag, and ensures proper synchronization with a mutex
    bool IsOpen();
    
    //Function returning whether the barbers are yet to still be working or not
    bool BarberCondition();

    //Destructor
    ~SalonManager() = default;
};

#endif // SalonManager_hpp

