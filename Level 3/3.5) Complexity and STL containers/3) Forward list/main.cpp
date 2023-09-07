//3.5) Complexity and STL containers

/*Purpose: Playing around with std::forward_list

C++11's std::forward_list is a fast, singly-linked container allowing efficient insertion and removal of elements
throughout the container, but lacks random access; it offers space efficiency over std::list when bidirectional 
iteration is unnecessary.
*/
//Author: Andrew Guerrand

//Modification dates: 6/20/2023

#include <iostream>
#include <forward_list>

int main()
{
//PART A) Create default list, a list with n elements and a given value, and a list that is built from an initialiser list (two forms).

    //Default constructed forward_list
    std::forward_list<int> list1;

    //List with n elements and a given value
    int n = 5;
    std::forward_list<int> list2(n, 10);    //5 elements, all with value 10

    //List built from an initializer list
    std::forward_list<int> list3{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

//PART B) Forward lists have no member functions to give their size. Write you own function in terms of 
//        std::distance().

    //Simply bind a lambda function that takes the distance between the beginning and end iterator of the container... !
    auto size_forward_list = [&](){return std::distance(list3.begin(), list3.end());};
    std::cout << "PART B: Distance between the beginning and end iterator of forward_list list3: " << size_forward_list() << std::endl;
    //Distance is 10, which makes sense, because there are 10 elements.

//PART C) Create code to insert values after a given position based on value, value and a count, two iterators and initialiser list. 
//        The code makes direct calls to std::forward_list::insert_after.

/*  std::insert_after of form:
    template<class InputIt>
    std::forward_list<T,Allocator>::insert_after( const_iterator POSITION, InputIt FIRST, InputIt LAST );

*/


    //Inserting a single value after a given position
    //Inserting after first element
    list3.insert_after(list3.begin(), 10);

    //Inserting a value and a count after a given position
    //Inserting after first element
    list1.insert_after(list3.begin(), 2, 20);

    //Inserting values using two iterators
    //Inserting after first element
    std::forward_list<int> values{30, 40, 50};
    list3.insert_after(list3.begin(), values.begin(), values.end());

    //Inserting values using an initializer list
    //Inserting after first element
    list3.insert_after(list3.begin(), {60, 70, 80});

    //Print the elements in the forward_list
    for (const auto& num : list3) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

//PART D) Create functions to erase values after a given position as well as in a range of iterators.

    //I will create wrapped lambda functions, rather than global functions (as I usually define global functions... Got to keep the skills sharp!)
    auto eraser_afterpos = [&](auto position) {
        if (position != list1.end()) {list1.erase_after(position, list1.end());}
    };

    auto eraser_range = [&](auto start, auto end) {
        if (start != list1.end() && end != list1.end()) {list1.erase_after(start, end);}
    };

//PART E) Create examples to show how splice and merge functionality work.

    //Splice example
    //std::splice_after -> moves elements from another forward_list
    std::forward_list<int> list4{100, 200, 300};
    std::forward_list<int> list5{400, 500, 600};
    
    //Splice after the first element of list4
    list4.splice_after(list4.begin(), list5);    //Move all elements from list5 to list4 after position
    
    std::cout << "\nPART E: Elements in list4 after SPLICE: ";
    for (const auto& num : list4) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    //Merge example
    //merge two sorted lists
    std::forward_list<int> list6{3, 6, 9};
    std::forward_list<int> list7{1, 4, 7};
    
    list6.sort();       //IMPORTANT: The forward lists should be sorted into ascending order.
    list7.sort();
    list6.merge(list7); //Merge list7 into list6 while maintaining the sorted order
    
    std::cout << "PART E: Elements in list6 after MERGE: ";
    for (const auto& num : list6) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}