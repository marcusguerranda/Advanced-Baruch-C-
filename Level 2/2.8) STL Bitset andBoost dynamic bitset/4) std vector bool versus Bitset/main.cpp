//2.8) 4. std::vector<bool> versus Bitset

//Purpose: An alternative to bitsets is to employ the class std::vector<bool>. There has been much discussion 
//         about the shortcomings of this class (for example, its iterators and it does not necessarily store its 
//         elements as a contiguous array).

//Author: Andrew Guerrand

//Modification dates: 5/29/2023

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<bool> Intersect_vectors (const std::vector<bool>& source_vector1, const std::vector<bool>& source_vector2)
{   
    //I'll plainly assume that both vectors are of the same size, and if not, I'll throw an exception
    if(source_vector1.size() != source_vector2.size())
    {
        throw std::invalid_argument("Vectors not of the same size");
    };

    std::vector<bool> results(source_vector1.size());

    auto lambda = [](bool a, bool b){return (a==b);};
    std::transform(source_vector1.begin(), source_vector1.end(), source_vector2.begin(), results.begin(), lambda);

    return results;
}


int main()
{

/*PART A:

Vectors don't include bitwise operators... which is of most interest to us. However, std::vector does include:
    • swap
    • resize
    • flip
    • push_back
    • pop_back
    • modification at run-time 
*/

//PART B: Create a function to compute the intersection of two instances std::vector<bool>
//The intersection of two instances std::vector<bool> is the set of elements that are common to both sets. 

    std::vector<bool> vector1 = {1,0,1,0,1,1,0,1,1};
    std::vector<bool> vector2 = {1,1,1,1,1,0,0,0,0};

    std::vector<bool> results = Intersect_vectors(vector1, vector2);
    std::cout << "Results of the intersection of the two vectors 'vector1' and 'vector2' are: \n[";
    if (!results.empty()) 
    {
        std::cout << results[0];
        for (size_t i = 1; i < results.size(); ++i) 
        {
            std::cout << ", " << results[i];
        }
    }
    std::cout << "]" << std::endl;


//Bitset classes are better than std::vector<bool>, hence why they were created in the first place
    return 0;
}