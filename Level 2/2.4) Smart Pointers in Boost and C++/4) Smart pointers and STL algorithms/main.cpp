//2.4.4: Smart pointers and STL algorithms

//Purpose: In this case, we create a simple example of STL containers whose elements are smart pointers.

//Author: Andrew Guerrand

//Modification dates: 5/17/2023

/*
    a) Create a list of smart pointers to Base. In particular, test the above code with both shared and unique 
       pointers. Which option compiles and why does unique pointer not compile?
    b) Create a factory function to create instances of Derived and then add them to the list.
    c) Test the functionality and check that there are no memory leaks.
*/

#include <iostream>
#include <memory>
#include <list>


//Base class 
class Base
{    
private:
public:
    Base() {std::cout<<"Base constructor\n";};
    virtual void print() const = 0;

protected:
    virtual ~Base() { std::cout << "Base destructor\n\n"; };
};

//Derived class
class Derived : public Base
{  
private:
public:
    Derived() : Base() {std::cout << "Derived constructor\n\n"; }
    ~Derived() { std::cout << "Derived destructor\n"; }
    void print() const { std::cout << "derived object\n";}
};


//PART B: Create a factory function to create instances of Derived and then add them to the list
std::shared_ptr<Base> factory()
{
    std::shared_ptr<Base> s_ptr(new Derived());
    return s_ptr;
}

template<typename T>
int list_counter(std::list<T> source_list)
{
    return source_list.size();
}


int main()
{

/*
PART A: Create a list of smart pointers to Base. In particular, test the above code with both shared and unique 
        pointers. Which option compiles and why does unique pointer not compile?*/

    std::list<std::shared_ptr<Base>> sharedptr_list;    //Create a list which will contain shared pointers
    //std::list<std::unique_ptr<Base>> uniqueptr_list;  //Create a list which will contain unique pointers (won't work)

/*DOES NOT WORK: Interestingly enough, I cannot instantiate the above for a unique_ptr, because the destructor is protected in Base class.
                From the research I have done, it is because the mechanism for managing the lifetime of the objects differs between that of 
                shared pointers and unique pointers. 

                For shared pointers, the control block holds a reference count and a deleter function, which is part of the std::shared_ptr
                implementation (this is key). This specific deleter function is responsible for calling the destructor of the managed object 
                when the reference count = 0 (.use_count() ). Indepedent of whether the destructor of the object is protected or not, the deletion
                is done internally by the std::shared_ptr.

                In contrast, the unique pointer requires the calling of the Base destructor everytime an object is destroyed; however, since it is
                'protected' in our case, we are not able to do so correctly. */

//PART B: Create a factory function to create instances of Derived and then add them to the list
//PART C: Test the functionality and check that there are no memory leaks.


    std::cout << "\nPART C" << std::endl;

    //Before adding additional shared pointers to my list, I will output the number of shared pointers currently in the list
    std::cout << "Number of shared pointers currently in the 'sharedptr_list' list is: " << list_counter(sharedptr_list) << std::endl;
    for(int i=0;i<5;i++){sharedptr_list.push_back(factory());};    //Pushback shared pointers into list
    std::cout << "Number of shared pointers currently in the 'sharedptr_list' list is: " << list_counter(sharedptr_list) << std::endl;

    //Are there any memory leaks?
// -> Essentially, when creating the factory(), are we creating dynamic Derived objects every time, or are we simply creating shared pointer
//    pointing to the same derived object? The answer is the former: we are pointing to different dynamically created objects. Therefore,
//    when using .use_count(), we'll only have one instance automatically destroyed when the counter for shared pointers == 0.

//   Only way to verify this is to iterate over every shared pointer in the list and call .use_count() to check we are only pointing to one object or not.

    std::cout << std::endl;
    for(auto it = sharedptr_list.begin(); it!= sharedptr_list.end(); ++it)
    {
        std::cout << "Number of different shared_ptr instances managing the current object: " << (*it).use_count() << std::endl;
    }

    //Note: Once running the code, we can clearly see that the destructor is called for all 5 shared pointers (both in Derived and then Base).
    //      Memory is therefore automatically freed, and there are no memory leaks


    return 0;
}




/*
NOTES FOR SELF, for review:

    Memory Leaks: This occurs when memory is repeatedly allocated by a program but never freed. This leads to excessive memory 
    consumption and eventually leads to a system crash. 

    Dangling Pointers: A dangling pointer is a pointer that occurs at the time when the object is de-allocated from memory without
    modifying the value of the pointer.

    Wild Pointers: Wild pointers are pointers that are declared and allocated memory but the pointer is never initialized to 
    point to any valid object or address.

    Data Inconsistency: Data inconsistency occurs when some data is stored in memory but is not updated in a consistent manner.
    Buffer Overflow: When a pointer is used to write data to a memory address that is outside of the allocated memory block. 
    This leads to the corruption of data which can be exploited by malicious attackers.

    //Smart pointers:   -shared_ptr, 
                        -unique_ptr, 
                        -weak_ptr, 
                        -auto_ptr(deprecated)


    //std::shared_ptr<T>::use_count()
    Returns the number of different shared_ptr instances (this included) managing the current object. If there is no managed object, ​0​ is returned.
*/