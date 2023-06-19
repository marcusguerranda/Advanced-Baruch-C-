//2.8) STL BITSET AND BOOST DYNAMIC BITSET: 2. Boolean operations on bitsets

//Purpose:  perform bitwise binary and unary operations on bitsets. In the former case we can choose 
//          to modify the left-hand operand or we can create a new bitset from the left and right-hand operands. 

//Author: Andrew Guerrand

//Modification dates: 5/29/2023

#include <iostream>
#include <bitset>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>


int main()
{
//PART A: create two bitsets bs1 and bs2 with the same number of bits, and the same size.

    std::cout << "\nPART A: create two bitsets bs1 and bs2." << std::endl;
    std::bitset<8> bs1;         //Default bitset will be 00000000
    bs1.flip(2);                //Flip the third element

    std::bitset<8> bs2(bs1);    //Copy constructor

    std::cout << "bs1 and bs2 are equal to the following: " << bs1 << ", and " << bs2 << std::endl;
    
//PART B: Toggle the bits in both bitsets

    std::cout << "\nPART B: Toggle bits in both bitsets. " << std::endl;
    bs1.flip(); bs2.flip();
    std::cout << "bs1 and bs2 are equal to the following: " << bs1 << ", and " << bs2 << std::endl;

//PART C: Perform bitwise XOR, OR, and AND operations on bs1 and bs2

    std::cout << "\nPART C: Bitwise XOR, OR, and AND operations." << std::endl;
    std::bitset<8> result_xor = bs1 ^ bs2;  //00000000 given all bits in bs1 and bs2 are the same, and thus '0' when bits are same, '1' when different
    std::bitset<8> result_or = bs1 | bs2;   //11111011 ->  returns 1 if at least one of the corresponding bits in the operands is 1, and 0 if both bits are 0.
    std::bitset<8> result_and = bs1 & bs2;  //11111011 -> with 'AND' &, returns 1 if both corresponding bits in the operands are 1, and 0 otherwise.

    std::cout << "Bitwise XOR: " << result_xor << std::endl;
    std::cout << "Bitwise OR: " << result_or << std::endl;
    std::cout << "Bitwise AND: " << result_and << std::endl;


//PART D: Perform right and left shift operations on bs1 and bs2
    std::cout << "\nPART D: Right and Left shift operations." << std::endl;
    std::bitset<8> result_right_shift = bs1 >> 3;  // Right shift bs1 by 2 positions
    std::bitset<8> result_left_shift = bs2 << 3;   // Left shift bs2 by 3 positions

    std::cout << "Right Shift: " << result_right_shift << std::endl;
    std::cout << "Left Shift: " << result_left_shift << std::endl;

//PART E: Use std::hash to created hashed values of bs1 and bs2

    std::cout << "\nPART E: Use std::hash to created hashed values of bs1 and bs2" << std::endl;
    std::hash<std::bitset<bs1.size()>> bitset_hash;  //Define a hash object for std::bitset<bs1.size()>
    std::size_t bs1_hash = bitset_hash(bs1);
    std::size_t bs2_hash = bitset_hash(bs2);

    std::cout << "Hash value of bs1: " << bs1_hash << std::endl;    //No surprise that these two are the same, given bs1 and bs2 are the same
    std::cout << "Hash value of bs2: " << bs2_hash << std::endl;

//PART F: investigate how to create binary literals in C++ (C++14) and their relationship with bitsets.
//        NOTE FOR SELF: check below for what binary literals are

    std::cout << "\nPART F: creating binary literals in C++" << std::endl;
    auto blit = 0b0011;
    std::byte b{ 0b0011 };                                      //Create from a binary literal
    std::bitset<4> bs(blit);
    boost::dynamic_bitset<unsigned int> dbs(4);                 //All 0 by default
    dbs[1] = dbs[0] = 1;
    std::cout << "Byte: " << std::to_integer<int>(b) << '\n'; //Int 3
    std::cout << "Bitset: " << bs << '\n';                      //Bitset of 3: 0011
    std::cout << "Dynamic bitset: " << dbs << '\n';             //Bitset of 3: 0011

//PART G and H: Create a byte in different ways: from a binary literal, 
//                                         from an integer, 
//        as binary logical operators on existing bytes

    std::cout << "\nPART G and H: create a byte in different ways: from an integer, and from a binary literal" << std::endl;
    //Create a byte from a binary literal
    std::byte byte1{0b0011};

    //Create a byte from an integer
    std::byte byte2{222};

    //Perform binary logical operators on existing bytes
    std::byte byte3 = byte1 & byte2;
    std::byte byte4 = byte1 | byte2;
    std::byte byte5 = byte1 ^ byte2;

    //Print the byte values
    std::cout << "Byte 1 (Binary literal): " << std::to_integer<int>(byte1) << std::endl;
    std::cout << "Byte 2 (From integer): " << std::to_integer<int>(byte2) << std::endl;
    std::cout << "Byte 3 (Bitwise AND &): " << std::to_integer<int>(byte3) << std::endl;
    std::cout << "Byte 4 (Bitwise OR |): " << std::to_integer<int>(byte4) << std::endl;
    std::cout << "Byte 5 (Bitwise XOR ^): " << std::to_integer<int>(byte5) << std::endl;

//PART I: Perform left and right shift operations on bytes. 

    // Perform left and right shift operations on bytes
    auto byte6 = byte1 << 2;  // Left shift by 2 positions
    auto byte7 = byte2 >> 4;  // Right shift by 4 positions

    std::cout << "Byte 6 (Left shift): " << std::to_integer<int>(byte6) << '\n';
    std::cout << "Byte 7 (Right shift): " << std::to_integer<int>(byte7) << '\n';
   
/*PART J: Can you think of examples/applications where bytes and bitsets can be used, for example raw memory access 
/         and savings and performance improvements?
   

    Cryptography: -> Bytes used to represent keys, messages, and encrypted data.  Bitwise operations, such as XOR and bitwise shifts, are used to manipulate and transform data during encryption and decryption processes.
    Image Processing/Analysis -> Images can be represented as collections of bytes, and bitwise operations can be performed to manipulate or analyze the image data. For example, bitsets can be used to represent binary masks or perform pixel-level operations efficiently.
*/
    return 0;
}


/*  NOTE FOR SELF:

    XOR ^ ;  ->  returns 1 if the corresponding bits in the operands are different, and 0 if they are the same.
    OR |     ->  returns 1 if at least one of the corresponding bits in the operands is 1, and 0 if both bits are 0.
    AND &    ->  returns 1 if both corresponding bits in the operands are 1, and 0 otherwise.


    LEFT Shift (<<): This operation shifts the bits of a value to the left by a specified number of positions. 
                     Each bit is shifted to the left, and new bits are filled in from the right side with zeros. Left shifting a 
                     value by n positions is equivalent to multiplying the value by 2^n. This operation effectively increases the value by a power of 2.

    RIGHT Shift (>>): This operation shifts the bits of a value to the right by a specified number of positions. 
                      Each bit is shifted to the right, and the new bits that come in from the left side depend on the type of right shift performed. 
                      There are two types of right shifts: logical right shift and arithmetic right shift.

    Logical Right Shift (>>>): This type of right shift fills in the new bits from the left side with zeros. It effectively divides the value by 2^n.
    Arithmetic Right Shift (>>): This type of right shift fills in the new bits from the left side with the sign bit (the leftmost bit). 
    It preserves the sign of the value and is commonly used for signed integers. In C++, the behavior of right shift for signed integers 
    depends on the implementation.


    BINARY LITERALS:
    -> Binary literals are a feature in programming languages that allow you to represent numeric values directly in binary (base-2) format. 
       They provide a convenient way to express binary values without the need for manual conversion from decimal or other number systems.

    -> In languages that support binary literals, you can typically prefix the binary value with a specific notation to indicate that it 
       should be interpreted as binary. For example:

    -> In C++14 and later versions, you can use the prefix 0b or 0B followed by a sequence of 0s and 1s. For example: 0b101010 represents 
       the binary value 101010.

*/