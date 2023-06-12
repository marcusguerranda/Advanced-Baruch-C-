//2.3.2: C++!4: Using init Captures to move objects into closures

//Purpose: When using lambda function, capturing by value may be costly in terms of performance, and 
//         capturing by reference can lead to dangling pointers.
//         These two capture modes do not work with move-only objects (e.g., std::unique_ptr, or std::future)
//         --> We therefore look into the 'init capture' syntax.

//Author: Andrew Guerrand

//Modification dates: 5/15/2023

/*      PART A: Modify this code using move semantics, that is the vector data is moved into the lambda function. Test 
                the new code, including the values in data after the code has run

        int size = 4; double val = 2.71;
        std::vector<double> data(size, val);

        // Default capture mode (not preferred)
        auto fun = [&data]() mutable
        {
            for (std::size_t i = 0; i < data.size(); ++i) 
            {
                data[i] = 3.14; std::cout << data[i] << ",";
            }
            std::cout << '\n';
        };
        fun();

        // 'data' still exists and has been modified
        for (std::size_t i = 0; i < data.size(); ++i)
        { data[i] = 3.14; std::cout << data[i] << ":"; }
*/

/*      PART B: Create the following code snippet:

    // C++14 init capture with local variables
    int x = 1'000'000; // This is a digit separator
    auto fun4 = [&r = x]() 
    {
        r *= 2;
        std::cout << "\nr: " << r;
    };
    fun4();
*/

/*      PART C: Migrate the following C++11 code that uses std::bind to emulate C++14 code that uses init capture:

    // Emulating generalized lambda capture with C++11
    int size2 = 3; double val2 = 1.41;
    std::vector<double> data2(size2, val2);
    std::array<double, 3> data3 = { 1.2, 2.4, 4.7 };

    auto fun3 = std::bind( [] (std::vector<double>& array, 
    std::array<double, 3> array2)
    {
        for (std::size_t i = 0; i < array.size(); ++i) 
        {
        array[i] = 3.14; std::cout << array[i] << "/";
        }
        std::cout << '\n';
        for (std::size_t i = 0; i < array2.size(); ++i)
        {
            array2[i] = 2.71; std::cout << array2[i] << "/";
        }
    }, std::move(data2), std::move(data3));
    fun3();

    if (0 == data2.size() || 0 == data3.size())
    {
        std::cout << "\nDouble arrays have no elements, OK\n";
    }
    else
    {
        std::cout << "\n Ouch!\n";
        for (std::size_t i=0;i<data2.size(); ++i)
            {std::cout<<data2[i]<< "^"; }
        for (std::size_t i = 0; i < data3.size(); ++i)
            {std::cout<<data3[i]<< "^"; }
    }
*/

//CONCLUSION THAT IS TO BE MADE FROM THIS EXERCISE: C++14 syntax is more elegant and user-friendly




#include <iostream>
#include <vector>
#include <array>
#include <functional>

int main()
{
    std::cout << "\n\tPART A:" << std::endl;
    int size = 4; 
    double val = 2.71;
    std::vector<double> data(size, val);

    //Move semantics used
    //move data into capture by using std::move
    auto fun = [data = std::move(data)]() mutable
    {
        for (std::size_t i = 0; i < data.size(); ++i) 
        {
            data[i] = 3.14; 
            std::cout << data[i] << ",";
        }
        std::cout << '\n';
    };
    fun();


//PART B:

    std::cout << "\n\tPART B:";
    // C++14 init capture with local variables
    int x = 1'000'000; // This is a digit separator
    auto fun4 = [&r = x]() 
    {
        r *= 2;
        std::cout << "\nr: " << r;
    };
    fun4();


//PART C:
    //Using C++14 init capture rather than using std::bind(), required prior to C++14

    std::cout << "\n\n\tPART C:" << std::endl;

    int size2 = 3; double val2 = 1.41;
    std::vector<double> data2(size2, val2);
    std::array<double, 3> data3 = { 1.2, 2.4, 4.7 };

    //Lambda below
    auto fun3 = [array = std::move(data2), array2 = std::move(data3)] () mutable
    {
        for (std::size_t i = 0; i < array.size(); ++i) 
        {
            array[i] = 3.14; std::cout << array[i] << "/";
        }
        std::cout << '\n';
        for (std::size_t i = 0; i < array2.size(); ++i)
        {
            array2[i] = 2.71; std::cout << array2[i] << "/";
        }
    };
    fun3();

    if (0 == data2.size() || 0 == data3.size())
    {
        std::cout << "\nDouble arrays have no elements, OK\n";
    }
    else
    {
        std::cout << "\n Ouch!\n";
        for (std::size_t i=0;i<data2.size(); ++i)
            {std::cout<<data2[i]<< "^"; }
        for (std::size_t i = 0; i < data3.size(); ++i)
            {std::cout<<data3[i]<< "^"; }
    }
    
    return 0;
}



/*  NOTES FOR SELF:

See excellent C++ notes here! : https://github.com/peter-can-write/cpp-notes/

In C++11, it was not possible to move objects into lambdas, introducing possible expensive copies. In C++14, there exists the concept 
of “init captures”, also called “generalized lambda captures”, which allow you to specify, in the capture brackets:

C++14 introduced the concept of init capture, which allows you to capture variables by value or reference and initialize them at the same time.

In the code you provided, the init capture [&r = x] captures the variable x by reference and binds it to the reference variable r. 
This allows the lambda function fun4 to modify the value of x indirectly through r.

The benefit of using init capture is that you can capture and initialize variables in one line of code, making your code more concise 
and easier to read. Additionally, init capture allows you to capture non-copyable objects by reference, such as std::unique_ptr or std::mutex, 
which cannot be copied but can be moved.

In the example you provided, the lambda function fun4 multiplies the value of x by 2 and prints it to the console. By using init capture, 
the lambda function can access and modify x without having to pass it as a parameter or capture it by value.
*/