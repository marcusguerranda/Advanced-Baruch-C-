//StopWatch.cpp

#include "StopWatch.hpp"

//Default constructor
StopWatch::StopWatch(): startTime(), endTime(){}

//Start stop watch
void StopWatch::StartStopWatch()
{
    startTime = std::chrono::high_resolution_clock::now();
}

//Stop start watch
void StopWatch::StopStopWatch()
{
    endTime = std::chrono::high_resolution_clock::now();
}

//Reset startwatch
void StopWatch::Reset()
{
    startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
    endTime = startTime;
}

//Time computer
double StopWatch::GetTime() const
{
    //Get endTime and calculate difference with startTime
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double>(endTime - startTime);
    return duration.count();
};