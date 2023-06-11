//2.2.1: A numeric application: the begining of a vector space

//Purpose: Creating a mathematical libray to model vector spaces.
//         Adding two vectors
//         Additive inverse of a vector
//         Scalar multiplicity (premultiply the vector by a scalar)
// IMPORTANT: Define the above operations for scalar and array/vector numeric types

#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>
#include <complex>
#include <algorithm>


//                                                      ADDITION OF TWO VECTORS
//Declare the bridge/implementation functions before declaring main function...
//Not of compound type (so primary type)
template<typename T>
T Addition_impl(const T& t1, const T& t2, std::false_type)
{   
    //I believe that this verification is important. Indeed, if a type trait is not of a compound type, this does not automatically mean it is of a 
    //fundamental/primary type, and therefore easily additionable.
    if(!std::is_fundamental<T>::value) {throw std::invalid_argument("You are not giving arguments that are either of both COMPOUND type or FUNDAMENTAL type.");};
    return t1 + t2;
}

//Of compound type, so 'true'
template<typename T>
T Addition_impl(const T& t1, const T& t2, std::true_type)
{
    //Make temporary compound type hold results
    T result = t1; 
    std::transform(t1.begin(), t1.end(), t2.begin(), result.begin(), [&](const auto& a, const auto& b) {return a + b;}); 
    return result;
}


//Addition of two vectors
template <typename T>
T Addition(const T& t1, const T& t2)
{   
    if (!std::is_same_v<decltype(t1), decltype(t2)>) 
    {
        throw std::invalid_argument("Addition requires two arguments of the same type.");
    }
    //std::is_compound<T>() checking whether T is a compound type (array, vector,, struct, union, class, etc.). Therefore not primary/fundamental types
    //such as int, float, char, etc.
    return Addition_impl(t1, t2, std::is_compound<T>());    //Call bridge functions
}




//                                                      ADDITIVE INVERSE

//Is compound type (vector, array, struc, etc.)
template <typename T>
void AdditiveInverse_impl(T& val, std::true_type)
{
    //Iterate over container/compound type with a defined iterator, and apply additive inverse
    for (auto iter = val.begin(); iter != val.end(); ++iter) 
    {
        *iter = -(*iter);
    }
}

//Is not compound type (could be a scalar)
template <typename T>
void AdditiveInverse_impl(T& val, std::false_type)
{
    //I believe that this verification is important. Indeed, if a type trait is not of a compound type, this does not automatically mean it is of a 
    //fundamental/primary type, and therefore easily additionable.
    if(!std::is_fundamental<T>::value) {throw std::invalid_argument("You are not giving arguments that are either of both COMPOUND type or FUNDAMENTAL type.");};
    val = -val;
}


//Additive inverse of a vector
template <typename T>
void AdditiveInverse(T& val)
{   //Condition is that I perform the following for either a scalar or a compound type similar to that of a vector
    //I take the same approach and call bridge functions, as a function of whether it is std::true_type or std:false_type
    AdditiveInverse_impl(val, std::is_compound<T>());
}


//                                                          SCALAR MULTIPLICATION

//Bridge function 1: If T1 template is a compound type, and T2 typename is a scalar
//Return type is specified using 'typename' and 'std::enable_if', and is then deduced by the compiler based on T1 and T2
template <typename T1, typename T2>
typename std::enable_if<std::is_compound<T1>::value && std::is_fundamental<T2>::value, T1>::type
Multiplication_impl(const T1& t1, const T2& t2)
{
    T1 result = t1;
    for (auto& elem : result)
    {
        elem *= t2;
    }
    return result;
}

//Bridge function 2: If T1 template is a scalar, and second typename T2 is a compound type
//Return type is specified using 'typename' and 'std::enable_if', and is then deduced by the compiler based on T1 and T2
template <typename T1, typename T2>
typename std::enable_if<std::is_fundamental<T1>::value && std::is_compound<T2>::value, T2>::type
Multiplication_impl(const T1& t1, const T2& t2)
{
    T2 result = t2;             //Make temporary compound type holding results
    for (auto& elem : result)
    {
        elem *= t1;
    }
    return result;
}

//Function for handling all other cases
template <typename T1, typename T2>
typename std::enable_if< !std::is_compound<T1>::value || !std::is_fundamental<T2>::value, void>::type
 Multiplication_impl(const T1& t1, const T2& t2)
{
    //Throw an invalid argument error
    throw std::invalid_argument("Inputs not appropriate for this function use.");
}


//Multiplication() function taking a scalar and a compound type. If (T1=scalar, and T2=compound) == good. (T1=compound and T2=compound) == good.
//I don't want a situation where I have two compound types, or two scalars. This would defeat the purpose of this function
template<typename T1, typename T2>
auto Multiplication(const T1& t1, const T2& t2)
{
    return Multiplication_impl(t1, t2);
}



template <typename T>
void Print_Container(const T& container)
{
    std::cout << "[";
    for(const auto& element : container)
    {
        std::cout << element << " ";
    }
    std::cout << "]";
}



int main()
{

//PART A: Define addition of two vectors in Addition() function
//PART B: Define additive inverse of a vector in AdditiveInverse() function
//PART C: Define a function for scalar multiplication of a scalar and a vector, producing a new vector. Determine 
//        the signature of this function.

    double a = 3.3;                                     //                      --> PRIMARY TYPE
    double b(a);                                        //                      --> PRIMARY TYPE
    std::vector<double> v1{1.2, 2.2, 3.3, 4.4, 5.5};    //5 elements in vector  --> COMPOUND TYPE
    std::vector<double> v2(v1);                         //Copy constructor      --> COMPOUND TYPE
    std::array<double, 5> array1 = {11.1, 22.2, 33.3, 44.4, 55.5};   //Of type std::array<double, N>
    std::array<double, 5> array2(array1);                       

//  ADDITION()

    std::cout << "\nPART A" << std::endl;
    std::cout << "Addition of two doubles a and b = " << Addition(a,b) << std::endl;
    std::cout << "\nAddition of two vectors<double> v1 and v2 = " << std::endl;
    Print_Container(Addition(v1,v2));
    
    std::cout << "\nAddition of std::array<double, N>s array1 and array2 = " << std::endl;
    Print_Container(Addition(array1, array2));

    //std::cout << "Addition of one integer and one vector will throw:" << Addition(a,v1) << std::endl; //WILL THROW COMPILER ERROR


//  ADDITIVEINVERSE()

    std::cout << "\n\nPART B" << std::endl;
    std::cout << "Additive inverse of a = " << a << " is "; AdditiveInverse(a); std::cout << a << std::endl; 
    
    AdditiveInverse(v1);
    std::cout << "\nAdditive inverse of vector v1  will be: "; Print_Container(v1); 
    
    AdditiveInverse(array1);
    std::cout << "\nAdditive inverse of array1 will be: "; Print_Container(array1);


//  MULTIPLICATION()

    //-> Will throw error because the exercise explicitly asks for a multiplication of a container such a vector with a scalar. 
    //   I therefore eliminated the case where multiplying two fundamental types together.

    //std::cout << "Multiplication of a double a = " << a << " by scalar b is equal to: " << std::endl;
    //Multiplication(a,b);

    std::cout << "\nMultiplication of v1 by a is: "; Print_Container(Multiplication(v1,a)); 

    std::cout << "\nMultiplication of array1 by a is: "; Print_Container(Multiplication(array1,a));


//PART E: Test these functions (AdditiveInverse(), Multiplication(), and Addition()) with containers whose underlying type is std::complex<double>

    std::cout << "\n\nPART E: COMPLEX NUMBERS ON CONTAINERS (could be vector or array)" << std::endl;

    std::complex<double> complex1(1, 1);  //Complex number 1
    std::complex<double> complex2(2, 2);  //Complex number 2
    std::complex<double> complex3(3, 3);  //Complex number 3
    std::complex<double> complex4(4, 4);  //Complex number 4

    std::array<std::complex<double>,2> comp_arr1{complex1, complex2};
    std::array<std::complex<double>,2> comp_arr2{complex3, complex4};


    //NOTE TO AVI: Exercises asks to use functions on the containers of our choice, not on the complex numbers themselves, or not multiple containers

//ADDITION()

    std::cout << "Addition of complex numbers complex1 and complex2 will give: "; Print_Container(Addition(comp_arr1, comp_arr2));

//ADDITIVEINVERSE()

    AdditiveInverse(comp_arr1);
    std::cout << "Additive inverse of an array of complex numbers comp_arr1 will be:  "; Print_Container(comp_arr1);

//MULTIPLICATION()

    //Of the form:              Print_Container(Multiplication(compound_type, scalar))
    std::cout << "Multiplication of comp_arr1 by a scalar a will give: "; Print_Container(Multiplication(comp_arr1,a));
    
    return 0;
}