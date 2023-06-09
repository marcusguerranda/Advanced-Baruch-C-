//2.2.2: Array categories

//Purpose: Functions that works with array types.
//         -> The rank of an array type is equa to the number of dimensions of the array.
//         -> The extent of an array type is the number of elements along the Nth dmension of the array if N is the closed interval [0, std::rank<T>::value].
//            For any other type, the value is 0.

#include <iostream>
#include <vector>
#include <array>
#include <type_traits>


enum enum_comp1
{
    COMPOUND,
    ARITHMETIC,
    FUNDAMENTAL
};

class class_comp2
{
public: 
    int x;
};



int main()
{

//PART A: Test std::is_array() on a range of fundamental, scalar, object, arithmetic, and compound types
//        std::array checks if a type is an array type

//Note: arithmetic type traits are a subset of the fundamental type traits, and are specifically concerned with identifying properties of the 
//      arithmetic types.
//      Fundamental type = arithmetic + void + null_ptr

//FUNDAMENTAL:

    std::cout << std::boolalpha;    //Converting binary 0 or 1 when calling type trait functions with ::value at the end to 'true' or 'false'
    //FUNDAMENTAL:
    std::cout << "\n \tFUNDAMENTAL\n";
    std::cout << "VOID is an array type: " << std::is_array<void>::value << ". Is void: " << std::is_void<void>::value << std::endl;
    std::cout << "NULL_PTR is an array type: " << std::is_array<std::nullptr_t>::value << std::endl;

    //ARITHMETIC
    std::cout << "\n \tFUNDAMENTAL AND ARITHMETIC AND SCALAR\n";
    std::cout << "CHAR is an array type: " << std::is_array<char>::value << ". Is fundamental: " << std::is_fundamental<char>::value << 
    ". Is scalar: " << std::is_scalar<char>::value << ". Is arithmetic: " << std::is_arithmetic<char>::value << std::endl;

    std::cout << "\nINT is an array type: " << std::is_array<int>::value << ". Is fundamental: " << std::is_fundamental<int>::value << 
    ". Is scalar: " << std::is_scalar<int>::value << ". Is arithmetic: " << std::is_arithmetic<int>::value << std::endl;

    std::cout << "\nFLOAT is an array type: " << std::is_array<float>::value << ". Is fundamental: " << std::is_fundamental<float>::value << 
    ". Is scalar: " << std::is_scalar<float>::value << ". Is arithmetic: " << std::is_arithmetic<float>::value << std::endl;

    std::cout << "\nDOUBLE is an array type: " << std::is_array<double>::value << ". Is fundamental: " << std::is_fundamental<double>::value << 
    ". Is scalar: " << std::is_scalar<double>::value << ". Is arithmetic: " << std::is_arithmetic<double>::value << std::endl;


    //OBJECT: anything that has value and a type (fundamental + pointer + reference + array + enum + class + union types)
    //HOWEVER: an object type that is not a compound type would be a fundamental type in C++
    //Conclusion: I will include compound types directly, which will comprise of object types

    //Compound types: array, function, object pointer, function pointer, member object pointer, member function pointer, reference, class, union
    //                enumeration.
    std::cout << "\n \tOBJECT";

    enum_comp1 example1{COMPOUND};
    std::cout << "ENUMERATION 'enum_comp1' is an array type: " << std::is_array<enum_comp1>::value << ". Is a compound type: " << std::is_compound<enum_comp1>::value << ". Is an object type: " 
    << std::is_object<enum_comp1>::value << std::endl;

    class_comp2 example2{3};
    std::cout << "CLASS 'class_comp2' is an array type: " << std::is_array<class_comp2>::value << ". Is a compound type: " << std::is_compound<class_comp2>::value << ". Is an object type: " 
    << std::is_object<class_comp2>::value << std::endl;

    std::cout << "ARRAY is an array type: " << std::is_array<std::array<int,1>>::value << ". Is a compound type: " << std::is_compound<std::array<int,1>>::value << ". Is an object type: "
    << std::is_object<std::array<int,1>>::value << std::endl;
    

//PART B: Create an array int[][3][4][5]. Find its rank and extent
    std::cout << "\n PART B: Create an array int[][3][4][5]. Find its rank and extent." << std::endl;
    std::cout << "Rank of this defined array would be: " << std::rank<int[][3][4][5]>::value << std::endl;
    std::cout << "Extent of this defined array would be; " << std::extent<int[][3][4][5]>::value << std::endl;

//PART C: Call std::remove_extent() and std::remove_all_extents() on the array in question b). What is happening?



    std::cout << "\n PART C: Call std::remove_extent() and std::remove_all_extent() on the array in question b). What is happening?." << std::endl;
    

    //                      TEST
    int save[10][3][4][5];
    std::cout << "Rank: " << std::rank<decltype(save)>::value << std::endl;
    using new_type = std::remove_extent<decltype(save)>::type;
    new_type new_save;
    std::cout << "Rank: " << std::rank<new_type>::value << std::endl;


    std::cout << "Calling std::remove_extent on the array will give a rank of: " << std::rank<std::remove_extent<int[][3][4][5]>>::value << std::endl;
    std::cout << "Calling std::remove_extent on the array will give an extent of: " << std::extent<std::remove_extent<int[][3][4][5]>>::value << std::endl;

    std::cout << "Calling std::remove_all_extent on the array will give a rank of: " << std::rank<std::remove_all_extents<int[][3][4][5]>>::value << std::endl;
    std::cout << "Calling std::remove_all_extent on the array will give an extent of: " << std::extent<std::remove_all_extents<int[][3][4][5]>>::value << std::endl;


/*
Comment: From the get go, the rank of this particular array was of 4 and of extent 0. 

When calling std::remove_extent and std::remove_all_extents, the resulting type is 'int', which is not an array type and therefore has rank 0 and extent 0.

*/

    return 0;
}