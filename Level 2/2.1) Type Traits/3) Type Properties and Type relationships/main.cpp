//2.1.3: Type Properties and Type Relationships

//Purpose: Type properties and type relationships using <type_traits> library and relevant functionalities

//Author: Andrew Guerrand

//Modification dates: 5/10/2023

#include <iostream>
#include <type_traits>  //Defines a series of clases to obtain type information on compile-time
#include <typeinfo>    //Defines types sed related to operators typeid and dynamic_cast

class Shape
{
public:
    virtual void draw() = 0;
};


class Base
{
private:
    int y;
public:
    Base() {}
    void draw() {}
};

class Point: public Shape
{
public:
    Point() {}
    virtual void draw() override {}
};


//Having some class that evaluates the different type relationships of interest to us:
template<typename T>
void ClassEvaluator (const T& source)
{
    std::cout << std::boolalpha;    //true/false for binary answers when summoning functions of types std::...<T>::value from <type_traits>
    std::cout << "\nType at hand is: " << typeid(source).name() << std::endl;
    std::cout << "Is empty? : " << std::is_empty<T>::value << std::endl;
    std::cout << "Is polymorphic? " << std::is_polymorphic<T>::value << std::endl;
    std::cout << "Is abstract? "    << std::is_abstract<T>::value << std::endl;
    std::cout << "\n";
}



int main()
{
/*
    a) Which classes/types are empty, polymorphic or abstract?
    b) Which classes are the same?
    c) Which classes have a gen/spec (base/derived) relationship?
    d) Which types can be converted to each other?
*/


//PART A: Which classes/types are empty, polymorphic or abstract?

    Shape* shape_ptr;
    Base b1;
    Point p1;

    ClassEvaluator(shape_ptr);
    ClassEvaluator(b1);
    ClassEvaluator(p1);

    //IMPORTANT: when calling ClassEvaluator(shape_ptr);, one can notice that we get 'false' in regard to the abstract nature of the class.
    //In effect, we are using a pointer declaration of type 'Shape', given that I can't create an instance of an abstract class.
    //In order to check whether the type pointed to by the 'shape_ptr' is an abstract class, I need to use std::is_abstract as seen below (2 possibilities):

    
    std::cout << "Checking whether Shape is abstract, with proper calling of std::is_abstract function." << std::endl;
    std::cout << std::is_abstract<Shape>::value << std::endl;;    //More straightforward implementation
    std::cout << std::is_abstract<std::remove_pointer_t<decltype(shape_ptr)>>::value << std::endl;;


//PART B: Which classes are the same?

    std::cout << "Is Point the same as Base? : " << std::is_same<Point, Base>::value << std::endl;
    std::cout << " Is Base the same as Shape? : " << std::is_same<Base, Shape>::value << std::endl;
    std::cout << "Is Point the same as Shape? : " << std::is_same<Point, Shape>::value << std::endl;
    std::cout << "Is Point the same as Point? : " << std::is_same<Point, Point>::value << std::endl;
    std::cout << "Is Base the same as Base? : " << std::is_same<Base, Base>::value << std::endl; 

//Part C: Which classes have a gen/spec (base/derived relationship)?

    //Note: I could be using    std::is_class<...>::value to check whether my input of interest is class to start with.
    //I will mostly be using functionalities that can be found in <type_traits>: is_polymorphic, is_final, is_abstract.
    std::cout << "Is Shape an abstract class? : " << std::is_abstract<Shape>::value << std::endl;
    std::cout << "Is Point an empty class? : " << std::is_empty<Point>::value << std::endl;

    std::cout << "Is Point class polymorphic? : " << std::is_polymorphic<Point>::value << std::endl;
    std::cout << "Is Base class polymorphic? : " << std::is_polymorphic<Base>::value << std::endl;

    //If I do write class Point() final{};, then the answer is 'true' 
    std::cout << "Is Point a final class? : " << std::is_final<Point>::value << std::endl; 

//Part D:

/*Mainly using: std::is_convertible and std::is_nothrow_convertible
-> Both determine if one type can be implicitly converted to another type, but they have different behavior in case
   the conversion can potentially throw an exception.

   std::is_convertible<T, U> evaluates to 'true' if a value of type 'T' can be implicitly converted to type 'U' using a single 
   conversion step, and 'false' otherwise. All of this is determined at compile-time by the compiler.

   std::is_nothrow_convertible<T, U> evaluates to 'true' if a value of type 'T' can be implicitly converted to type 'U' using a single conversion
   step without throwing any exceptions exceptions.*/

    std::cout << "Is Shape convertible to a Point class? : " << std::is_convertible<Shape, Point>::value << std::endl;
    std::cout << "Is Point convertible to a Base class? : " << std::is_convertible<Point, Base>::value << std::endl;
    std::cout << "Is Base convertible to a Point class? : " << std::is_convertible<Base, Point>::value << std::endl;

    std::cout << "Is Shape convertible to a Point class? : " << std::is_nothrow_convertible<Shape, Point>::value << std::endl;
    std::cout << "Is Point convertible to a Base class? : " << std::is_nothrow_convertible<Point, Base>::value << std::endl;

    //Since all of the above return 'false', I want to try other calls to see when it prints 'true'
    std::cout << "Double convertible to an int? : " << std::is_convertible<double,int>::value << std::endl;
    std::cout << "Int convertible to a double? : " << std::is_convertible<int, double>::value << std::endl;

    std::cout << "Double convertible to an int? (nothrow) : " << std::is_nothrow_convertible<double,int>::value << std::endl;
    std::cout << "Int convertible to a double? (nothrow) : " << std::is_nothrow_convertible<int, double>::value << std::endl;

    return 0;
}