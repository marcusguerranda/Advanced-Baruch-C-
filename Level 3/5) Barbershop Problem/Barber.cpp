//Barber.cpp

#include "Barber.hpp" //Importing header file

//Overloaded constructor
Barber::Barber(int id, std::shared_ptr<Queue>& queue, std::shared_ptr<SalonManager>& salon): m_id(id), m_queue(queue), m_salon(salon)
{
    std::unique_lock<std::mutex> lock{c_mutex};
    std::cout << "Barber " << m_id << " has come to work in the salon." << std::endl;
}

//Operator () overloading
void Barber::operator()()
{


    while(this->m_salon->BarberCondition())
    {
        std::cout << "IN OPERATOR () BARBER" << std::endl;
        if(this->m_queue->IsEmpty())
        {
            std::cout << "Barber " << m_id << " waiting." << std::endl;
            this->m_queue->WaitnotEmpty();    //Waiting till salon is no longer empty and that a customer enters the store
        }

        //Remove next customer in line from waiting room 
        std::string customerData = this->m_queue->Dequeue();

        // Barber is cutting hair
        std::cout << "Barber " << m_id << " is cutting hair for " << customerData << std::endl;
            
        //Generate a random time for barber cutting time
        srand(static_cast<unsigned int>(time(0)));      //Seed RNG with the current time
        int cuttingTime = rand() % 5 + 2;               //Random number between 1 and 5 (inclusive) --> Time of cutting between 1 and 5 seconds, randomly
        std::this_thread::sleep_for(std::chrono::seconds(cuttingTime));

        // Barber finished cutting hair
        std::cout << "Barber " << m_id << " finished cutting hair for " << customerData << std::endl;
        std::this_thread::yield();
    }
    std::cout << "OUT OPERATOR () BARBER" << std::endl;
}

