//2.4.6: Weak pointers

//Purpose: A weak pointer is an observer of a shared pointer. It is useful to avoid dangling pointers, and when
//         we wish to use shared resources without assuming ownership.

//Author: Andrew Guerrand

//Modification dates: 5/18/2023



#include <iostream>
#include <memory>


int main()
{
/*a) Create a shared pointer, print the use count and then create a weak pointer that observes it. Print the 
use count again. What are the values?*/

    std::cout << "\nPART A:" << std::endl;

    //Note to self: If doing: double* init_ptr = new double(11.11), every shared_ptr will believe it's managing the object on its own.
    //You need to use std::make_shared<T>(...)
    std::shared_ptr<double> init_ptr = std::make_shared<double>(11.11);
    std::shared_ptr<double> sptr1(init_ptr);
    std::shared_ptr<double> sptr2(init_ptr);
    std::shared_ptr<double> sptr3(init_ptr);
    std::cout<< "Number of shared pointers pointing at dynamically created double: " << sptr1.use_count() << std::endl;

    //Comment: indeed, there are now 4 shared pointers pointing to dynamically allocated double '11.11'.




//PART B:) Assign a weak pointer to a shared pointer and check that the weak pointer is not empty.
 
    std::cout << "\nPART B:" << std::endl;
    std::weak_ptr<double> very_weak_ptr(init_ptr);
    std::cout<< "Number of shared pointers pointing at dynamically created double, AFTER creating weak pointer: " << sptr1.use_count() << std::endl;

/*c) Assign a weak pointer to another weak pointer; assign a weak pointer to shared pointer. What is the 
use count in both cases?*/

    //1. Assign a weak pointer to a shared pointer.
    //  A: we saw just above that the count does not change when we assign a weak pointer to a shared pointer.

    //2. Assign a weak pointer to another weak pointer. 
    std::weak_ptr<double> even_weaker_ptr (very_weak_ptr);
    std::cout<< "Count of pointers pointing to double, after creating a weak pointer pointing to a weak pointer pointing to a shared pointer...: " 
    << sptr1.use_count() << std::endl;

    //A: given that weak pointers are simply 'observer' pointers, they don't affect .use_count().

    return 0;
}



/*
NOTES FOR SELF:

The main differences between std::make_unique and std::make_shared are:

Ownership: std::make_unique creates a std::unique_ptr, which represents exclusive ownership of the dynamically allocated object. 
Only one std::unique_ptr can own the object at a given time. On the other hand, std::make_shared creates a std::shared_ptr, 
which allows multiple shared pointers to share ownership of the object.

Memory Allocation: std::make_unique uses new internally to allocate memory for the object, while std::make_shared uses a single 
allocation to allocate memory for both the object and a control block that manages the shared ownership.

Efficiency: Due to its single allocation, std::make_shared can be more efficient in terms of memory usage and performance compared 
to std::make_unique. It reduces the overhead of memory allocations and improves cache locality.

Availability: std::make_shared is available in C++11 and later versions, while std::make_unique is available starting from C++14.

In general, if you need exclusive ownership, use std::make_unique with std::unique_ptr. If you need shared ownership or want 
to optimize memory usage and performance, use std::make_shared with std::shared_ptr.

*/