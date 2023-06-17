//2.7) C++ system error -> 3) Portable error conditions corresponding to POSIX Error codes

//Purpose: concerns the class std::error_condition, how to instantiate it, and how to access some of its properties.

//Author: Andrew Guerrand

//Modification dates: 5/28/2023

/*
a) Create error condition instances based on the following POSIX error codes (use scoped enumerator 
std::errc ):
    • io_error.
    • network_unreachable.
    • no_such_file_or_directory.
    • not_a_socket.
    • permission_denied.
b) Create an std::error_condition object based on the value 128 and the generic error category.
c) Use std::make_error_condition (with std::io_errc as argument) to create an instance of 
std::error_condition.

*/

#include <iostream>
#include <system_error>

int main()
{

//PART A: Create error condition instances based on the following POSIX error codes (use scoped enumerator std::errc):
//    • io_error.
//    • network_unreachable.
//    • no_such_file_or_directory.
//    • not_a_socket.
//    • permission_denied.

    std::cout << "\nPART A" << std::endl;
    std::error_condition error1 (std::errc::io_error);
    std::error_condition error2 (std::errc::network_unreachable);
    std::error_condition error3 (std::errc::no_such_file_or_directory);
    std::error_condition error4 (std::errc::not_a_socket);
    std::error_condition error5 (std::errc::permission_denied);

    std::cout << "Error value of 'io_error' is: " << error1.value() << ", category is: " << error1.category().name() << ", and message: " << error1.message() << std::endl;
    std::cout << "Error value of 'network_unreachable' is: " << error2.value() << ", category is: " << error2.category().name() << ", and message: " << error2.message() << std::endl;
    std::cout << "Error value of 'no_such_file_or_directory' is: " << error3.value() << ", category is: " << error3.category().name() << ", and message: " << error1.message() << std::endl;
    std::cout << "Error value of 'not_a_socket' is: " << error4.value() << ", category is: " << error4.category().name() << ", and message: " << error4.message() << std::endl;
    std::cout << "Error value of 'permission_denied' is: " << error5.value() << ", category is: " << error5.category().name() << ", and message: " << error5.message() << std::endl;


//PART B: Create an std::error_condition object based on the value 128 and the generic error category

    std::error_condition error6 (128, std::generic_category());
    std::cout << "Based on the error value 128, value is: " << error5.value() << ", category is: " << error5.category().name() << ", and message: " << error5.message() << std::endl;

//PART C: Use std::make_error_condition (with std::io_errc as argument) to create an instance of std::error_condition.

    std::error_condition error7 = std::make_error_condition(std::io_errc::stream);
    std::cout << "Error value of std::io_errc: " << error7.value() << ", category is: " << error7.category().name() << ", and message: " << error7.message() << std::endl;

    return 0;
}