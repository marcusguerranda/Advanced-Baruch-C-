//2.8) STL Bitset and boost dynamic bitset

//Purpose: Introduce compact data structures to model containers whose elements 
//         are bits. To this end, we discuss C++11 compile-time bitsets and dynamic bitsets in Boost. The two libraries 
//         have the same interface for all intents and purposes.

//Author: Andrew Guerrand

//Modification dates: 5/28/2023

/*
    A) Create bitsets from unsigned long and unsigned long long.
    B) Create bitsets from full strings (for example, “01010”). Create a bitset from parts of strings based on a 
       start index and the number of bits to use.
    C) In the case of strings (for example), use exception handling to check for out-of-range values and invalid 
       arguments (bits that are neither 0 nor 1).
    D) Set the bits in a bitset in different ways:
        • Set/reset all bits.
        • Flip the bits.
        • Test if none, all or any bits are set.
        • Access the elements.
        • Count the number of set bits.
    E) Convert a bitset to std::string, unsigned long and unsigned long long.
    F) Test if two bitsets are equal or unequal.
*/


#include <iostream>
#include <bitset>
#include <stdexcept>
#include <string>

int main()
{
//Part A:

    std::cout << "\nPART A: Bitsets from unsigned long and unsigned long long. " << std::endl;
    unsigned long int ul_value = 123456789UL;
    unsigned long long int ull_value = 987654321012345678ULL;

    // Bitset from unsigned long and unsigned long long with a size of 64 bits
    std::bitset<sizeof(unsigned long)*8> bitset_ul(ul_value);
    std::bitset<sizeof(unsigned long long)*8> bitset_ull(ull_value);
    std::cout << "Bitset of unsigned long: " << bitset_ul << std::endl;
    std::cout << "Bitset of unsigned long long: " << bitset_ull << std::endl;



//PART B: 
//OF FORM ->  std::bitset<N> bitset_cut(str, start_index, num_bits);.
//            Will take     '(num_bits - start index) + 1'    indeces.

    std::cout << "\nPART B: Bitsets from full and parts of string, based on a start index and the numbe of bits to use." << std::endl;
    
    //Create bitsets from full strings (for example, “01010”).
    std::bitset<5> bitset_s("01010");

    //Create a bitset from parts of strings based on a start index and the number of bits to use.
    //Here, I take string 'str' and create a bitset using the characters from index 5 to 19 (inclusive)
    std::string str = "0110101 ";
    //std::string simple = "Hello, simple.";    --> bitset only accepts 0 and 1... 

    //METHOD 1
    std::bitset<5> bitset_cut(str.substr(2, 5)); //Start at index 2 and take the next 5 characters of the string
    
    //METHOD 2
    std::bitset<4> bitset_cut2(str, 2, 4);   //Start at index 2, and take the next 4 characters of the string (2,3,4,5) ...

    std::cout << "Bitset 'bitset_s' created from a string is " << bitset_s << std::endl;
    std::cout << "Bitset 'bitset_cut' created from part of a string is: " << bitset_cut << std::endl;
    std::cout << "Bitset 'bitset_cut2' created from part of a string is: " << bitset_cut2 << std::endl;
    
//PART C: in the case of strings, use exception handling to check for 'out-of-range' values and 'invalid arguments' (bits that are neitherr 0 or 1)

    std::cout << "\nPART C: out-of-range and invalid arguments error handling." << std::endl;
//Out-of-range
    try 
    {
        std::string str2{"110101"};
        std::bitset<8> bitset_cut3(str2, 10, 7); // Start at index 10 (out of range), take the next 7 characters
        std::cout << "Bitset: " << bitset_cut3 << std::endl;
    } catch (const std::out_of_range& error) {
        std::cout << "Out-of-range error: " << error.what() << std::endl;
    }


//Invalid arguments
    try
    {
        std::string bitset_str = "202z01c0 HELLLOOO";
        for (char c : bitset_str)
        {
            if (c != '0' && c != '1')
            {
                throw std::invalid_argument("Invalid character in bitset string");
            }
        }
        std::bitset<8> invalid_bitset{bitset_str};
    } catch (const std::invalid_argument& error) {
        std::cout << "Invalid argument error: " << error.what() << std::endl;
    }

//PART D: set the bits in a bitset in different ways:

    std::cout << "\nPART D: setting the bits in different ways." << std::endl;
    std::bitset<8> bitset_part_d("01010111");
    std::cout << "'bitset_part_d' is: " << bitset_part_d << std::endl;

    //Setting all bits to 0 such that we have: 01010111 -> 00000000
    std::cout << "Setting all bits to 0 by using .reset()" << bitset_part_d.reset() << std::endl;

    //Setting all bits to 1 such that we have: 00000000 -> 11111111
    std::cout << "Setting all bits to 1 by using .set(): " << bitset_part_d.set() << std::endl;

    //Flip the bits such that we have: 11111111 -> 00000000
    std::cout << "Flipping the bits will give: " << bitset_part_d.flip() << std::endl;

    //Testing if none, all, or any are set
    std::cout << std::boolalpha;
    std::cout << "Current bitset for 'bitset_part_d' is: " << bitset_part_d << std::endl;
    std::cout << "None of the bits are set: " << bitset_part_d.none() << std::endl;
    std::cout << "All of the bits are set: " << bitset_part_d.all() << std::endl;
    std::cout << "Any of the bits are set: " << bitset_part_d.any() << std::endl;

    //Accessing the elements in a bitset-> Two methods: .test() and [] brackets
    std::cout << "The third element in 'bitset_part_d' is ON: " << bitset_part_d.test(2) << std::endl;
    bitset_part_d.flip(2);
    std::cout << "After flipping the third element in 'bitset_part_d', the third element is ON: " << bitset_part_d.test(2) << std::endl;
    std::cout << "The third element in 'bitset_part_d' is: " << bitset_part_d[2] << std::endl;

    //Counting the number of elements:
    std::cout << "Current bitset for 'bitset_part_d' is: " << bitset_part_d << std::endl;
    std::cout << "Number of elements in 'bitset_part_d' is: " << bitset_part_d.count() << std::endl; //00000100 -> 1 element

//PART E: converting a bitset into a std::string, unsigned long, and unsigned long long

    std::cout << "\nPART E: " << std::endl;
    std::bitset<8> new_bitset("01010111");
    std::cout << "Converting '01010111' to std::string gives: " << new_bitset.to_string() << std::endl;
    std::cout << "Converting '01010111' to unsigned long gives: " << new_bitset.to_ulong() << std::endl;
    std::cout << "Converting '01010111' to unsigned long long gives: " << new_bitset.to_ullong() << std::endl;

//PART F: Test if two bitsets are equal or unequal

    std::cout << "Is 'new_bitset' and 'bitset_part_d' equal? " << (new_bitset == bitset_part_d) << std::endl;
    new_bitset.reset(); 
    bitset_part_d.reset();

    std::cout << "We have reset both 'new_bitset' and 'bitset_part_d', such that they are now: " << new_bitset << ", and " << bitset_part_d << std::endl;
    std::cout << "Is 'new_bitset' and 'bitset_part_d' equal? " << (new_bitset == bitset_part_d) << std::endl;
    std::cout << "Is 'new_bitset' and 'bitset_part_d' unequal? " << (new_bitset != bitset_part_d) << std::endl; 
    std::cout << std::endl;
    return 0;
}


//NOTE TO SELF: to manipulate and access individual bits in the std::bitset, use the following member functions
//              set(),  reset(),  flip(),  test()
//!!!!! -> same member functions as in Boost libraries with std::dynamic_bitset.

// SEE CPPREFERENCE FOR MORE GOOD INFO!