//2.7 C++ system error

//Purpose: Boost and C++11 error condition
         
//Author: Andrew Guerrand

//Modification dates: 5/27/2023

#include <iostream>
#include <fstream>
#include <string>
#include <system_error>                 //For C++11 error management
#include <boost/system/error_code.hpp>  //For Boost error management
#include <boost/system/system_error.hpp>
#include <boost/filesystem.hpp>

//Part A and part B together: write code to test an exisiting file and return type is boost::system::error_condition
//PART B: check whether the file exists. Employ the function boost::system::make_error_condition --> And I use here: boost::system::errc::no_such_file_or_directory
boost::system::error_condition FileOpenerandReader(const std::string& source_string)
{
    std::ifstream input_file(source_string);
    if(!input_file.is_open())
    {
        return boost::system::errc::make_error_condition(boost::system::errc::no_such_file_or_directory);
    }
    std::cout << "File open." << std::endl;
    std::cout << input_file.rdbuf();
    std::cout << "File closed." << std::endl;

/*  OR ALTERNATIVELY:

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::cout << line << std::endl;
    }

    inputFile.close();
*/
    return boost::system::error_condition();
}



//PART D: PORT THE CODE USING BOOST FUNCTIONALIITIES TO C++11 CODE
std::error_condition FileOpenerandReader2(const std::string& source_string)
{
    std::ifstream input_file(source_string);
    if (!input_file.is_open())
    {
        return std::make_error_condition(std::errc::no_such_file_or_directory);
    }
    
    std::cout << "File open." << std::endl;
    std::cout << input_file.rdbuf();
    std::cout << "File closed." << std::endl;
    
    input_file.close();
    
    return std::error_condition();
}



int main()
{
//PART A: Write the code and test it using an existing file as input. The return type is boost::system::error_condition

    //Create a text file and write some content to it
    std::ofstream outputFile("example.txt");
    if (outputFile.is_open()) 
    {
        outputFile << "Hello!" << std::endl;
        outputFile << "This is an example for 2.7) of level 2, advanced c++!" << std::endl;
        outputFile.close();
        std::cout << "\nFile created and written successfully." << std::endl;
    } 
    else 
    {
        std::cerr << "Failed to create the file." << std::endl;
        return 1;
    }

    //Reopen the file and read its contents
    //Write the code and test it using an existing file as input
    std::cout << "\nTesting with existing .txt file 'example.txt', using BOOST code. ";
    boost::system::error_condition result1 = FileOpenerandReader("example.txt");

    //Check the result
    if (result1.value() == 0) 
    {
        std::cout << "File opened and read successfully." << std::endl;
    } else 
    {
        std::cerr << "Failed to open the file. Error code: " << result1.value() << std::endl;
    }

    //Testing the code a non-existing file
    std::cout << "\nTesting a non-existent file 'nonexistingfile.txt', using BOOST code. " << std::endl; 
    boost::system::error_condition result2 = FileOpenerandReader("nonexistingfile.txt");
    //Check the result
    if (result2.value() == 0) 
    {
        std::cout << "File opened and read successfully." << std::endl;
    } else 
    {
        std::cerr << "Failed to open the file. Error code: " << result2.value() << " and error category: " << result2.category().name() << std::endl;
    }

//NOTE: the 'generic' category is usually the platform-independent error condition when calling a non-existent file.
//      It serves as a fallback category when a more specific category is not available or applicable.


//PART D: Port the Boost code to C++11 and test your program again.

//Retesting for an existing file, but with C++11 code
    std::cout << "\nTesting with existing .txt file 'example.txt', using C++11 code. " << std::endl;
    std::error_condition result3 = FileOpenerandReader2("example.txt");
    if(result3.value() == 0)
    {
        std::cout << "error value when calling 'example.txt. with C++11 code is 0, and thus the file exists and was opened+read."<< std::endl;
    }
    else
    {        
        std::cerr << "Failed to open the file. Error code: " << result3.value() << " and error category: " << result3.category().name() << std::endl;
    }


//Retesting for an non-existing file, but with C++11 code
    std::cout << "\nTesting with non-existing .txt file 'example2.txt', using C++11 code. " << std::endl;
    std::error_condition result4 = FileOpenerandReader2("example2.txt");
    if(result4.value() == 0)
    {
        std::cout << "error value when calling 'example2.txt. with C++11 code is 0, and thus the file exists and was opened+read."<< std::endl;
    }
    else
    {        
        std::cerr << "Failed to open the file. Error code: " << result4.value() << " and error category: " << result4.category().name() << std::endl;
    }

    std::cout << std::endl;
    return 0;
}



