//3.2/3.3) C++ Concurrency:  1. Atomic Operations on Shared Pointers

//Purpose: learn some more C++11 syntax and features and to apply them to several simple parallel design patterns.

//Author: Andrew Guerrand

//Modification dates: 6/8/2023

/*
    In general, shared pointers are not thread-safe. However, reading the count while another thread modifies 
    a shared pointer does not introduce a race condition but the value may not be up-to-date. 
    The syntax in this context is a bit tricky. In particular, you have to take memory ordering into account.
*/


#include <iostream>
#include <memory>
#include <atomic>

struct X
{
    double val;

    X() : val(0.0) {}

    void operator ()()
    {
        std::cout << val << std::endl;
    }
};
// C++11

template <typename T>
using GenericPointerType = std::shared_ptr<T>;
using PointerType = GenericPointerType<X>;

int main()
{
    //A) Create an instance x of class PointerType and give it a value.

    std::cout << "\nPART A) Create an instance x of class PointerType and give it a value.\n";
    //Use std::make_shared to create instance of std::shared_ptr
    PointerType x= std::make_shared<X>();   //Creating a dynamic X instance -> Note to self: don't use raw pointers using 'new'
    x->val = 3.3;                           //Assigning value to x

    //B) Create a second instance x2 and atomically store its value in x.
    std::cout << "\nPART B: Create a second instance x2 and atomically store its value in x\n";
    PointerType x2= std::make_shared<X>();  //Creating a dynamic X instance
    x2->val = 5.5;      
    std::cout << "Old value of x is: "; (*x)();
    std::atomic_store(&x, x2);              //Important: expected second argument to be a value, not pointer or reference
    std::cout << "New value of x is: "; (*x)();

    //C) Create an instance x3 and exchange it with both x and x2.
    //std::atomic_exchange(std::atomic<T>* obj, std::atomic<T>::value_type desr): 
    //Atomically replaces the value pointed to by obj with the value of desr and returns the value obj held previously, as if by obj->exchange(desr)
    PointerType x3 = std::make_shared<X>();
    x3->val = 6.6;
    
    //Printing values
    std::cout << "\nPART C: Create an instance x3 and exchange it with both x and x2\n"; 
    std::cout << "Old value of x is: "; (*x)();
    std::cout << "Old value of x2 is: "; (*x2)();
    std::cout << "Old value of x3 is: "; (*x3)();

    PointerType old_x3= std::atomic_exchange(&x3, x2);   //Replacing x3 with x2. See explanation above of std::atomic_exchange. x3 is now equal to 5.5
    old_x3 = std::atomic_exchange(&x3, x);               //Replacing x3 with x

    std::cout << "New value of x, after exchange between x3 and x/x2, is: "; (*x)();
    std::cout << "New value of x2, after exchange between x3 and x/x2, is: "; (*x2)();
    std::cout << "New value of x3, after exchange between x3 and x/x2, is: "; (*x3)();

    //D) Keep tabs on the use count of these instances.
    //std::shared_ptr::use_count -> returns the number of different shared_ptr managing the current object
    std::cout << "\nPART D: Keep tabs on the use count of these instances\n";
    std::cout << "Number of different shared_ptr instances managing x is: " << x.use_count() << std::endl;
    std::cout << "Number of different shared_ptr instances managing x2 is: " << x2.use_count() << std::endl;
    std::cout << "Number of different shared_ptr instances managing x3 is: " << x3.use_count() << std::endl;

    PointerType random = std::make_shared<X>();
    random = x3;
    std::cout << "Number of different shared_ptr instances managing x3, NOW, is: " << x3.use_count() << std::endl;

/*
Use count is 4 for all of them, besides the line above. Well why is that???

The most convincing explanation for this would be that atomic operations transfer ownership between shared pointers, without releasing owernship.
This is why the use_count increases.

*To be confirmed by Avi
*/



    //E) Why is std::atomic<std::shared_ptr> not possible?

/*
Answer from cppreference.com:

If multiple threads of execution access the same instance of shared_ptr without synchronization and any of those accesses 
uses a non-const member function of shared_ptr then a data race will occur; the shared_ptr overloads of atomic functions 
can be used to prevent the data race

*/

    //F) Are shared pointers lock-free?
    std::cout << "\nPart F) Are shared pointers lock-free?" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "Shared pointers are lock-free : " << std::atomic_is_lock_free(&random) << std::endl;

    std::cout << std::endl;
    return 0;
}
