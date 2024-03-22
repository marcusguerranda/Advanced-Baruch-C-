#include "Proposition.hpp"


//Default constructor
Proposition::Proposition(){};

//Overloaded constructor taking bool as argument
Proposition::Proposition(const bool& bool_arg): data(bool_arg){};

//Overloaded constructore using std::bitset<1> as argument
Proposition::Proposition(std::bitset<1> arg): data(arg){};
    
//BOOLEAN OPERATORS

//Equality operator (A == B)
//true if the value of each bit in *this equals the value of the corresponding bit in rhs, otherwise false
bool Proposition::operator == (const Proposition& other) const
{
    //Given dat is a bitset of size 1, I can simply do the below rather than comparing values for each indices
    return data == other.data;
}

//Inequality operator (A != B)
//true if !(*this == rhs), otherwise false
bool Proposition::operator != (const Proposition& other) const
{
    return data != other.data;
}

//Conjunction operator (AND) (A & B)
//Sets the bits to the result of binary AND on corresponding pairs of bits of *this and other.
Proposition Proposition::operator & (const Proposition& other) const
{
    return Proposition(data & other.data);
}

//Disjunction operator (OR) (A | B)
//Sets the bits to the result of binary OR on corresponding pairs of bits of *this and other.
Proposition Proposition::operator | (const Proposition& other) const
{
    return Proposition(data | other.data);
}

//Exclusive OR operator (XOR) (A ^ B)
//Sets the bits to the result of binary XOR on corresponding pairs of bits of *this and other.
Proposition Proposition::operator ^ (const Proposition& other) const
{
    return Proposition(data ^ other.data);
}

//Negation operator (!A)
Proposition Proposition::operator ! () const
{
    return !data[0];;
}

//Assign a proposition to a bool
void Proposition::operator = (const bool& bool_arg)
{
    data = bool_arg;
}

//Conditional operator (->) (A % B)
Proposition operator % (const Proposition& A, const Proposition& B)
{
    return Proposition(!(A.data[0]) | B.data[0]);
}

//Biconditional operator (<->) (A <-> B)
Proposition operator %= (const Proposition& A, const Proposition& B)
{
    return Proposition((A % B) & (B % A));
}

// << operator overloading to print data
std::ostream& operator << (std::ostream& os, const Proposition& other)
{
    os << std::boolalpha << other.data[0];
	return os;
}