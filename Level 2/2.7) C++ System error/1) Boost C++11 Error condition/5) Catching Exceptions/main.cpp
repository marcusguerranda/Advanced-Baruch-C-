//2.7) C++ System error -> 5) Catching exceptions

//Purpose: catch a (simulated) exception thrown when setting the exception mask of an input file stream.

//Author: Andrew Guerrand

//Modification dates: 5/28/2023

/*
    A) In the catch block use e.code() with std::io_errc::stream. 
    B) If the comparison in a) is true, then:
        • Create an error code instance ec1 with e.code() as argument.
        • Create an error condition ec2 instance with ec1 as argument.
        • Print the properties value, message and error category of ec2.
    C) Test your code.
*/

#include <iostream>
#include <system_error>
#include <string>
#include <fstream>

//Function printing information for a std::error_code instance
void errorcode_printer(const std::error_code& source_error) 
{
    std::cout << "Error code value: " << source_error.value() << std::endl;
    std::cout << "Error message: " << source_error.message() << std::endl;
    std::cout << "Error category: " << source_error.category().name() << std::endl;
}

//Function printing information for a std::error_condition instance
void errorcondition_printer(const std::error_condition& source_error)
{
    std::cout << "Error code value: " << source_error.value() << std::endl;
    std::cout << "Error message: " << source_error.message() << std::endl;
    std::cout << "Error category: " << source_error.category().name() << std::endl;
}

int main()
{
    std::ifstream file(std::string("DOESNOTEXIST.txt"));
    try
    {
        // Set the exception mask of the file stream
        // In this case 1) logical error on I/O operation or 
        // 2) read/write error on I/O operation
        file.exceptions(file.failbit | file.badbit);
    }
    catch (const std::ios_base::failure& e)
    {
        if (e.code() == std::io_errc::stream)
        {
            //Creating an error code instance with e.code() as an arg
            std::error_code ec1(e.code()); 

            //Creating an error condition instance with error code ec1 as argument. Given it's platform independent, the category needs to be specified
            std::error_condition ec2(ec1.value(), ec1.category()); 

            //Printing value, message, and error category of ec1 and ec2.
            std::cout << "\nInformation regarding std::error_code ec1:" << std::endl;;
            errorcode_printer(ec1);
            std::cout << "\nInformation regarding std::error_condition ec2:" << std::endl;;
            errorcondition_printer(ec2);
        }
    }
    catch (...)
    {
        std::cout << "Catch all\n";
    }

    std::cout << std::endl;
    return 0;
}