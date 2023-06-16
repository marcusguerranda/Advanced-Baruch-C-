//2.5 and 2.6 IEEE 754 and C floating point classification

//Purpose: Overflow errors, gaps/bits/ULP (unit in last place)
//         --> float_next: The next representable value that is greater than x. An overflow_error is thrown if no such value exists
//         --> float_prior: The next representable value that is less than x. An overflow_error is thrown if no such value exists
//         --> float_advance: Advance a floating-point number by a specified number of ULP (Unit in Last Place)
//         --> float_distance: Find the number of gaps/bits/ULP between two floating-point value
//         --> std/boost::nextafter(x,y):  Return the next representable value of x in the direction y

//Author: Andrew Guerrand

//Modification dates: 5/27/2023

//NOTE FOR SELF: overflow_error -> defines a type of object to be thrown as exception. It can be used to report an arithmetic overlow errors 
//               (that is, situations where a result of a computation is too large for the destination type)
//              --> an arithmetic overflow is te result of a calculation that exceeds the memory space deisgnated to hold it.

#include <iostream>
#include <boost/math/special_functions/next.hpp>
#include <stdexcept>

int main()
{
    double a = 0.1;
    double b = a + std::numeric_limits<double>::min();


//float_next
    try 
    {
        //Get the next representable value greater than a
        double next = boost::math::float_next(a);
        std::cout << "\nNext value of value a: " << next << std::endl;
    } 
    catch (const std::overflow_error& error) 
    {
        std::cout << "Overflow error occurred: " << error.what() << std::endl;
    }


//float_prior
    try 
    {
        //Get the next representable value less than a
        double prior = boost::math::float_prior(a); 
        std::cout << "Prior value of value a: " << prior << std::endl;
    } 
    catch (const std::overflow_error& error) 
    {
        std::cout << "Overflow error occurred: " << error.what() << std::endl;
    }


//float_advance
    try 
    {   //Advance a by 4 ULP (Unit in Last Place)
        double advanced = boost::math::float_advance(a, 4);
        std::cout << "Advanced value of value a: " << advanced << std::endl;

        //By 5
        advanced = boost::math::float_advance(a, 5);
        std::cout << "Advanced value of value a: " << advanced << std::endl;

        //By 6
        advanced = boost::math::float_advance(a, 6);
        std::cout << "Advanced value of value a: " << advanced << std::endl;
    } 
    catch (const std::overflow_error& error) 
    {
        std::cout << "Overflow error occurred: " << error.what() << std::endl;
    }

//float_distance
    try 
    {   //Get the number of gaps/bits/ULP between x and y
        double distance = boost::math::float_distance(a, b); 
        std::cout << "Distance between a and b: " << distance << std::endl;
    } 
    catch (const std::overflow_error& error) 
    {
        std::cout << "Overflow error occurred: " << error.what() << std::endl;
    }

//nextafter
    try 
    {
        //Get the next representable value of a in the direction of b
        double nextAfter = std::nextafter(a, b);  
        std::cout << "Next after value: " << nextAfter << std::endl;
    } 
    catch (const std::overflow_error& error) 
    {
        std::cout << "Overflow error occurred: " << error.what() << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

