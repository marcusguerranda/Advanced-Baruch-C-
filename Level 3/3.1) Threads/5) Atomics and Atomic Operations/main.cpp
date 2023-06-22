//3.1) Threads. 5) Atomic Operations

//Purpose: Become acquainted with the mechanics of using atomic data types and atomic operations in C++11

//Author: Andrew Guerrand

//Modification dates: 6/8/2023

#include <iostream>
#include <atomic>


int main()
{
//PART A: Create atomic objects of type long long, bool and int

    std::atomic_llong a_llong1;
    std::atomic_bool a_bool1;
    std::atomic_int a_int;

    std::cout << std::boolalpha;

//PART B: Determine which atomic types are lock-free.

    std::cout << "PART B: Determine which atomic types are lock-free. \n";
    //Are they lock-free?
    std::cout << "Atomic long long is lock free: " << a_llong1.is_lock_free() << std::endl;
    std::cout << "Atomic bool is lock free: " << a_bool1.is_lock_free() << std::endl;
    std::cout << "Atomic int is lock free: " << a_int.is_lock_free() << std::endl;
    std::cout << std::endl;

    //Are they always lock-free?
    std::cout << "Atomic long long is always lock free: " << a_llong1.is_lock_free() << std::endl;
    std::cout << "Atomic bool is lock always free: " << a_bool1.is_lock_free() << std::endl;
    std::cout << "Atomic int is lock always free: " << a_int.is_lock_free() << std::endl;
    std::cout << std::endl;

    //Printing out values prior to using .exchange() or .load()
    std::cout << "a_llong1 before exchange or loading: " << a_llong1 << std::endl;
    std::cout << "a_bool1 before exchange or loading: " << a_bool1 << std::endl;
    std::cout << "a_int before exchange or loading: " << a_int << std::endl;
    

//PART C: Atomically replace the value of one atomic object by another atomic object.

    std::cout << "\nPART C: Atomically replace value of one atomic object by another atomic object. \n";
    std::atomic_llong a_llong2(42);
    a_llong1.exchange(a_llong2);

    std::cout << "a_llong1 after exchange: " << a_llong1  << std::endl;

//PART D: Atomically load an atomic object and return its current value
    std::cout << "\nPART D: Atomically load an atomic object and return its current value. \n";

    std::cout << "Value of a_llong2: " << a_llong2.load()  << std::endl;
    std::cout << std::endl;
    return 0;
}


/*          NOTE FOR SELF:

                                                        std::atomic library

MEMBER FUNCTIONS:

    std::atomic::OPERATOR =
stores a value into an atomic object

    std::atomic::IS_LOCK_FREE()
checks if the atomic object is lock-free

    std::atomic::STORE()
atomically replaces the value of the atomic object with a non-atomic argument.
Useful when -> value assignment (ensure assignment operation of new value to atomic object (important) is performed atomically), state updates, communication between
threads, synchronization primitives (often used in the implementation of locks or flags. Allows for atomic updates to control variables or synchronization flags,
ensuring that changes are visibile to other threads)

    std::atomic::LOAD()
atomically obtains the value of the atomic object. Since atomic operations ensure that there are no data races or race conditions, 
using std::atomic::load guarantees that you get a consistent and up-to-date value of the atomic object.
Useful when: -> reading shared data, condition checking, synchronization with non-atomic variables


    std::atomic::OPERATOR T
loads a value from an atomic object

    std::atomic::EXCHANGE()
atomically replaces the value of the atomic object and obtains the value held previously.
Useful when: -> atomic swap (swap the value of an atomic object with another value), value update, shared resource handoff (in multithreading, you may 
need to hand off ownership of a shared resource from one thread to another), lock-free data structures (often used in the implementation of lock-free data
structures, such as lock-free queues or lists. It allows for atomic updates to the internal state of the data structure, ensuring consistency and thread
safety).

    std::atomic::COMPAE_EXCHANGE_WEAK()
    std::atomic::cCOMPARE_EXCHANGE_STRONG()
atomically compares the value of the atomic object with non-atomic argument and performs atomic exchange if equal or atomic load if not

    std::atomic::WAIT()
blocks the thread until notified and the atomic value changes

    std::atomic::NOTIFY_ONE()
notifies at least one thread waiting on the atomic object

    std::atomic::NOTIFY_ALL()
notifies all threads blocked waiting on the atomic object










SPECIALIZED MEMBER FUNCTIONS:

    std::atomic::fetch_add
atomically adds the argument to the value stored in the atomic object and obtains the value held previously

    std::atomic::fetch_sub()
atomically subtracts the argument from the value stored in the atomic object and obtains the value held previously

    std::atomic::fetch_and()
atomically performs bitwise AND between the argument and the value of the atomic object and obtains the value held previously

    std::atomic::fetch_or()
atomically performs bitwise OR between the argument and the value of the atomic object and obtains the value held previously

    std::atomic::fetch_xor()
atomically performs bitwise XOR between the argument and the value of the atomic object and obtains the value held previously








    std::atomic<T>::is_lock_free()

-> All atomic types except for std::atomic_flag may be implemented using mutexes or other locking operations, 
rather than using the lock-free atomic CPU instructions. Atomic types are also allowed to be sometimes lock-free, e.g. only aligned memory accesses 
are naturally atomic on a given architecture, misaligned objects of the same type have to use locks.
A lock-free operation means that the operation can be performed by multiple threads concurrently without the need for explicit locking mechanisms, 
such as mutexes or critical sections. Lock-free operations are generally more efficient because they avoid contention and synchronization overhead.
The is_lock_free function returns a bool value indicating whether the atomic operations on objects of type T are lock-free. If the function returns 
true, it means that the atomic operations on T are guaranteed to be lock-free. If it returns false, it means that the atomic operations may involve 
locks and are not guaranteed to be lock-free.
It's important to note that the lock-free property depends on the specific implementation and hardware architecture. The is_lock_free function 
allows you to query the lock-free property at runtime, enabling you to make decisions based on the availability of lock-free operations.



    std::atomic<T>::is_always_lock_free()

The std::atomic<T>::is_always_lock_free() function is similar to std::atomic<T>::is_lock_free(), but with a stronger guarantee.
While std::atomic<T>::is_lock_free() returns true if the atomic operations on objects of type T are lock-free, it does not provide a guarantee that
all instances of std::atomic<T> are lock-free. IT DEPENDS ON THE SPECIFIC IMPLEMENTATION AND HARDWARE ARCHITECTURE. 
On the other hand, std::atomic<T>::is_always_lock_free() provides a stronger guarantee. It returns true if all instances of std::atomic<T> are 
guaranteed to be lock-free. This means that REGARDLESS of the specific implementation or hardware architecture, all atomic operations on objects 
of type T will be performed in a lock-free manner.
The is_always_lock_free() function allows you to determine if lock-free operations are always available for std::atomic<T> objects. If it returns 
true, you can rely on the lock-free behavior of std::atomic<T>. If it returns false, it means that lock-free operations are not guaranteed for all 
instances of std::atomic<T>, and you should use caution when assuming lock-free behavior

*/