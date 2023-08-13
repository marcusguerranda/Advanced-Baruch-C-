#include "SalonManager.hpp"
#include "Barber.hpp"
#include "Customer.hpp"

//Constructor specifying the number of barbers in a salon, and the number of chairs in a salon (size of)
SalonManager::SalonManager(const int& numBarbers, const int& simulationTime, std::shared_ptr<Queue> queue): m_Barbers(numBarbers), m_simTime(simulationTime),m_queue(queue)
{   
    //Set atomic flag to 'true'
    //std::memory_order_acquire -> enforces a rule that ensures other threads see the modification made by an atomic operation before they perform any subsequent operations.
    m_SalonOpen.test_and_set(std::memory_order_acquire);
    std::cout << "The salon is open for barbers to come in." << std::endl;
    //Salon is opened! (see relevant flags)
}

//Copy constructor
SalonManager::SalonManager(const SalonManager& copy_manager):
      m_Barbers(copy_manager.m_Barbers),
      m_simTime(copy_manager.m_simTime),
      m_queue(copy_manager.m_queue)
{
    //std::atomic_flag does not have a copy constructor unfortunately, so we need to about it the manual way
    m_SalonOpen.clear();
    if (copy_manager.m_SalonOpen.test()) 
    {
        m_SalonOpen.test_and_set();
    }
}



//Run the salon operation
void SalonManager::Run(std::shared_ptr<SalonManager>& shared_manager)
{
    std::cout << "The salon is now accepting new customers. Barbers are ready to cut some hair!" << std::endl;

    int tmp_sim = m_simTime;

    //Start the simulation timer. 
    //std::memory_order_release --> memory ordering constraint that ensures that the store operation performed by m_SalonOpen is visible to other threads.
    //This ensures that the modification o the 'm_SalonOpen' atomic flag is visible to other threads.
    std::thread timerThread([&tmp_sim, this]() 
    {
        std::this_thread::sleep_for(std::chrono::minutes(tmp_sim));         //Sleep for 'simulationTime'
        m_SalonOpen.clear(std::memory_order_release);                       //Set atomic flag to 'false'
    });

    //Start the Barber's threads --> barbers are coming to work to the salon each at a time
    while(BarberCondition())
    {
        std::vector<std::thread> barberThreads;
        //For-loop. I define the upper limit as m_Barbers+1 because I start index at 1. Does not make sense to have a Barber id = 0...
        for (int id = 1; id<(m_Barbers+1); id++)
        { 
            //Lambda emplacing back into barber thread vector + calling operator() overloading
            //Lambda captures this pointer (access member variables and functions)
            //Lambda captures 'shared_manager' shared pointer by value
            std::cout << std::boolalpha;
            std::cout << "IS IT OPEN: " << IsOpen() << " \nIS THE QUEUE EMPTY: " << m_queue->IsEmpty() << " \nor FULL: " << m_queue->IsFull() << std::endl;
            
            barberThreads.emplace_back([this, id, &shared_manager]() 
            {

                Barber b(id, m_queue, shared_manager);
                b(); // Call operator()
            });
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::vector<std::thread> customerThreads;
        int customerId = 0;
        //While salon is still open to new customers, AND that barbers are still working (BarberCondition() == 'true')
        while (m_SalonOpen.test())
        {
            //Loop to add customers when store is still open to new customers AND salon is not full. Do so until the salon no longer accepts customers
            //Check if the salon is full: if so, then wait before adding a customer to waiting room in salon
            //It's important to note that in a multi-threaded environment, there is a possibility of spurious wake-ups, where a thread may be woken up 
            //without the condition it was waiting for actually being true. To handle such spurious wake-ups, using a while loop is recommended to recheck the condition after waking up.

            //Lambda emplacing back into customer thread-vector
            customerThreads.emplace_back([this,customerId, &shared_manager]() 
            {
                std::cout << std::boolalpha;
                std::cout << "MY GODDAMN SALON IS OPEN: " << this->IsOpen()<< std::endl;
                Customer c(customerId, m_queue, shared_manager);
                c(); // Call operator()
            });
            customerId++;

            //Generate a random time for customer arrival
            srand(static_cast<unsigned int>(time(0)));
            int arrivalTime = rand() % 10 + 1;         //Random number between 1 and 10 (inclusive) --> Time of arrival between 1 and 5 seconds, randomly

            //Sleep for the generated arrival time
            std::this_thread::sleep_for(std::chrono::seconds(arrivalTime));
        }

        //Join customer threads
        for (auto& thread : customerThreads)
        {
            thread.join();
        }
        
        //Join barber threads
        for (auto& thread : barberThreads)
        {
            thread.join();
        }
    }

    timerThread.join();
}

//Getter for atomic flag, and ensures proper synchronization with a mutex
bool SalonManager::IsOpen()
{
    std::unique_lock<std::mutex> lock(open_mutex);
    return m_SalonOpen.test();
}



//Function returning compounded atomic flag on whether the salon is ready to close or not
bool SalonManager::BarberCondition()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    //Equivalent: If the store is no longer open AND the queue is empty, then barbers are free to leave because customers have all been dealt with
    //            If one of these conditions are not met, then the salon is technically still open and barbers still need to work!
    
    /*
    std::cout << std::boolalpha;
    std::cout << "Queue is EMPTY: " << m_queue->IsEmpty() << ", Queue is FULL:" << m_queue-> IsFull() << std::endl;
    std::cout << "Salon is OPEN: " << this->IsOpen() << ", Size: " << m_queue->Size() << std::endl;
    std::cout << std::endl;*/
    
    if( (IsOpen()  == false) && this->m_queue->Size() == 0)
    {
        return false;
    }
    else{return true;};
}



