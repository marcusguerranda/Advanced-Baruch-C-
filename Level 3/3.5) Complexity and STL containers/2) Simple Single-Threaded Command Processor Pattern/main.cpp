//3.5) Complexity and STL containers. 2) Simple single-threaded command processor pattern

/*Purpose:  Create a mini-application. We'll generalize it in module 5.
            -> It's a single-threaded producer consumer pattern in which executable commands are inserted into a priority queue.
            When finished, consumer code executed each command in the priority queue in turn before popping it.
*/

//Author: Andrew Guerrand

//Modification dates: 6/20/2023

#include <iostream>
#include <queue>
#include "Command.hpp"

//Alias for function wrapper
using FunctionType = std::function<double (double)>;

//Comparator function
struct CommandComparator 
{
    bool operator()(const Command& cmd1, const Command& cmd2) const 
    {
        return cmd1.priority() > cmd2.priority();
    }
};


int main()
{
//PART A) Create a comparator for Command to compare two of its instances.
// -> see above

//PART B) Create several instances of Command, using function wrapper and defined lambda functions
    FunctionType cube = [](double x) { return x * x * x; };
    FunctionType sqrt = [](double x) { return std::sqrt(x); };
    FunctionType square = [](double x) { return x * x; };

    Command cmd1(square, 2);
    Command cmd2(cube, 3);
    Command cmd3(sqrt, 1);

//PART C) Create a priority queue of commands and insert the objects from part b) into it.

    std::priority_queue<Command, std::vector<Command>, CommandComparator> commandQueue;

    commandQueue.push(cmd1);
    commandQueue.push(cmd2);
    commandQueue.push(cmd3);

//PART D) Execute each command in the priority queue until it is empty.
    while (!commandQueue.empty()) 
    {
        Command cmd = commandQueue.top();
        cmd.Execute(11.11);
        commandQueue.pop();
    }   

/*The results are straightforward. sqrt will be first, sqr will be second, cube will be third in order of processing.
    3.33317
    123.432
    1371.33
*/

    return 0;
}