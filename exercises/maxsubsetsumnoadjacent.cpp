// Dificulty: Medium
// Category: Dynamic Programming
//
// Write a function that takes in an array of positive integers and returns
// the maximum sum of non-adjacent elements in the array.
//
// If the input array is empty, the function should return 0.
//
// Sample Input:
// array = [75, 105, 120, 75, 90, 135]
//
// Sample Output:
// 330 = 75 + 120 + 135

#include <vector>
using namespace std;

//
// O(n) time | O(n) space
// We're traversing the array one time and using another
// array to store its sums
//
int maxSubsetSumNoAdjacent(vector<int> array)
{
    if(array.size() == 0)
    {
        return 0;
    }
    else if(array.size() == 1)
    {
        return array[0];
    }

    vector<int> maxSumsArray = array;
    maxSumsArray[1] = max(array[0], array[1]);
    
    for(int i = 2; i < array.size(); i++)
    {
        maxSumsArray[i] = max( maxSumsArray[i-1], maxSumsArray[i-2] + array[i] );
    }
    
    return maxSumsArray.back();
}
