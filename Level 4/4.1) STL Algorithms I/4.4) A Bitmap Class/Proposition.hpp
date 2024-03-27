//Proposition.hpp

#ifndef Proposition_hpp
#define Propositon_hpp

#include <iostream>
#include <bitset>

/*
    c) Check that your code satisfies De Morgan’s Laws:
        - NOT (A OR B) == NOT(A) AND NOT(B)
        - NOT (A AND B) == NOT(A) OR NOT(B).

    d) Check that your code satisfies the Distributive Laws:
        - A AND(B OR C) == (A AND B) OR (A OR C)
        - A OR(B AND C) == (A OR B) AND (A OR C).

    e) Let A, B and C be propositions. Check that the statement form:
        - [A -> (B -> C)] <-> [(A & B) -> C] Is a tautology (that is, it always returns true for all assignments of truth values to its statement letters A,B 
    and C). There are EIGHT options to be checked.

*/

//IMPORTANT: since std::bitset<1> data is of size 1, I will simply not use indices but rather refer to data itself.
//           Had the bitset had more bits, I would have used indices instead.


//A class representing true/false
class Proposition
{
private:
    std::bitset<1> data;    //Bitset of size, representing only a single bit of data

public:

    //a) Create the following constructors: default, bool as argument and a std::bitset<1> as argument.

    //Default constructor
    Proposition();

    //Overloaded constructor taking bool as argument
    Proposition(const bool& bool_arg);

    //Overloaded constructore using std::bitset<1> as argument
    Proposition(std::bitset<1> arg); 

    //b) Implement the below Boolean operators as members with the exception of CONDITIONAL and 
    //BICONDITION which should be NON-MEMBER friends. TEST each operator separately.
    
//BOOLEAN OPERATORS

    //Equality operator (A == B) -> 
    //true if the value of each bit in *this equals the value of the corresponding bit in rhs, otherwise false
    bool operator == (const Proposition& other) const;

    //Inequality operator (A != B)
    bool operator != (const Proposition& other) const;

    //Conjunction operator (AND) (A & B)
    //Sets the bits to the result of binary AND on corresponding pairs of bits of *this and other.
    Proposition operator & (const Proposition& other) const;

    //Disjunction operator (OR) (A | B)
    //Sets the bits to the result of binary OR on corresponding pairs of bits of *this and other.
    Proposition operator | (const Proposition& other) const;

    //Exclusive OR operator (XOR) (A ^ B)
    //Sets the bits to the result of binary XOR on corresponding pairs of bits of *this and other.
    Proposition operator ^ (const Proposition& other) const;

    //Negation operator (!A)
    Proposition operator !() const;

    //Assign a proposition to a bool
    void operator = (const bool& bool_arg);

//NON-MEMBER functions for CONDITIONAL and BICONDITIONAL
    //Tried overloading with -> and <-> but they already have predetermined meanings.
    //Ref. QN orums for % and %=

    //Conditional operator (->) (A & B – operator -> is overloaded, as modulo is inappropriate in this context)
    friend Proposition operator % (const Proposition& A, const Proposition& B);

    //Biconditional operator (<->) (aka (A->B)&(B->A))
    friend Proposition operator %= (const Proposition& A, const Proposition& B);

    // << operator overloading to print data
    friend std::ostream& operator << (std::ostream& os, const Proposition& other);
};

#endif //Propositon_hpp
