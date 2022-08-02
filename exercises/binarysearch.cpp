// Dificulty: Easy
// Category: Search
//
// Write a function that takes in a sorted array of integers as well as a
// target integer. The function should use the Binary Search algorithm to
// determine if the target integer is contained in the array and should
// return its index if it is, otherwise -1.
//
// Sample Input:
// array = [0, 1, 21, 33, 45, 61, 71, 72, 73]
// target 33
//
// Sample Output:
// 3

#include <vector>
#include <iostream>
using namespace std;

int binarySearchHelper(vector<int> array, int target, int index)
{
    int half = array.size() / 2;

    if(array.size() == 0)
    {
        return -1;
    }
    else if(array[half] == target)
    {
        return index + half;
    }
	else if(array[half] > target)
	{
        std::vector<int> newvec(array.begin(), array.begin() + half);
		return binarySearchHelper(newvec, target, index);
	}
	else
	{
        std::vector<int> newvec(array.begin() + half+1, array.end());
		return binarySearchHelper(newvec, target, index+half+1);
	}
}

int binarySearch(vector<int> array, int target)
{
    return binarySearchHelper(array, target, 0);
}
