//2.4.5: Custom deleter

/*Purpose: 

    Shared and unique pointers support deleters. A deleter is a callable object that executes some code before 
    an object goes out of scope. A deleter can be seen as a kind of callback function. We first give a simple 
    example to show what we mean: we create two-dimensional points as smart pointers. Just before a point goes 
    out of scope a callback delete function will be called:

        auto deleter = [](Point* pt)-> void
        { std::cout << "Bye:" << *pt; };
        The corresponding code is:
        using SmartPoint = std::shared_ptr<Point>;


//Author: Andrew Guerrand

//Modification dates: 5/17/2023


A) The goal of this exercise is to open a file, write some data to the file an then close it when we are finished writing. 
Under normal circumstances we are able to close the file. However, if an exception occurs before the file can be closed the 
file pointer will still be open and hence it cannot be accessed. 
In order to ensure exception safety we employ a shared pointer with a delete function in the constructor, for example by using a function object:
std::shared_ptr<FILE> mySharedFile(myFile, FileFinalizer()); where FileFinalizer is a function object. 

B) Create a free function and a stored lambda function that also play the role of custom deleters for this 
problem.
C) Test the code for the three kinds of deleter functions (the delete closes the file).
D) Create a small loop in which records are added to the file; throw an exception at some stage in the 
loop, catch the exception and then open the file again. Does it work?
*/

#include <iostream>
#include <memory>
#include <fstream>  //Stream class to read and write from/to files


// Function object
struct FileFinalizer
{
    void operator()(FILE* file) const
    {
        fclose(file);   //Close the file
    };
};

// Free function
void freeFunctionFileFinalizer(FILE* file)
{
    fclose(file);   //Close the file
}

// Lambda function
auto lambda = [](FILE* file)
{
    fclose(file);   //Close the file
};

int main()
{
/*
    A) The goal of this exercise is to open a file, write some data to the file an then close it when we are finished writing. 
    Under normal circumstances we are able to close the file. However, if an exception occurs before the file can be closed the 
    file pointer will still be open and hence it cannot be accessed. 
    In order to ensure exception safety we employ a shared pointer with a delete function in the constructor, for example by using a function object:
    -> std::shared_ptr<FILE> mySharedFile(myFile, FileFinalizer()); 
    -> where FileFinalizer is a function object.*/


    std::cout << "PART A\n" << std::endl;

    try
    {
        FILE* fileptr1;
        FILE* fileptr2;
        FILE* fileptr3;

        fopen_s(&fileptr1,"myFile1.txt", "a");
        fopen_s(&fileptr2, "myFile2.txt", "a");
        fopen_s(&fileptr3,"myFile3.txt", "a");

        std::shared_ptr<FILE> file1(fileptr1, FileFinalizer());
        std::shared_ptr<FILE> file2(fileptr2, freeFunctionFileFinalizer);
        std::shared_ptr<FILE> file3(fileptr3, lambda);
            
        // Testing file opening and writing
        if (file1 && file2 && file3)
        {
            // Write data to the files
            fprintf(file1.get(), "Data written to file 1 ");
            fprintf(file2.get(), "Data written to file 2 ");
            fprintf(file3.get(), "Data written to file 3 ");

            std::cout << "Data written in three .txt files created." << std::endl;
            // The files will be automatically closed and deleted when the shared_ptr objects go out of scope
        }
        else
        {
            std::cout << "Failed to open one or more files." << std::endl;
        }
    
        std::ifstream checkFile1("myFile1.txt");
        std::ifstream checkFile2("myFile2.txt");
        std::ifstream checkFile3("myFile3.txt");

        if (checkFile1.good() && checkFile2.good() && checkFile3.good())
        {
            std::cout << "All files still exist." << std::endl;
        }
        else
        {
            std::cout << "One or more files no longer exist." << std::endl;
        }

        //Everything works for now. Let's now throw an error.
        throw  std::runtime_error("Oh no, an unexpected error message has arisen.");
    }
    catch(const std::exception& e)
    {
        FILE* new_ptr;
        fopen_s(&new_ptr, "myFile1.txt", "a");
        std::shared_ptr<FILE> test_ptr(new_ptr, lambda);
        //Writing more data to the first txt file
        for(int i=0; i<10; i++)
        {
            fprintf(test_ptr.get(), "A new record added ");
        }
        //fclose(new_ptr)   Will be managed by shared_ptr directly
    }

//What I find cool with my implementation is that I use append "a" rathern than "w+". I can reaccess my file and see the effects of rerunning the code on the file
//I find this more realistic, than closing and deleting the contents of the file, and then recreating one, etc.
    
    return 0;
}