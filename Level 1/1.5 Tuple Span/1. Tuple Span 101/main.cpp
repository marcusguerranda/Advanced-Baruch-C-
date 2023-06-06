//main.cpp

//Purpose: We create code that creates and manipulates tuples and we endeavor to emulate similar functionality when working with databases.

//Author: Andrew Guerrand

//Modification date: 4/12/2023

#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <tuple>
#include <array>
#include <vector>
#include <span>
#include <iterator>


using namespace boost::gregorian;

//Tuple alias to model some attributes of a Person consisting of a name, address, and date of a birth 
using Person = std::tuple<std::string, std::string, boost::gregorian::date>;

//Vector alias for 'People', where elements are different individual 'Person's
using People = std::vector<Person>;


//PART B:
void printPerson(const Person& source_person)
{
    std::cout << std::get<0>(source_person) << " lives in " << std::get<1>(source_person) << ", and was born in " << std::get<2>(source_person) << "." << std::endl;
};

//Sorts 'People' vector by name
void sortByFirstName(People& source_people) 
{
    std::sort(source_people.begin(), source_people.end(), [](const auto& a, const auto& b) {
        return std::get<0>(a) < std::get<0>(b);
    });
};

//Sorts 'People' vector by address
void sortByAddress(People& source_people) 
{
    std::sort(source_people.begin(), source_people.end(), [](const auto& a, const auto& b) {
        return std::get<1>(a) < std::get<1>(b);
    });
}

//Sorts 'People' vector by date of birth
void sortByDateOfBirth(People& source_people) 
{
    std::sort(source_people.begin(), source_people.end(), [](const auto& a, const auto& b) 
    {
        return std::get<2>(a) < std::get<2>(b);
    });
};

//operator << function that takes a std::ostream object and a Person object as arguments, and outputs the data members of the Person object in a desired format
std::ostream& operator << (std::ostream& os, const Person& source_person) 
{
    os << "Name: " << std::get<0>(source_person) << ", Address: " << std::get<1>(source_person) << ", Date of Birth: " << std::get<2>(source_person);
    return os;
};


//PART F:

//Print function using range-based for-loop
void printSpan_Range(const std::span<double>& source_span)
{
    for (const double& element : source_span) 
    {
        std::cout << element  << ", ";
    };
    std::cout << std::endl;
};

//Print function using iterators
void printSpan_Iterators(const std::span<double>& source_span)
{
    for(auto it = source_span.begin(); it != source_span.end(); it++)
    {
        std::cout << *it << ", ";
    };
    std::cout << std::endl;
};

//Print function using index operator []
void printSpan_Indexing(const std::span<double>& source_span)
{
    for (std::size_t i = 0; i < source_span.size(); ++i) 
    {
        std::cout << source_span[i] << ", ";
    };
    std::cout << std::endl;

    //Note to self: I choose to use std::size_t, because it ensures that the index variable is ALWAYS non-negative and can represent the maximum size of an
    //              object that can be allocated in memory. (prevents signed integer overflow when working with large spans)
}


//PART G:

//Print first N elements in span
std::span<double> Span_firstN(const std::span<double> source_span, const size_t& firstN)
{
    //USE .first(firstN) function!
    return source_span.first(firstN);
    
};


//Print last N elements in span
std::span<double> Span_lastN(const std::span<double> source_span, const size_t& lastN)
{
    //USE .last(lastN) function!
    return source_span.last(lastN);
};


//PART H:
void SubSpan(const std::span<double>& source_span, const int& first, const int& last)
{
    auto subspan = source_span.subspan(first, last);        //Create subspan using .subspan(first)
    printSpan_Range(subspan);                               //Print subspan using range-based for-loop function
};


//PART I: byte view of any spans
template <typename T>
void ByteView(const std::span<T>& source_span)
{
    auto bytes = std::as_writable_bytes(source_span);
    for (std::size_t i = 0; i < bytes.size(); ++i)
    {
        std::cout << std::setw(2)
                  << std::hex
                  << std::uppercase
                  << std::setfill('0')
                  << static_cast<int>(bytes[i]) << ' ';
    }
    std::cout << '\n' << std::endl;
};






// ************************************************************************************************************************


int main()
{
//PART A: Creating instances, and modifying elements within

    Person Emeric = std::make_tuple("Emeric G", "France, VDA", boost::gregorian::date{1996, Jul, 29});
    Person Andrew = std::make_tuple("Andrew G", "Canada, Montreal", boost::gregorian::date{1998, Mar, 6});
    Person William = std::make_tuple("William G", "France, VDA", boost::gregorian::date{2000, Dec, 14});
    std::cout << std::endl;


    //Modify elements (I could also define some setter functions which would help us alter the elements within )
    std::cout << "Address of Emeric, prior to altering address, is: " << std::get<1>(Emeric) << std::endl;
    std::get<1>(Emeric) = "South of France, Monaco";
    std::cout << "Address of Emeric, post altering address, is: " << std::get<1>(Emeric) << std::endl;

    //Modifying birthday... Process is straightforward
    std::cout << "Birthday of Andrew, prior to altering address, is: " << std::get<2>(Andrew) << std::endl;
    std::get<2>(Andrew) = boost::gregorian::date{1998, Jun, 7};
    std::cout << "Birthday of Andrew, post altering address, is: " << std::get<2>(Andrew) << std::endl;
    

//PART B: print elements in a Person instance
//Note: we assume that the formatting of these elements will be homogeneous and strictly respected.

    std::cout << std::endl;
    printPerson(Emeric);
    printPerson(Andrew);
    printPerson(William);
    std::cout << std::endl;

//PART C:

    //Making vector of my brothers and I as 'Person' instances
    //(could also use std::push_back, but much more tedious)
    People brothers_Guerrand{Emeric, Andrew, William};

//PART D:
    // Sort by name
    sortByFirstName(brothers_Guerrand);

    //VERIFICATION:
    //Among my three brothers, my name and address should come first, and thus should be the first element in the vector brothers_Guerrand
    std::cout << "The first 'Person' instance in the vector brothers_Guerrand, based off of sorted name, is " << brothers_Guerrand[0] << std::endl;
    std::cout << std::endl;

    // Sort by address
    sortByAddress(brothers_Guerrand);

    //VERIFICATION:
    //Among my three brothers, my name and address should come first, and thus should be the first element in the vector brothers_Guerrand
    std::cout << "The first 'Person' instance in the vector brothers_Guerrand, based off of sorted address, is " << brothers_Guerrand[0] << std::endl;
    std::cout << std::endl;

    // Sort by date of birth
    sortByDateOfBirth(brothers_Guerrand);
    
    //VERIFICATION:
    //Among my three brothers, my brother Emeric should come first (oldest, and thus birth of date lowest: 1996 < 1998 < 2000)
    std::cout << "The first 'Person' instance in the vector brothers_Guerrand, based off of sorted birthdate, is " << brothers_Guerrand[0] << std::endl;
    std::cout << std::endl;



//PART E: use of std::span

    //Fix-sized array
    std::array<double, 10> fixed_array1 = {0,1,2,3,4,5,6,7,8,9};

    double fixed_array2[10]{0,1,2,3,4,5,6,7,8,9};

    //Variable-sized array
    std::vector<double> variable_array1 = {0,1,2,3,4,5,6,7,8,9};

    //Creating span views of both of my fix- and variable-sized arrays (contiguous sequence of objects)
    auto s1 = std::span(fixed_array1);
    auto s2 = std::span(fixed_array2);
    auto s3 = std::span(variable_array1);

    //Printing the modified element in fixed_array1
    std::cout << "s1[0] = " << s1[0] << std::endl; 
    //Modifying an element in s1
    s1[0] = 99;
    //Printing the modified element
    std::cout << "s1[0] = " << s1[0] << std::endl; 


    //Printing the original element in variable_array1
    std::cout << "s3[0] = " << s3[0] << std::endl; 
    //Modifying an element in s3
    s3[0] = 99;
    //Printing the modified element
    std::cout << "s3[0] = " << s3[0] << std::endl; 


    //std::span<const double> s4= std::span<const double>(fixed_array1);    //See below
    //s4[0] = 99;

/*Answer: 
By default, std::span views are not read-only. Indeed, I have shown above one approach to modify the elements in fixed_array1 and variable_array1.
HOWEVER! There is a possible approach to make these views 'read-only'.

You can declare these spans as const and this will create a 'read-only' view of the fixed- and variable-sized arrays.

Example:    std::span<const double> s4= std::span<const double>(fixed_array1);

            s4[0] = 99; ERROR!!!!

            ERROR MESSAGE:
                                    error: assignment of read-only location 's4.std::span<const double>::operator[](0)'
                        157 |     s4[0] = 99;
*/          


//PART F:

    //For span s1
    std::cout << "\nFOR S1:" << std::endl;
    printSpan_Iterators(s1);
    printSpan_Range(s1);
    printSpan_Indexing(s1);

    //For s2
    std::cout << "\nFOR S2:" << std::endl;
    printSpan_Iterators(s2);
    printSpan_Range(s2);
    printSpan_Indexing(s2);

    //For s3
    std::cout << "\nFOR S3:" << std::endl;
    printSpan_Iterators(s3);
    printSpan_Range(s3);
    printSpan_Indexing(s3);


//PART G: Write functions to print first N and last N elements

    std::cout << "\nFIRST AND LAST N ELEMENTS EXERCISE" << std::endl;
    printSpan_Range(Span_firstN(s1,4));   //Print first 4 elements in s1 span
    printSpan_Range(Span_lastN(s2,4));    //Print last 4 elements in s2 span


//PART H: Define a function using std::subspan (here SubSpan() function, and which also prints back the subspan generated)

    std::cout << "\nSUBSPAN EXERCISE" << std::endl;
    SubSpan(s1, 0, 4);  //Prints subspan starting at index = 0 in span s1, and prints next 4 elements
    SubSpan(s1, 2, 4);  //Prints subspan starting at index = 2 in span s1, and prints next 4 elements


//PART I: // Bytes stuff

/*
The std::as_bytes function interprets the memory occupied by the data array as a sequence of bytes, regardless of its original type. 
The resulting const_bytes object can be used to access the bytes that represent the floating-point value of pi in memory.

The code then uses a range-based for loop to iterate over the bytes in the const_bytes object and print them out as hexadecimal values to the console. 
The std::setw, std::hex, std::uppercase, and std::setfill manipulators are used to format the output of each byte as a two-digit uppercase hexadecimal number with leading zeros.

Overall, this code demonstrates how to access the bytes of a floating-point value in memory and print them out in a readable format.
*/

    std::cout << "\nPART I DOWN BELOW:" << std::endl;

    float data[1]{ 3.141592f };
    auto const const_bytes = std::as_bytes(std::span{data});
    for (auto const b : const_bytes)
    {
        std::cout << std::setw(2) 
        << std::hex 
        << std::uppercase 
        << std::setfill('0')
        << std::to_integer<int>(b) << ' ';
    }
    std::cout << "\n" << std::endl;

    //I have now created a function to take any byte view of any type of span (and not for an array)

    std::string mystringtest = "Hello this is a test!";
    auto s4 = std::span<char>(mystringtest);

    ByteView<double>(s1);
    ByteView<double>(s2);
    ByteView(s3);
    ByteView(s4);

    
    return 0;
}





/*
The std::as_bytes and std::as_writable_bytes functions are both part of the C++20 standard library and can be used to create byte views of objects stored in memory. 
However, they differ in the type of byte view that they return and the operations that can be performed on the resulting view.

std::as_bytes returns a std::span of const std::byte> objects, which represents a non-modifiable view of the bytes of the input object. 
The resulting byte view can be used to read the contents of the input object as a sequence of bytes, but attempting to modify the 
bytes through the view results in undefined behavior.

On the other hand, std::as_writable_bytes returns a std::span of std::byte objects, which represents a modifiable view of the bytes of the input object. 
The resulting byte view can be used to both read and write the contents of the input object as a sequence of bytes. This allows for more flexibility in modifying 
the underlying data in a type-safe way.

To summarize, std::as_bytes provides a read-only view of the bytes of an object, while std::as_writable_bytes provides a read-write view of the bytes of an object.

*/