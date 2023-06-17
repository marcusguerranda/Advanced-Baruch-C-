//2.7: C++ system error

//Purpose: 2) std::error_condition -> fundamentals. This exercise is concerned with the interface and properties of std::error_condition

//Author: Andrew Guerrand

//Modification dates: 5/28/2023

/*PART A) Create instances of std::error_condition based on the following requirements:
    • Default constructor.
    • Value (stored error code) and error category.
    • Based on std::errc code.
*/


/*PART B) Create a function that returns the following information pertaining to instances of std::error_condition:
    • Its error code (an integer).
    • Its message (a string).
    • The name of its category (a string).
The return type is std::tuple < std::string, int, std::string>.
*/

#include <iostream>
#include <system_error>
#include <string>
#include <tuple>

//PART B: would make more sense to return a std::tuple<int, std::string, std::string> given the order of bullet points
std::tuple<int, std::string, std::string> Error_Finder(const std::error_condition&& source_error)
{
    int error_code = source_error.value();           
    std::string message = source_error.message();
    std::string category = source_error.category().name();     

    //Make tuple of results of interest here
    auto result = std::make_tuple(error_code, message, category);
    return result;
}


int main()
{

//PART A: 

    std::cout << "PART A: default constructor, value and error category, and based on std::errc code." << std::endl;;
    
    //For default constructor (note: found on cppreference.com) + value and message
    std::error_condition one = std::generic_category().default_error_condition(EDOM);
    std::cout << "Category: " << one.category().name() << '\n'
              << "Value: " << one.value() << '\n'
              << "Message: " << one.message() << '\n';


    //For std::errc code (basically I saw that there were a lot, so might as well print all of them out of curiosity)
    //NOTE TO SELF: I did not find any proper way to define upper bound of number of std::errcs error categories. So I just took the numerical 
    //              value to loop through the error categories
    for (int i = 0; i < 256; ++i)
    {
        std::error_condition error(i, std::generic_category());
        std::cout << "#" << i << ": " << error.message() << '\n';
    }

    //VERY CURIOUSLY ENOUGH, one can see that error codes HERE in the range from #43 to #99 and from #141 to #255 do exist in the 'std::errc' enumeration.
    //But the explanation I got was that this is behavior and availability that also depends on the platform being used. In my current environment,
    //such errors cannot be encountered. Cool!


//PART B:
    
    auto t1 = Error_Finder(std::move(std::error_condition(1, std::generic_category())));
    auto t2 = Error_Finder(std::move(std::error_condition(2, std::generic_category())));
    auto t3 = Error_Finder(std::move(std::error_condition(3, std::generic_category())));

    std::cout << "\nTuple 1: \nError code is: " << std::get<0>(t1) << ", Error message: " << std::get<1>(t1) << ", and Error Category: " << std::get<2>(t1) << std::endl;
    std::cout << "Tuple 2: \nError code is: " << std::get<0>(t2) << ", Error message: " << std::get<1>(t2) << ", and Error Category: " << std::get<2>(t2) << std::endl;
    std::cout << "Tuple 3: \nError code is: " << std::get<0>(t3) << ", Error message: " << std::get<1>(t3) << ", and Error Category: " << std::get<2>(t3) << std::endl;
    std::cout << std::endl;

    return 0;
}