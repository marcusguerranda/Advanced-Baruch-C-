//Command class

#ifndef Command_hpp
#define Command_hpp

#include <iostream>
#include <chrono>
#include <functional>
#include <cmath>

//GIVEN CODE IN EXERCISE 3.5.2 + MY IMPLEMENTATIONS

//Alias for function wrapper
using FunctionType = std::function<double (double)>;

class Command
{
private:
    long ID;            //Priority of command
    FunctionType algo;  //Function wrapper

public:
    //Overloaded constructor
    Command(const FunctionType& algorithm, long priority);
    
    //Execute executable commands
    void Execute(double x);
    
    //Priority number 
    int priority() const;

};

#endif //Command_hpp

