//2.7) C+ system error -> 4. error code fundamentals

//Purpose: Using std::error_code for platform dependent errors

//Author: Andrew Guerrand

//Modification dates: 5/28/2023

/*
    A) Create a default error code and an error code with a platform-dependent error code value and an 
    error category.
    
    B) Create a function that returns the following information pertaining to instances of std::error_code:
    • Its error code (an integer).
    • Its message (a string).
    • The name of its category (a string).
    The return type is std::tuple < std::string, int, std::string> .
    
    C) Test equality/inequality of instances of std::error_code and std::error_condition using 
    operators == and !=.
*/

#include <iostream>
#include <system_error>
#include <string>
#include <tuple>


//PART B
//Function returning the error code, the message, and the name of the category of the instance of std::error code
//Given the order of the bullet points, my function below returns rather a tuple of int, string, and string.
std::tuple<int, std::string, std::string> ErrorFinder (const std::error_code& source_error)
{
    int error_code = source_error.value();
    std::string error_message = source_error.message();
    std::string error_name = source_error.category().name();

    return std::make_tuple(error_code, error_message, error_name);
}


int main()
{
//PART A: Create a default error code, and an error code with a platform-dependent error code value AND an error category

    //Default error code
    std::error_code error_code;

    //Platform-dependent error code
    std::error_code platformdependent1 (2, std::generic_category());
    std::error_code platformdependent2 (3, std::generic_category());
    std::error_code platformdependent3 (4, std::generic_category());
    
    auto tuple1 = ErrorFinder(error_code);
    auto tuple2 = ErrorFinder(platformdependent1);
    auto tuple3 = ErrorFinder(platformdependent2);
    auto tuple4 = ErrorFinder(platformdependent3);  

    //Printing out info from tuple storing results of interest for default std::error_code
    std::cout << "\nDEFAULT -> Code: " << std::get<0>(tuple1) << ", message: " << std::get<1>(tuple1) << ", and name: " << std::get<2>(tuple1) << std::endl;

    //Printing out info from tuple storing results of interest for std::error_code of error value 2
    std::cout << "\nERROR VALUE 2 -> Code: " << std::get<0>(tuple2) << ", message: " << std::get<1>(tuple2) << ", and name: " << std::get<2>(tuple2) << std::endl;
    
    //Printing out info from tuple storing results of interest for std::error_code of error value 3
    std::cout << "\nERROR VALUE 3 -> Code: " << std::get<0>(tuple3) << ", message: " << std::get<1>(tuple3) << ", and name: " << std::get<2>(tuple3) << std::endl;
    
    //Printing out info from tuple storing results of interest for std::error_code of error value 4
    std::cout << "\nERROR VALUE 4 -> Code: " << std::get<0>(tuple4) << ", message: " << std::get<1>(tuple4) << ", and name: " << std::get<2>(tuple4) << std::endl;
    


//PART C:    
    std::cout << "\nPART C: testing equality and inequality for std::error_code and std::error_condition" << std::endl;

    std::error_condition errorCondition;
    std::error_condition error_condition1(2, std::generic_category());
    std::error_condition error_condition2(3, std::generic_category());
    std::error_condition error_condition3(4, std::generic_category());

//TESTING == sign
    if (error_code == errorCondition) {
        std::cout << "The error code and error condition are equal." << std::endl;
    } else {
        std::cout << "The error code and error condition are not equal." << std::endl;
    }

    if (platformdependent1 == error_condition1) {
        std::cout << "The error code and error condition of error code value 2 are equal." << std::endl;
    } else {
        std::cout << "The error code and error condition of error code value 2 are not equal." << std::endl;
    }

//TESTING INEQUALITY != sign
    if (platformdependent2 == error_condition2) {
        std::cout << "The error code and error condition of error code value 3 are equal." << std::endl;
    } else {
        std::cout << "The error code and error condition of error code value 3 are not equal." << std::endl;
    }

    if (platformdependent3 == error_condition3) {
        std::cout << "The error code and error condition of error code value 4 are equal." << std::endl;
    } else {
        std::cout << "The error code and error condition of error code value 4 are not equal." << std::endl;
    }


    //Conclusion: as we can see, SO FAR, the error_code (platform dependent) and error_condition (platform independent) are the same.
    //            HOWEVER, this is not guaranteed for other error code values.

    return 0;
}

