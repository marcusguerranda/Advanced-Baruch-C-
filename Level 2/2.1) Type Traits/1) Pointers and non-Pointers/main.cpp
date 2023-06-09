//2.1) Type Traits, 1) Pointers and non-Pointers

//Purpose: this execise consists of calling some functions from Primary type categories

//Author: Andrew Guerrand

//Modication dates: 5/4/2023

//a. Write a function to determine if a type is a pointer, null-pointer, lvalue reference, or rvalue reference
//b. Determine if a type is a member function pointer or if it is a pointer to a non-static member object
//c. Is a shared pointer a pointer type? Is it a pointer type when converted to a raw pointer?

// SEE BELOW FOR EXTENSIVE NOTES

#include <iostream>
#include <type_traits>      //Type traits library to use different functions such as: std::is_member_object_pointer, etc.
#include <array>
#include <memory>           //For pointers


//Part A. Write a function to determine if a type is a pointer, null pointer, lvalue refeence, or rvalue reference
//'if constexpr' is used instead of 'if' to make sure that the non-matching branches are discarded at compile-time.
template <typename T>
void DetermineType (const T& t)
{
    //if type trait of argument 't' passed is a pointer
    if constexpr(std::is_pointer<T>::value)
    {
        std::cout << "Of type POINTER." << std::endl;
    }
    //if type trait of argument 't' passed is a null_ptr
    else if constexpr(std::is_null_pointer<T>::value)
    {
        std::cout << "Of type NULL POINTER." << std::endl;
    }
    //if type trait of argument 't' passed is an lvalue reference
    else if constexpr(std::is_lvalue_reference<T>::value)
    {
        std::cout << "Of type LVALUE REFERENCE." << std::endl; 
    }
    //if type trait of argument 't' passed is an rvalue reference
    else if constexpr(std::is_rvalue_reference<T>::value)
    {
        std::cout << "Of type RVALUE REFERENCE." << std::endl;
    }
    else
    {
        std::cout << "Type is not pointer, null pointer, lvalue nor rvalue reference..." << std::endl;
    }
};


//Part B: Determine if a type is a member function pointer, or if it is a pointer to a non-static member object

//within class, define a member function, and a member object, such that we can then have pointers pointing to either 
class RandomClass
{
public:
    //Member object in RandomClass class
    double m_object;
    //Member function in RandomClass class
    void print(){std::cout << "I'm using member function here..." <<std::endl;};
};


//Determine if a type is a member function pointer, or if it is a pointer to a non-static member object
//See https://en.cppreference.com/w/cpp/header/type_traits for documentation
template<typename T>
void DeterminePointer(const T& t)
{
    if constexpr (std::is_member_function_pointer<T>::value)
    {
        std::cout << "Type is a member function pointer" << std::endl;
    }
    else if constexpr (std::is_member_object_pointer<T>::value)
    {
        std::cout << "Type is a non-static member object pointer" << std::endl;
    }
    else {std::cout << "Type is neiher a member function pointer, nor a non-static member object pointer." << std::endl;}
};


//Part C: Determining whether a shared pointer is of a pointer type? Is it a pointer type when converted to a raw pointer?
//GIVEN CODE
//See documentation for std::is_pointer: https://en.cppreference.com/w/cpp/types/is_pointer
//std::is_pointer checks whether T is a pointer to object or function (IMPORTANT: including pointer to void, but exclusing pointer to member)
template <typename T>
void IsPointer (const T& t)
{
    // Return type is std::true_type or std::false_type, and thus need to retrieve boolean from struct with ::value. See documentation if unclear
    if(std::is_pointer<T>::value)
    {
        std::cout << "This is a pointer type argument\n" << std::endl;
    }
    else {std::cout << "_not_ a pointer type argument\n" << std::endl;}
};



int main()
{
//PART A:

    int a = 11;                     
    int* b;           
    std::array<int,4> c {1,1,1,1};                 

    DetermineType<int&>(a);                         //Option 1:Lvalue reference
    DetermineType(b);                               //Pointer
    DetermineType<decltype(std::move(a))>(a);       //Option 1: Rvalue reference
    DetermineType<int&&>(a);                        //Option 2: Rvalue reference
    DetermineType(nullptr);                         //Null pointer case
    DetermineType(c);;                              //An array (which is primary type, but not defined within DetermineType() function)

//Part B:

    //Member function pointer 
    void (RandomClass::*pMemberFunc)() = &RandomClass::print;

    //Creating a pointer to a non-static member object
    RandomClass myObject; 
    double RandomClass::*obj_ptr = &RandomClass::m_object; 
    myObject.*obj_ptr = 3.14;


    DeterminePointer(pMemberFunc);
    DeterminePointer(obj_ptr);

//Part C:

    //Create shared pointer
    std::shared_ptr<int> sp(new int(42));
    //Convert shared pointer to raw pointer
    int* ptr = sp.get();

    //Checking if shared pointer is of 'pointer' type, as well as when converted to a raw pointer.
    IsPointer(sp);  //A:   _not_ a pointer type argument
    IsPointer(ptr); //A:    This is a pointer type argument   -> when converted to raw pointer

    /*
    WHY? 
    It seems like std::shared_ptr is not a pointer type in the strict sense. It is not a raw pointer, but rather a smart pointer that
    encapsulates a raw pointer. This nuance explains the above result.
    */
    return 0;
}


/*                                                  NOTE TO SELF:

PRIMARY TYPE CATEGORIES:
-void                                   template <class T> struct is_void;
-int                                    template <class T> struct is_integral;
-float                                  template <class T> struct is_floating_point;
-array                                  template <class T> struct is_array;
-pointer                                template <class T> struct is_pointer;
-lvalue reference                       template <class T> struct is_lvalue_reference;
-rvalue reference                       template <class T> struct is_rvalue_reference;
-member object pointer                  template <class T> struct is_member_object_pointer;
-member function pointer                template <class T> struct is_member_function_pointer;
-enum                                   template <class T> struct is_enum;
-union                                  template <class T> struct is_union;
-class                                  template <class T> struct is_class;
-function                               template <class T> struct is_function;

COMPOSITE TYPE CATEGORIES:
-reference                              template <class T> struct is_reference;
-arithmetic                             template <class T> struct is_arithmetic;
-fundamental                            template <class T> struct is_fundamental;
-object                                 template <class T> struct is_object;
-scalar                                 template <class T> struct is_scalar;
-compound                               template <class T> struct is_compound;
-member pointer                         template <class T> struct is_member_pointer;

What differentiates primary types to composite types?
A -> Primary types (int, double, float, etc.) are built into the language and don't require any additional headers or libraries to be used.
     Composite type categores refer to types that are composed of one or more primary types, such as arrays, pointers, references, classes, and function types.

*/







/*      In <type_traits> header file, for Primary type categories:
Primary type categories:

is_void
checks if a type is void

is_null_pointer
checks if a type is std::nullptr_t

is_integral
checks if a type is an integral type

is_floating_point
checks if a type is a floating-point type

is_array
checks if a type is an array type

is_enum
checks if a type is an enumeration type

is_union
checks if a type is a union type

is_class
checks if a type is a non-union class type

is_function
checks if a type is a function type

is_pointer
checks if a type is a pointer type

is_lvalue_reference
checks if a type is an lvalue reference

is_rvalue_reference
checks if a type is an rvalue reference

is_member_object_pointer
checks if a type is a pointer to a non-static member object

is_member_function_pointer
checks if a type is a pointer to a non-static member function




*/