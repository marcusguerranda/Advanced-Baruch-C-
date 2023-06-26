//Customer.hpp

#ifndef Customer_hpp
#define Customer_hpp

#include "Queue.hpp"
#include "SalonManager.hpp"
#include <cstdlib>
#include <ctime>

class Customer
{
private:

    int m_id;                                   //ID of Customer
    std::mutex m_mutex;                         //Mutex
    std::shared_ptr<Queue> m_queue;             //Pointer to Queue to hold incoming customers
    std::shared_ptr<SalonManager> m_salon;      //Pointer to salon where barber works

public:

    //Overloaded constructor
    Customer(int id, std::shared_ptr<Queue> queue, std::shared_ptr<SalonManager> salon);

    //Operator () overloading
    void operator () ();
};


#endif //Customer_hpp


