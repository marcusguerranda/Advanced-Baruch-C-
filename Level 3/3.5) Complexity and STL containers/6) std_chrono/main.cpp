//3.5) Complexity. 6) std::chrono

//Purpose:  we create an adapter class for certain functionality in the std::chrono library. The 
//          objective is to create a class to measure how long it takes for an operation to complete.

//Author: Andrew Guerrand

//Modification dates: 6/20/2023

#include <iostream>
#include "StopWatch.hpp"

void TediousPrinter()
{
     for(int i=0; i<10000; i++)
     {
        std::cout<< "I am in TediousPrinter, just wasting time for my StopWatch class to time" << std::endl;
     }
}

int main()
{
        StopWatch stop1;
        stop1.StartStopWatch(); //Starting time
        TediousPrinter();       //Printing
        stop1.StopStopWatch();  //Stopping time
        std::cout << "Time to print all this nonsense is: " <<  stop1.GetTime() << std::endl; //Getting time

        //Reset and then reget time
        stop1.Reset();
        std::cout << "Time after being reset is: " <<  stop1.GetTime() << std::endl;         //Getting time



    return 0;
}




/*
    PERSONAL NOTES:

    std::chrono::system_clock 
            -> Clock classes provide access to the current time_point. It is intended to represent the real time, and thus
               it can be translated in some way to and from calendar representations

    std::chrono::steady_clock
            -> Clock classes provide access to the current time_point, and is specifically designed to calculate time intervals.

    std::chrono::high_resolution_clock
            -> The members of clock classes provide access to the current time_point. Is the clock with the shortest tick period. 
               It may be a synonym for system_clock or steady_clock.
    
    std::chrono::duration
            -> A duration object expresses a time span by means of a count and a period.
            Internally, the object stores the count as an object of member type rep (an alias of the first template parameter, Rep), 
            which can be retrieved by calling member function count.
            This count is expresed in terms of periods. The length of a period is integrated in the type (on compile time) by its 
            second template parameter (Period), which is a ratio type that expresses the number (or fraction) of seconds that elapse in each period

    std::chrono::time_point
            -> A time_point object expresses a point in time relative to a clock's epoch.
            Internally, the object stores an object of a duration type, and uses the Clock type as a reference for its epoch.

*/