//Customer.cpp

#include "Customer.hpp"

//Overloaded constructor
Customer::Customer(int id, std::shared_ptr<Queue> queue, std::shared_ptr<SalonManager> salon): m_id(id), m_queue(queue), m_salon(salon){}


//Operator () overloading
void Customer::operator () ()
{
    std::cout << std::boolalpha;
    std::cout << "IS OPEN " << m_salon->IsOpen() << std::endl;

    std::unique_lock<std::mutex> lock{m_mutex};
    //Check if the associated queue is full in the SalonManager instance
    if (m_queue->IsFull()) 
    {
        std::cout << "Customer " << m_id << " arrived, but queue is full. Customer leaves." << std::endl;
    }
    else
    {
        std::string customerData = "Customer " + std::to_string(m_id);
        m_queue->Enqueue(customerData);
        std::cout << "Customer " << m_id << " arrived and is waiting in salon." << std::endl;
    }
}


