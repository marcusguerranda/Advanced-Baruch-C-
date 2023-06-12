//2.2.3: Conversions

//PART A: Write a separate function for each of the above requirements.
//PART B: Test the functions on a range of fundamental, scalar, object, arithmetic and compound types.


//VERY IMPORTANT NOTE FOR SELF: using 'typename', such as with 'typename std::add_pointer<T>::type' and 'typename std::remove_pointer<T>::type' expressions. 
//                              Use std::add_pointer_t<T> INSTEAD!!! There is technically no difference between these in terms of functionality,
//                              but the latter is more succint and easier to understand




#include <iostream>
#include <limits>       //For std::numeric_limits functionalities
#include <stdexcept>    //For exception throwing
#include <type_traits>
#include <vector>
#include <string>

/////////////////////////////////////////
//UNSIGNED / SIGNED
template<typename T>
constexpr std::make_unsigned_t<T> Toggle_SignedUnsigned_impl(T& t, std::true_type)
{
    using Unsigned = typename std::make_unsigned<T>::type;
    return static_cast<Unsigned>(t);
}

template <typename T>
constexpr std::make_signed_t<T> Toggle_SignedUnsigned_impl(T& t, std::false_type)
{
    using Signed = typename std::make_signed<T>::type;
    return static_cast<Signed>(t);
}

template <typename T>
constexpr auto Toggle_SignedUnsigned(T& t)
{
    static_assert(std::numeric_limits<T>::is_integer, "You have not provided an integer type.");
    return Toggle_SignedUnsigned_impl(t, std::bool_constant<std::is_signed_v<T>>{});
}

/////////////////////////////////////////
//  CONST / NON-CONST
template <typename T>
constexpr std::add_const_t<T> Toggle_Const_impl(T& t, std::false_type)
{
    return const_cast<const T&>(t);
}

template <typename T>
constexpr std::remove_const_t<T> Toggle_Const_impl(T& t, std::true_type) 
{
    return const_cast<T&>(t);
}

template <typename T>
constexpr auto Toggle_Const(T& t)
{
    return Toggle_Const_impl(t, std::is_const<T>());
}

/////////////////////////////////////////
// POINTER / NON-POINTER
template<typename T>
constexpr std::remove_pointer_t<T> Toggle_Pointer_impl(T t, std::true_type)
{
    return *t;
}

template<typename T>
constexpr std::add_pointer_t<T> Toggle_Pointer_impl(T& t, std::false_type)
{
    return &t;
}

template<typename T>
constexpr auto Toggle_Pointer (T t)
{
    return Toggle_Pointer_impl(t, std::is_pointer<T>());
}



// VOLATILE SPECIFIER:
template<typename T>
constexpr std::remove_volatile_t<T> Toggle_Volatile_impl(T& t, std::true_type) {
    return const_cast<std::remove_volatile_t<T>&>(t);
}

template<typename T>
constexpr std::add_volatile_t<T> Toggle_Volatile_impl(T& t, std::false_type) {
    return const_cast<std::add_volatile_t<T>&>(t);
}

template<typename T>
constexpr auto Toggle_Volatile(T& t) {
    return Toggle_Volatile_impl(t, std::is_volatile<T>());
}



int main()
{
//PART A: Write a separate function for each of the above requirements.

//1.  Mapping integers to unsigned integers and vice versa.

    std::cout << std::boolalpha;
    std::cout << "\n1) Mapping integers to unsigned integers and vice versa." << std::endl;

    unsigned int a{2};
    int b{-2};
    unsigned long long c{10000};
    long long d{-10000};
    double e{2.3};


    std::cout << Toggle_SignedUnsigned(a) << std::endl; //Makes unsigned int of value signed, so would still expect value of 2

    std::cout << Toggle_SignedUnsigned(b) << std::endl; //Makes unsigned value signed, therefore taking value from -2 to 4294967294

    std::cout << Toggle_SignedUnsigned(c) << std::endl; //Make unsigned value signed, therefore not changing value of 10000

    std::cout << Toggle_SignedUnsigned(d) << std::endl; //Make igned value unsigned, therefore taking value from -10000 to 18446744073709541616

    //Toggle_SignedUnsigned(e);             //Will throw error because of static_assert


//2. Add/remove the const specifier to or from a type.

    int i = 42;
    const int ci = 100;

    std::vector<int> v{1, 2, 3};
    const std::vector<int> cv{4, 5, 6};

    std::string s = "hello";
    const std::string cs = "world";

    auto const_i = Toggle_Const(ci);    //const_i is now 'const' by deduction from compiler and using toggle function

    auto non_const_i = Toggle_Const(i); //non_const_i is now 'non-const' by deduction from compiler and using toggle function

    auto const_v = Toggle_Const(cv);    //const_v is now 'const' by deduction from compiler and using toggle function

    auto non_const_v = Toggle_Const(v); //non_const_v is now 'non-const' by deduction from compiler and using toggle function

    auto const_s = Toggle_Const(cs);    //const_s is now 'const' by deduction from compiler and using toggle function

    auto non_const_s = Toggle_Const(s); //non_const_s is now 'non-const' by deduction from compiler and using toggle function


//3. Add/remove a pointer to or from a type

    //Testing with non-pointer type
    int num = 10;
    auto toggled_num = Toggle_Pointer(num); //toggled_num will now be a pointer

    //Testing with pointer type
    int* ptr = nullptr;
    auto toggled_ptr = Toggle_Pointer(ptr); //toggled_ptr will now be a simple int


//4. Volatile/ non-volatile

    int y= 10;
    volatile int x=9;
    
    auto vol_int = Toggle_Volatile(y);      //vol_int will now be volatile
    auto nonvol_int = Toggle_Volatile(x);   //nonvol_int will now not be volatile

    return 0;
}




/*  NOTE TO SELF:

There are many interesting functionalities in the <limits> header file. Notably:

is_specialized
identifies types for which std::numeric_limits is specialized

is_signed
identifies signed types

is_integer
identifies integer types

is_exact
identifies exact types


has_infinity
identifies floating-point types that can represent the special value "positive infinity"


has_quiet_NaN
identifies floating-point types that can represent the special value "quiet not-a-number" (NaN)


has_signaling_NaN
identifies floating-point types that can represent the special value "signaling not-a-number" (NaN)


has_denorm
identifies the denormalization style used by the floating-point type


has_denorm_loss
identifies the floating-point types that detect loss of precision as denormalization loss rather than inexact result

round_style
identifies the rounding style used by the type


is_iec559
identifies the IEC 559/IEEE 754 floating-point types

is_bounded
identifies types that represent a finite set of values

is_modulo
identifies types that handle overflows with modulo arithmetic

digits
number of radix digits that can be represented without change

digits10
number of decimal digits that can be represented without change

max_digits10
number of decimal digits necessary to differentiate all values of this type

radix
the radix or integer base used by the representation of the given type

min_exponent
one more than the smallest negative power of the radix that is a valid normalized floating-point value

min_exponent10
the smallest negative power of ten that is a valid normalized floating-point value


max_exponent
one more than the largest integer power of the radix that is a valid finite floating-point value


max_exponent10
the largest integer power of 10 that is a valid finite floating-point value


traps
identifies types which can cause arithmetic operations to trap

tinyness_before
identifies floating-point types that detect tinyness before rounding


                    Member functions:

min
returns the smallest finite value of the given type


lowest
returns the lowest finite value of the given type

max
returns the largest finite value of the given type

epsilon
returns the difference between 1.0 and the next representable value of the given floating-point type

round_error
returns the maximum rounding error of the given floating-point type


infinity
returns the positive infinity value of the given floating-point type

quiet_NaN
returns a quiet NaN value of the given floating-point type


signaling_NaN
returns a signaling NaN value of the given floating-point type


denorm_min
returns the smallest positive subnormal value of the given floating-point type






*/