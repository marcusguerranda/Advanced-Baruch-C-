//2.4.3: The deprecated smart pointer std::auto_ptr

//Purpose: 'std::auto_ptr' The following pointer is deprecated in C++11 and should not be used in future applications.

//Author: Andrew Guerrand

//Modification dates: 5/17/2023


#include <iostream>
#include <memory>

int main()
{
/*
    using std::auto_ptr;

    //Define auto_ptr pointers instead of raw pointers
    std::auto_ptr <double> d(new double (1.0));
    
    //Dereference
    *d = 2.0;

    //Change ownership of auto_ptr 
    //(after assignment, d is undefined)
    
    std::auto_ptr <double> d2 = d;
    *d2 = 3.0;
    std::cout << "Auto values: " << *d.get() << ", " << *d2.get();
*/




/*ANSWER:       warning: 'template<class> class std::auto_ptr' is deprecated: use 'std::unique_ptr' instead [-Wdeprecated-declarations]
                18 |     std::auto_ptr <double> d(new double (1.0));
            -> I get 'Auto values:' and then it just sits there and eventually crashes.

Auto pointers take ownership of the pointers assigned to them. No two auto pointers own the same element, since both would try to destruct them at some 
point.
-> Essentially, the problem really arises when using the assignment operator. d is left in an unknown state. We then try to dereference it AND use 
*d.get(), which is problematic. I suspect this is the reason as to why the code crashes at run-time.
*/




// USE STD::UNIQUE_PTR

    // Define unique_ptr pointers instead of auto_ptr
    std::unique_ptr<double> d(new double(1.0));
    
    // Dereference
    *d = 2.0;
    
    // Transfer ownership of unique_ptr
    std::unique_ptr<double> d2 = std::move(d);
    *d2 = 3.0;
    
    // Access values using get()
    //*d.get() will result in unefined behavior because d is now a nullptr (because of std::move above), and therefore points to nothing
    std::cout << "Unique_ptr values: " << *d2.get() << std::endl;

    return 0;
}