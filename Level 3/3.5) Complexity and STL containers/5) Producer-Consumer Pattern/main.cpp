//3.5) Complexity and STL containers. 5) Producer-Consumer Pattern

/*Purpose:  Generalize exercise 2 to accomodate multiple concurrent producers and consumers of commands.
*/

//Author: Andrew Guerrand

//Modification dates: 6/20/2023


#include <iostream>
#include <queue>
#include <thread>
#include "Command.hpp"
#include "SynchronizingQueue.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include <boost/thread/thread.hpp>
#include <random>

struct FuncCompare
{
    bool operator()(Command left, Command right)
    {
        return left.priority() > right.priority();
    }
};

int main()
{
    const int num_producers = 3;
    const int num_customers = 3;

    std::function<Command(void)> voidlambda = [](){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(1, 20);
        int randomNumber = distribution(generator);

        std::function<double(double)> doubleLambda = [](double x) { return std::pow(x, 2) + 3.33;};
        return Command(doubleLambda, randomNumber);
    };

    SynchronizingQueue<Command, FuncCompare> queue1;

    std::thread t_producers[num_producers];
    for (int prod = 0; prod < num_producers; prod++)
    {
        Producer<Command, FuncCompare> producer(&queue1, voidlambda);
        t_producers[prod] = std::thread(producer);
    }

    std::thread t_consumers[num_customers];
    for (int cons = 0; cons < num_customers; cons++)
    {
        Consumer<Command, FuncCompare> consumer(&queue1);
        t_consumers[cons] = std::thread(consumer);
    }

    std::this_thread::sleep_for(std::chrono::seconds(15));
    queue1.ToggleFlag();

    // Join all threads when done
    for (int prod = 0; prod < num_producers; prod++)
    {
        t_producers[prod].join();
    }

    // Join all threads
    for (int cons = 0; cons < num_customers; cons++)
    {
        t_consumers[cons].join();
    }

    return 0;
}