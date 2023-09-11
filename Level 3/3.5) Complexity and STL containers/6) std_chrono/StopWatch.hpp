//StopWatch.hpp

#include <iostream>
#include <chrono>

class StopWatch
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

    //Copy constructor -> prevent usage by putting into private -> non-defined for now
    StopWatch(const StopWatch&);

    //operator () overloading -> -> prevent usage by putting into private -> non-defined for now
    StopWatch& operator=(const StopWatch &);

public:
    //Default constructor
    StopWatch();

    //Start stop watch
    void StartStopWatch();

    //Stop start watch
    void StopStopWatch();

    //Reset startwatch
    void Reset();

    //Time computer
    double GetTime() const;

};




