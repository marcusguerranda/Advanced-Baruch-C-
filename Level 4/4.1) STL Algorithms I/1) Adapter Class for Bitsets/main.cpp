//4.1) STL Algorithms I. 1) Adapter Classes for bitsets

//Purpose: Examine the ADTS and some of the algorithms in STL and build new generic abstractions on top of them.
//         Design and implement reusable classes and functionality in C++11.

//Author: Andrew Guerrand

//Modification dates: 6/22/2023


#include "Proposition.hpp"

int main()
{
//PART B: testing constructors + operator overloading
    std::cout << "\nPART B: constructors and operator overloading\n" << std::endl;

    Proposition p1;                                     //Test default constructor
    bool b = true;
    Proposition p2(b);                                  //Test constructor with bool argument
    std::bitset<1> bit(0);
    Proposition p3(bit);                                //Test constructor with std::bitset<1> argument

    Proposition p4 = (p1 & p2);                         //Test AND operator
    Proposition p5 = (p1 | p2);                         //Test OR operator
    Proposition p6 = (p1 ^ p2);                         //Test XOR operator
    Proposition p7 = (!p1);                             //Test negation operator

    bool result1 = (p1 == p2);                          //Test equality operator
    bool result2 = (p1 != p2);                          //Test inequality operator
    Proposition p8 = true;                                 //Assign a proposition to a bool, here 'true' 

    Proposition p9 = (p1 % p2);                         //Test conditional operator
    Proposition p10 = (p1 %= p2);                       //Test biconditional operator

    std::cout << "Default constructor, p1: " << p1 << std::endl;
    std::cout << "Overloaded constructor with bool as argument, p2: " << p2 << std::endl;
    std::cout << "Overloaded constructor with std::bitset<1> as argument, p3: " << p3 << std::endl;
    std::cout << "AND operator, s.t p1 & p2 -> p4: " << p4 << std::endl;
    std::cout << "OR operator, s.t p1 | p2 -> p5: " << p5 << std::endl;
    std::cout << "XOR operator, s.t p1^p2 -> p6: " << p6 << std::endl;
    std::cout << "Negation operator, s.t !p1 -> p7: " << p7 << std::endl;
    std::cout << "Assignment operator, p8: " << p8 << std::endl;
    std::cout << "Conditional operator, s.t p1 % p2, p9: " << p9 << std::endl;
    std::cout << "Biconditional operator, s.t p1 %= p2 " << p10 << std::endl;
    std::cout << "Equality operator, s.t p1 == p2: " << result1 << std::endl;
    std::cout << "Inequality operator, s.t p1 != p2: " << result2 << std::endl;

//PART C) Check that your code satisfies De Morgan’s Laws:
//          - NOT (A OR B) == NOT(A) AND NOT(B)
//          - NOT (A AND B) == NOT(A) OR NOT(B).
    std::cout << "\nPART C: De Morgan's laws\n" << std::endl;

    Proposition A = false;
    Proposition B = true;
    Proposition C = false;

    //De Morgan's Laws: NOT (A OR B) == NOT(A) AND NOT(B)
    Proposition leftSide = !(A | B);
    Proposition rightSide = (!A) & (!B);

    std::cout << std::boolalpha;
    std::cout << "NOT (A OR B) == NOT(A) AND NOT(B): " << (leftSide == rightSide) << std::endl;

    // De Morgan's Laws: NOT (A AND B) == NOT(A) OR NOT(B)
    leftSide = !(A & B);
    rightSide = (!A) | (!B);

    std::cout << "NOT (A AND B) == NOT(A) OR NOT(B): " << (leftSide == rightSide) << std::endl;

//PART D) Check that your code satisfies the Distributive Laws:
//          - A AND(B OR C) == (A AND B) OR (A OR C)
//          - A OR(B AND C) == (A OR B) AND (A OR C).
    std::cout << "\nPART D: Distributive laws\n" << std::endl;

    //Distributive Law: A AND (B OR C) == (A AND B) OR (A AND C)
    leftSide = A & (B | C);
    rightSide = (A & B) | (A & C);

    std::cout << "A AND (B OR C) == (A AND B) OR (A AND C): " << (leftSide == rightSide) << std::endl;

    //Distributive Law: A OR (B AND C) == (A OR B) AND (A OR C)
    leftSide = A | (B & C);
    rightSide = (A | B) & (A | C);

    std::cout << "A OR (B AND C) == (A OR B) AND (A OR C): " << (leftSide == rightSide) << std::endl;


//PART E) Let A, B and C be propositions. Check that the statement form:
//          - [A -> (B -> C)] <-> [(A & B) -> C]   is a tautology it always returns true for all assignments of truth values to its statement letters A,B 
//          and C). There are EIGHT options to be checked.

    bool isTautology = true; //Assume the statement is a tautology

/*
DIFFERENT CASES FOR ABC, where 0 'false' and 1 'true'
                            -000
                            -001
                            -010
                            -100
                            -101
                            -011
                            -110
                            -111
*/
    //Assume for now that it is a tautology. If not, it will be modified to 'false' below.
    //I will print result after.
    bool is_Tautology = true;

    //Check all possible truth value assignments for A, B, and C


    //METHOD 1 using triple for loops, but it is quite messy
    /*
    std::vector<bool> true_false = {true, false};
    for (auto A : truefalse) {
        for (auto B : truefalse) {
            for (auto C : truefalse) {
                // Evaluate the left side of the statement [A -> (B -> C)]
                Proposition leftSide = (!(A) | (B % C));

                // Evaluate the right side of the statement [(A & B) -> C]
                Proposition rightSide = ((A & B) % C);

                // Check if the left and right sides are equivalent
                if (!(leftSide == rightSide)) {
                    std::cout << "Counterexample found: A = " << A << ", B = " << B << ", C = " << C << std::endl;
                    return; // Exit the function if a counterexample is found
                }
            }
        }
    }
    */

    //METHOD 2: using binary representations. Require a bit more though, but indeed it is quite efficient.
    //Binary representation of a number 
    for(int i = 0; i < 8; i++)
    {
        //Assign truth values based on the current iteration
        A = (i & 0b100) != 0;   
        B = (i & 0b010) != 0;
        C = (i & 0b001) != 0;   // 0b001 indicates that only the rightmost bit is set to 1, and others set to 0

        // Evaluate the left side of the statement [A -> (B -> C)]
        Proposition leftSide = (!(A) | (B % C));

        // Evaluate the right side of the statement [(A & B) -> C]
        Proposition rightSide = ((A & B) % C);

        // Check if the left and right sides are equivalent
        if (!(leftSide == rightSide))
        {
            isTautology = false;
            break; //Exit the loop if a counterexample is found
        }
    }
    std::cout << "It is a tautology: " << is_Tautology << std::endl;


    std::cout << std::endl;
    return 0;
}

