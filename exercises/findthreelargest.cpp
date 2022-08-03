// Dificulty: Easy
// Category: Search
//
// Write a function that thakes in an array of at least three integers and,
// without sorting the array, returns a sorted array of the three largest integers
// in the input array
//
// The function should return duplicate integers if necessary; for example, it should
// return [10, 10, 12] for an input array of [10, 5, 9, 10, 12].
//
// Sample Input:
// array = [141, 1, 17, -7, -17, -27, 18, 541, 8, 7, 7]
//
// Sample Output:
// [18, 141, 541]

#include <vector>
using namespace std;

vector<int> findThreeLargestNumbers(vector<int> array) {
    std::vector<int> maxes;

    for(int i = 0; i < 3; i++)
    {
        auto largest = std::max_element(array.begin(), array.end());
        maxes.push_back(*largest);
        array.erase(largest, largest+1);
    }

    std::sort(maxes.begin(), maxes.end());
    return maxes;
}


#include <vector>
using namespace std;

vector<int> findThreeLargestNumbers(vector<int> array) {
    std::vector<int> output;
    for(auto item: array)
    {
        output.insert(output.begin(), item);
        std::sort(output.begin(), output.end());
    }
    std::vector<int>newVec(output.end()-3, output.end());
    return newVec;
}
