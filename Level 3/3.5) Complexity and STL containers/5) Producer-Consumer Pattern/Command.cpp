//Command.cpp
#include "Command.hpp"
#include <thread>

//Overloaded constructor
Command::Command(const FunctionType& algorithm, long priority): algo(algorithm), ID(priority){}
    
//Execute executable commands
void Command::Execute(double x)
{
    //Introduce delay to simulate a heavy algorithm
    //  boost::this_thread::sleep(boost::posix_time::millisec(5000));
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));       //Replaced Boost functionalities with that of STL...
    std::cout << algo(x) << '\n';
}
    
//Priority number 
int Command::priority() const
{
    return ID;
}


