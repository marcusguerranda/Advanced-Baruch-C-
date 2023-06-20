//2.8) STL Bitset: 3.Boost dynamic bitset 101

//Purpose: using boost dynamic bitset

//Author: Andrew Guerrand

//Modification dates: 5/29/2023

/*
    PART B) (Changing the size of a bitset at run-time). Apply resize(), clear(), push_back(), pop_back()
    and append() to bitset instances.
    PART C) (Set operations). Test the functionality to test if a bitset is a subset (or proper subset) of another bitset.
    PART) (Searching in bitsets). Use find_first() and find_next() to search for bits in bitsets.
*/

#include <iostream>
#include <boost/dynamic_bitset.hpp>

int main() {
    std::cout << "PART B: Changing the size of a bitset at run-time." << std::endl;

    // Changing the size of the bitset
    boost::dynamic_bitset<> bitset_b(3, 2ul); // 3 bits for 2 unsigned long: 010
    std::cout << "Original bitset: " << bitset_b << std::endl;

    bitset_b.resize(4); // Resizing to 4 bits: 0010
    std::cout << "After resizing: " << bitset_b << std::endl;

    bitset_b.push_back(0); // Pushing a 0 to the most significant bit (left side): 00010 (5 bits)
    std::cout << "After push_back(0): " << bitset_b << std::endl;

    bitset_b.pop_back(); // Removing the most significant bit (left side): 0010 (4 bits)
    std::cout << "After pop_back(): " << bitset_b << std::endl;

    bitset_b.append(0); // Appending a block of zeros at the most significant bit: 00010
    std::cout << "After append(0): " << bitset_b << std::endl;

    bitset_b.clear(); // Clearing the bitset
    std::cout << "After clear(): " << bitset_b << std::endl;

    std::cout << "\nPART C: Set operations." << std::endl;

    boost::dynamic_bitset<> bitset_c8(4, 8ul); // 4 bits for 8 unsigned long: 1000
    boost::dynamic_bitset<> bitset_c3(4, 3ul); // 4 bits for 3 unsigned long: 0011
    boost::dynamic_bitset<> bitset_c7(4, 7ul); // 4 bits for 7 unsigned long: 0111

    std::cout << "Bitset8: " << bitset_c8 << std::endl;
    std::cout << "Bitset3: " << bitset_c3 << std::endl;
    std::cout << "Bitset7: " << bitset_c7 << std::endl;

    // Subset check
    if (bitset_c8.is_subset_of(bitset_c7)) {
        std::cout << "Bitset8 is a subset of Bitset7." << std::endl;
    } else {
        std::cout << "Bitset8 is not a subset of Bitset7." << std::endl;
    }

    if (bitset_c3.is_subset_of(bitset_c7)) {
        std::cout << "Bitset3 is a subset of Bitset7." << std::endl;
    } else {
        std::cout << "Bitset3 is not a subset of Bitset7." << std::endl;
    }

    std::cout << "\nPART D: Searching in bitsets." << std::endl;

    boost::dynamic_bitset<> bitset_d7(4, 7ul); // 4 bits for 7 unsigned long: 0111
    std::cout << "Bitset for searching: " << bitset_d7 << std::endl;

    std::size_t first_index = bitset_d7.find_first();
    std::cout << "First occurrence of 1 is at index: " << first_index << std::endl;

    std::size_t next_index = bitset_d7.find_next(2);
    std::cout << "Next occurrence of 1 after index " << 2 << " is at index: " << next_index << std::endl;
    std::cout << std::endl;
    return 0;
}