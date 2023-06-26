//Barber.hpp

//Purpose :Barber class producing data and sending to buffer (here a std::queue)

//Author: Andrew Guerrand

//Modification dates: 6/7/2023

#ifndef Barber_hpp
#define Barber_hpp

#include "Queue.hpp"
#include "SalonManager.hpp"
#include <cstdlib>
#include <ctime>

//Forward declaration
class SalonManager;

//Barber class producing the data that will be sent to the queue
class Barber
{
private:

    int m_id;                                       //ID of Barber
    std::mutex m_mutex, c_mutex;                    //Mutex for constructor and then the rest in terms of functionality calling
    std::shared_ptr<Queue> m_queue;                 //Pointer to Queue to hold incoming customers
    std::shared_ptr<SalonManager> m_salon;          //Pointer to salon where barber works

public:
    //Overloaded constructor
    Barber(int id, std::shared_ptr<Queue>& queue, std::shared_ptr<SalonManager>& salon); 

    //Operator () overloading
    void operator () ();
};

#endif //Barber_hpp



