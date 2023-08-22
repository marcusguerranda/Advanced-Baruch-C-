//3.4) C++11 Tasks. 4) Packaged Tasks

//Purpose:  The added value of using a PACKAGED task is that we can create a background task without starting it 
//          immediately. In particular, the task is typically started in a separate thread. 

//Author: Andrew Guerrand

//Modification dates: 6/19/2023

#include <iostream>
#include <future>
#include <random>
#include <cmath>
#include <queue>
#include <thread>

//ANDREW : See NOTES BELOW


// Thread function
double compute(double x, double y)
{
    //Wait a while
    std::default_random_engine dre(42);
    std::uniform_int_distribution<int> delay(0, 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay(dre)));
    
    return std::cos(x) * std::exp(y);
}


int main()
{
    std::cout << std::endl;
    double x = 0.0; 
    double y = 2.71;

    //A. 'Direct' tasks 
    std::future<double> fut = std::async(compute, x, y);

    // Get the shared data
    double result = fut.get();
    std::cout << "Result in PART A is: " << result << '\n';

//PART B: Rewrite/port the code in order to use a packaged task and delay execution
//IMPORTANT: In essence, we are decomposing the "std::async(compute, x, y)" code above

    /*Creating packaged task: encapsulates callable object, compute() function here, and ALLOWS it be invoked asynchronously
    VERY IMPORTANT: -> the 'std::packaged_task' class combines the functionality of both a promise and a future into a single entity.
                       and provides a mechanism to obtain a future from it. When the packaged task is invoked, it executes the encapsulated callable 
                       object and stores the result internally.

    EQUIVALENT code that found below is:
    
    //Create a promise
    std::promise<double> promise;

    //Get the future from the promise
    std::future<double> future = promise.get_future();

    //Launch a thread to execute the compute function
    std::thread thread( [&promise, x, y]() 
    {
        double result = compute(x, y);

        // Set the result in the promise
        promise.set_value(result);
    });
    */

    using TASKS = std::packaged_task<double (double, double)>;
    TASKS task1(compute);
    
    //Get the future associated with the packaged_task
    std::future<double> future2 = task1.get_future();

    //Start a thread and execute the task
    //In essence here, we can simply std::move(task1), whereas if dealing with a promise, we would need to set_value of the promise, and the future would get_future()!
    std::thread thread(std::move(task1), x, y);

    //Wait for the result
    result = future2.get();
    std::cout << "Result in PART B is: " << result << std::endl;

    //Join the thread
    thread.join();


//PART C: Create a queue of packaged tasks, dequeue each task, and execute it
//        Rather trivial subexercise: simply wrap exercise around queuing/dequeuing....
    std::cout << std::endl;
    std::queue<TASKS> queue1;

    //ENQUEUEING packages tasks into queue with appropriate values
    for(int i=0; i< 15; i++)
    {
        //Create packaged tasks
        TASKS queued_tasks(compute);
        //Enqueue by moving for efficiency
        queue1.push(std::move(queued_tasks));
    }

    int counter = 1;
    //DEQUEUE
    while (!queue1.empty())
    {
        TASKS task = std::move(queue1.front());
        queue1.pop();

        std::future<double> future_loop = task.get_future();
        std::thread thread_loop(std::move(task), x, y);
        double result = future_loop.get();
        std::cout << "Result " << counter << " in queue for PART C is: " << result << std::endl;
        thread_loop.join();
        counter++;
    }


    std::cout << std::endl;
    return 0;
}


/* 
    What is the difference between 'std::packaged_task' and 'std::async'?

-> Main difference lies in how they handle the association of a callable element with a future

std::async : higher-level utility function that combines the creation of a packaged task, launching it asynchronously, and returning a future that holds the result.
            -> encapsulates the process of creating a task,
            -> executing it asynchronously,
            -> obtaining the result in a single call.

std::packaged_task: explicitly wraps a callable element and allows you to obtain a future associated with that specific task. It decouples the task's execution 
                    from the creation of the future, GIVING YOU MORE CONTROL OVER WHEN AND HOW THE TASK IS EXECUTED.



*/