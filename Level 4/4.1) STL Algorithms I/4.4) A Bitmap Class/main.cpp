//4.1) STL Algorithms I, 4. A bitmap class

/*Purpose:  create a useful class that has many applications. We call it a bitmap and it can be created 
            as a partial specialization of the matrix class that we discussed in exercise 3 in which the specialised class is 
            the Proposition class of exercise 1.
*/

//Author: Andrew Guerrand

//Modificates dates: 6/24/2023

#include <iostream>
#include "Proposition.hpp"
#include "Matrix.hpp"
#include <string>
#include <bitset>
#include <exception>

//Given
using value_type = Proposition;

//Bitmap
template <int NR, int NC>
using BitMap = Matrix<value_type, NR, NC>;

//Bitmap2
template <int NR, int NC>
using BitMap2 = std::array<std::bitset<NC>, NR>;

//Print function for BitMap2. Print function for BitMap is already defined within Matrix function
template<int NR, int NC>
void Printb2 (const BitMap2<NR,NC>& source)
{
    std::cout << "[";
    for (int i = 0; i < NR; i++)
    {
        std::cout << "[";
        for (int j = 0; j < NC; j++)
        {
            //As per documentation, accssing specific bit is achieved through [] operator
            std::cout << source[j];
            if (j != NC - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        if (i != NR - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}


//Generic function to create a third bitmap. For each, we could AND the individual cells of the bitmaps that we apply to the cells of two bitmaps.
using BitFunction = std::function<Proposition(const Proposition&, const Proposition&)>; //Alias

template <int NR, int NC>
BitMap<NR, NC> mask(const BitMap<NR, NC>& bm1, const BitMap<NR, NC>& bm2, const BitFunction& masker)
{
    BitMap<NR, NC> result;

    for(int i=0; i<NR; i++)
    {
        for(int j=0; j<NC;j++)
        {
            result[i][j] = masker(bm1[i][j], bm2[i][j]);
        }
    }
    return result;
}

//PART C: generic function to initialise BitMap2 efficiently using a string of 0s and 1s
template <int NR, int NC>
void initialise(BitMap2<NR, NC>& bm, int row, const std::string& bitstring) 
{
    if (row >= 0 && row < NR && bitstring.length() == NC)
    {
        for (int i = 0; i < NC; i++)
        {
            bm[row][i] = (bitstring[i] == '1');
        }
    }
    else
    {
        throw std::invalid_argument("Invalid row number or length of string.");
    }
}



int main()
{

//PART A:
    BitMap<3,3> b_1;    //Matrix of 3 rows and 3 columns of default Proposition, for which Proposition's sole private member is a bitset of size 1
    BitMap2<3,3> b2_1;  //NR arrays (number of rows) of bitsets of size NC (number of columns)
    
    std::cout << "Printing b_1, as a Bitmap of 3 rows and 3 columns of default type" << std::endl;
    b_1.Print();

    std::cout << "Printing b_2, as a Bitmap2 of 3 rows and 3 columns of default type" << std::endl;
    Printb2<3,3>(b2_1);

//PART B:   Testing generic function for part B
//          CAREFUL: elements are zero based. So the first element has index 0...
    BitMap<4, 4> bm(true);
    bm(3, 2) = false;

    BitMap<4, 4> bm2(true);
    bm2(3, 2) = true;


    //AND
    auto AND = [](const Proposition& p1,const Proposition& p2) 
    {   Proposition temp = p1;
        return temp & p2; 
    };

    //OR
    auto OR = [](const Proposition& p1,const Proposition& p2) 
    {   Proposition temp = p1;
        return temp | p2; 
    };

    //XOR 
    auto XOR = [](const Proposition& p1,const Proposition& p2) 
    {   Proposition temp = p1;
        return temp ^ p2; 
    };

    //CONDITIONAL
    auto COND = [](const Proposition& p1,const Proposition& p2) { return p1 % p2; };

    //BICONDITIONAL
    auto UNCONDO = [](const Proposition& p1, const Proposition& p2){return p1 %= p2; };

    //PRINTING
    std::cout << "\n Using AND" << std::endl;
    mask(bm, bm2, AND).Print();

    std::cout << "\n Using OR" << std::endl;
    mask(bm, bm2, OR).Print();

    std::cout << "\n Using XOR" << std::endl;
    mask(bm, bm2, XOR).Print();

    std::cout << "\n Using COND" << std::endl;
    mask(bm, bm2, COND).Print();

    std::cout << "\n Using CONDO" << std::endl;
    mask(bm, bm2, UNCONDO).Print();

/*
One of the shortcomings of BitMap is the drudgery of setting its rows, for example:
    BitMap<NR, NC> bitblt(false);
    bitblt(1, 2) = bitblt(1, 3) = bitblt(1, 4) = bitblt(1, 6) = true;
Now use BitMap2 to make life easier:
    const int P = 8; const int Q = 8;
    BitMap2<P, Q> bitblt2;
    initialise(bitblt2, 0, std::string("01111100"));
*/


    BitMap2<8, 8> bitblt2;
    initialise<8, 8>(bitblt2, 0, "11110100");
    initialise<8, 8>(bitblt2, 1, "00110011");
    initialise<8, 8>(bitblt2, 2, "01110001");
    initialise<8, 8>(bitblt2, 3, "10001111");
    initialise<8, 8>(bitblt2, 4, "10101110");
    initialise<8, 8>(bitblt2, 5, "11110100");
    initialise<8, 8>(bitblt2, 6, "00110011");
    initialise<8, 8>(bitblt2, 7, "01110001");

    Printb2<8,8>(bitblt2);

    return 0;
}