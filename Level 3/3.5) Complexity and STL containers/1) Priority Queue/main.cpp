/*3.5) Complexity and STL containers. 1) Priority Queues
In this exercise series, we'll:
    • Discuss some ADTs (Abstract Data Types), their complexity and implementation.
    • Useful utility (a timer class).
    • Single-threaded Command Processor pattern.
    • Synchronised queue and Producer-Consumer pattern.
    • Forward lists.

/*Purpose:
    A priority queue is a collection of elements each of which having a priority value. When an element is 
    chosen for deletion it is always the element with the highest priority. We thus see that a priority queue is 
    not a queue (the latter being FIFO (First In First Out)). We can implement priority queues as:
        • A list ordered by priority values (highest priority element at the end of the list).
        • A simple unordered list (O (n) complexity in the worst case).
        • A heap (supported in STL) (insertion and deletion have logarithmic complexity).
*/

//Author: Andrew Guerrand    

//Modification dates: 6/20/2023

//Priority_queue class -> defined already in STL!
//    template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>> 
//    class priority_queue

#include <iostream>
#include <queue>

int main()
{
/*a) Create a priority queue whose elements are long long using the above default template parameters. 
    In particular, perform the following:
    • Push values 66, 22, 44. 
    • Print top element and the pop it.
    • Push values 11,22,33.
    • Pop element.
    • Iterate in the priority until it is empty:
        o Print top
*/
    std::cout << "\nPART A\n";

    //Create priority queue
    std::priority_queue<long long> pqueue1;

    //Pushing elements
    pqueue1.push(66);
    pqueue1.push(22);
    pqueue1.push(44);

    //Print top element and then pop it
    std::cout << "Top element in priority queue currently is: " << pqueue1.top() << std::endl;
    pqueue1.pop();

    //Push values 11, 22, 33
    pqueue1.push(11);
    pqueue1.push(22);
    pqueue1.push(33);

    //Pop element
    pqueue1.pop();

    while(!pqueue1.empty()){
        //Print top element
        std::cout << "PQUEUE1: Top element in priority queue currently is: " << pqueue1.top() << std::endl;

        //Pop it
        pqueue1.pop();
    }

/*PART B: 
    Create a priority queue whose elements are long long whose container is std::deque and whose comparator is
    std::greater<long long>. Test this case with the data in part a) of the exercise. Inspect the output.
*/
    std::cout << "\nPART B\n"; 
    //Create a priority queue of long long elements with std::deque container and std::greater comparator
    // -> std::greater is a function object in STL is a default comparator in various containers + algos to perform comparison in a specific order.
    // -> will compare elements using greater-than comparator (>), and store elements in descending order(largest element at the top)
    //Hence, the first popped elements will be: 11, 22, 22, 33, etc. as anticipated.
    std::priority_queue<long long, std::deque<long long>, std::greater<long long>> pqueue2;

    //Pushing elements from part A
    pqueue2.push(66);
    pqueue2.push(22);
    pqueue2.push(44);
    pqueue2.push(11);
    pqueue2.push(22);
    pqueue2.push(33);

    // Iterate through the priority queue until it is empty
    while (!pqueue2.empty()) {
        //Print top element
        std::cout << "PQUEUE2: Top element in priority queue currently is: " << pqueue2.top() << std::endl;

        //Pop it
        pqueue2.pop();
    }

//PART C: Modify the code in part b) to use a lambda function instead of std::greater<long long>. Inspect the output.
    std::cout << "\nPART C\n";
    auto greater_than = [](long long& a, long long& b){return a>b;};

    /*-> Similar thought process to that of using std::greater. See below:
    
    If the comparison std::greater<T>(a, b) returns true:
        It indicates that a is considered greater than b based on the comparison criteria.
        In the context of std::priority_queue, this means that a has higher priority than b. So, a will be placed before b in the priority queue.
    
    If the comparison std::greater<T>(a, b) returns false:
        It indicates that a is NOT greater than b based on the comparison criteria.
        In the context of std::priority_queue, this means that a does not have higher priority than b. So, a will be placed after b in the priority queue.
    */

    //Create a priority queue of long long elements with std::deque container and lambda function comparator
    std::priority_queue<long long, std::deque<long long>, decltype(greater_than)> pqueue3(greater_than);

    //Pushing elements from part A
    pqueue3.push(66);
    pqueue3.push(22);
    pqueue3.push(44);
    pqueue3.push(11);
    pqueue3.push(22);
    pqueue3.push(33);

    //Iterate through the priority queue until it is empty
    while (!pqueue3.empty()) {
        //Print top element
        std::cout << "PQUEUE3: Top element in priority queue currently is: " << pqueue3.top() << std::endl;

        //Pop it
        pqueue3.pop();
    }

}




/*    NOTE FOR SELF:    STD::PRIORITY_QUEUE

KEY DIFFERENCES BETWEEN PRIORITY QUEUE AND QUEUE:
1. Ordering: In a queue (specifically a FIFO - First-In-First-Out queue), the elements are processed in the order they were added.
    The element that has been in the queue the longest (the front of the queue) is the next one to be processed. On the other hand, 
    in a priority queue, elements are processed based on their priority. The element with the highest priority (as defined by a comparison function or operator)
    is processed first.

2. Element Removal: In a queue, elements are typically removed from the front (or head) of the queue, maintaining the order in 
                    which they were added. This is done using the pop() or dequeue() operation. In a priority queue, elements are removed based on 
                    their priority. The highest-priority element is removed first using the pop() operation.

3. Ordering Requirements: A queue does not have any requirements for the ordering or comparison of its elements. 
                        It simply follows the FIFO principle. On the other hand, a priority queue requires a comparison function or operator 
                        to determine the priority of its elements. This comparison function defines the order in which elements are processed.

4. Usage: Queues are commonly used in scenarios where elements need to be processed in the order they arrive, 
          such as handling tasks or messages in a system. Priority queues, on the other hand, are used when elements have
          different levels of importance or urgency, and they need to be processed based on their priority. Examples include
          scheduling tasks in an operating system or implementing an efficient algorithm like Dijkstra's algorithm.



              
A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.

    //Constructor
        explicit priority_queue(const Compare& comp = Compare(), const Container& cont = Container());

    //Push element into the priority queue
        void push(const T& value);

    //Move version of push
        void push(T&& value);

    //Remove the top element from the priority queue
        void pop();

    //Access the top element
        const T& top() const;

    //Check if the priority queue is empty
        bool empty() const;

    //Get the number of elements in the priority queue
        size_t size() const;

    //Swap the contents of two priority queues
        void swap(priority_queue& other); 

*/