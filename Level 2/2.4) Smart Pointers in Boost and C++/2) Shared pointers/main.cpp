//2.4.2: Shared pointers

//Purpose: Objective of this exercise is to show shared ownership using smart pointers in C++.
//         Create two classes C1 and C2 that share a common heap-based object as data member.

//Author: Andrew Guerrand

//Modification dates: 5/16/2023

#include <iostream>
#include <memory>
#include "Point.hpp"

//Comments: for reasons of succintness, I include my header files in main.cpp. Usually, I would be defining these in separate header and source files.

//CREATE THE CODE FOR THE CLASSES C1 AND C2 EACH OF WHICH CONTAINS THE SHARED OBJECT FROM THE VALUE D ABOVE: std::shared_ptr<double> d;
class C1
{ 
private:
    //double* d;                        OLD WAY 
    //Shared object from the value d
    std::shared_ptr<double> d;

public:
    C1(std::shared_ptr<double> value) : d(value) {std::cout <<"C1 constructor\n";};
    virtual ~C1() {std::cout << "\nC1 destructor";};
    void print() const {std::cout << "Value " << *d; };
};

class C2
{
private:
    //Shared object from the value d
    std::shared_ptr<double> d;
public:
    C2(std::shared_ptr<double> value) : d(value) {std::cout <<"C2 constructor\n";}
    virtual ~C2() { std::cout <<"C2 destructor";}
    void print() const { std::cout <<"Value "<< *d; }
};



//CARRY OUT THE SAME EXERCISES AS IN STEPS A AND B BUT WITH A USER-DEFINED TYPE AS SHARED DATA
class C3
{
private:
    //Shared user-defined type as shared data (a 'Point' was suggested in the exercise, so I will use the same class previously defined)
    std::shared_ptr<Point> p;
public:
    C3(std::shared_ptr<Point> value) : p(value) {std::cout <<"C3 constructor\n";}
    virtual ~C3() { std::cout <<"\nC3 destructor";}
    void print() const { std::cout <<"Value "<< *p; }
};

class C4
{
private:
    std::shared_ptr<Point> p;
public:
    C4(std::shared_ptr<Point> value) : p(value) {std::cout <<"C4 constructor\n";}
    virtual ~C4() { std::cout <<"C4 destructor";}
    void print() const { std::cout <<"Value "<< *p; }
};



int main()
{
//PART B: Create instances of these classes in scopes so that you can see that resources are automatically released when 
//        no longer needed. To this end, employ the member function use_count() to keep track of the number of shared owners.
//        This number should be equal to 0 when the program exists.

    using sptr_double = std::shared_ptr<double>;
    using sdptr_point = std::shared_ptr<Point>;

    std::cout << "\nPART A TO C" << std::endl;
    {
    sptr_double firstptr(new double(3.33)); 
    //Count = 1
    std::cout << "\nThe number of times (OUT OF SCOPE) 'firstptr' is allocated: " << firstptr.use_count() << std::endl;
        {
        C1 example1(firstptr);  //Instantiating and initializing with 'firstptr', a shared pointer defined out-of-scope
        C2 example2(firstptr);
        //Count = 3
        std::cout << "The number of times (IN-SCOPE) 'firstptr' is allocated: " << firstptr.use_count() << std::endl;
        }
    //Count = 1
    std::cout << "\nThe number of times (OUT OF SCOPE) 'ptr_pt1' is allocated: " << firstptr.use_count() << std::endl;
    }
    
    //Count should be equal to 0 -> Conclusion: resources are deallocated automatically
    //std::cout << "The number of times (OUT OF SCOPE) 'firstptr' is allocated: " << firstptr.use_count() << std::endl;

    {
        Point p1(3.33, 4.44);   //First instance of point 
        sdptr_point ptr_pt1(new Point(3.33, 4.44));
        //Count = 1
        std::cout << "\n\nThe number of times (OUT OF SCOPE) 'ptr_pt1' is allocated: " << ptr_pt1.use_count() << std::endl;

        {
            C3 example3(ptr_pt1);
            C4 example4 (ptr_pt1);
            //Count = 1
            std::cout << "The number of times (OUT OF SCOPE) 'ptr_pt1' is allocated: " << ptr_pt1.use_count() << std::endl;
        }
        //Count = 1
        std::cout << "\nThe number of times (OUT OF SCOPE) 'ptr_pt1' is allocated: " << ptr_pt1.use_count() << std::endl;
    }
    //Count should be equal to 0 -> Conclusion: resources are deallocated automatically
    //std::cout << "The number of times (OUT OF SCOPE) 'ptr_pt1' is allocated: " << ptr_pt1.use_count() << std::endl;


/*PART D: Extend the above code by:
        -Assigning
        -Copying
        -Comparing two shared pointers 'sp1' and 'sp2'

Also, test the following features: 
        -Transfer ownership from sp1 to sp2
        -Determine if a shared pointer is the only owner of a resource
        -Give up the owernship and reinitialise the shared pointer as being empty
*/


    std::cout << "\nPART D\n" << std::endl;

    sdptr_point ptr1(new Point(3.33, 4.44));
    sdptr_point sp1 = ptr1;                     //Copy assignment operator
    sdptr_point sp2(sp1);                       //Copying
    std::cout << "Number of times 'ptr1' is used currently: " << ptr1.use_count() << std::endl;

    //Comparing two shared pointers 'sp1' and 'sp2'
    if(sp1 == sp2){std::cout << "Shared pointers are the same.\n";}
    else {std::cout << "Shared pointers are NOT the same.\n";};

    //Transfer ownership from one pointer to the other

    //Transfer ownership from sp1 to sp2.
    sp2 = std::move(sp1); 
    std::cout << "Number of times 'ptr1' is used currently: " << ptr1.use_count() << std::endl;
    //If count = 1, then it's the only owner of resources

    //Swap sp1 and sp2
    sp1.swap(sp2);
    std::cout << "Number of times 'ptr1' is used currently: " << ptr1.use_count() << std::endl;
    
    //Give up ownership and reinitialise the shared pointer as being empty.
    sp1.reset();
    std::cout << "Number of times 'ptr1' is used currently: " << ptr1.use_count() << std::endl;

    return 0;
}