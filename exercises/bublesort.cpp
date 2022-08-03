// Difficulty: Easy
// Category: Sorting
// 
// Write a function that takes in an array of integers and returns a sorted version of that array.
// Use the Bubble Sort Algorithm to sort the array.
// 
// If you are unfamiliar with Bubble Sort, we recommend watching the Conceptual Overview section of
// this question's video explanation before starting to code
// 
// Sample Input
// array = [8, 5, 2, 9, 5, 6, 3]
// 
// Sample Output
// [2, 3, 5, 5, 6, 8, 9]
// 

#include <vector>
using namespace std;

vector<int> bubbleSort(vector<int> array)
{
    bool notSorted = true;

    do
    {
        notSorted = false;
        for(auto it = array.begin(); it != array.end()-1; it++)
        {
            if(*(it) > *(it+1))
            {
                std::iter_swap(it, it+1);
                notSorted = true;
            }
        }
    }while(notSorted);

    return array;
}
