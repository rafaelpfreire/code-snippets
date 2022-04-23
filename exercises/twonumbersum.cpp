// Dificulty: Easy
// Category: Arrays

// Write a function that takes in a non-empty array of distinct integers and
// an integer representing a target sum. If any two numbers in the input array
// sum up to the target sum, the function should return them un an array, in 
// any order. If no two numbers sum up to the target sum, the function return
// an empty array.
//
// Note that the target sum has to be obtained by summing two different integers
// in the array; you can't add a single integer to itself in order to obtain
// the target sum.
//
// You can assume that there will be at most one pair of numbers summing up
// to the target sum.
//
// Sample input: 
// array = [3, 5, -1, 8, 1, -1, 6]
// targetSum = 10
//
// Sample output:
// [-1, 11]

//
// O(n^2) time | O(1) space
// Two nested for loops traversing the array
//
#include <vector>
using namespace std;

//
// O(n^2) time | O(1) space
// Two nested for loops traversing the array
//
vector<int> twoNumberSum(vector<int> array, int targetSum) {
    for(int i = 0; i < array.size(); i++)
    {
        for(int j = i+1; j < array.size(); j++)
        {
            if((array[i] + array[j]) == targetSum)
            {
                return vector<int>{array[i], array[j]};
            }
        }
    }
        
    return {};
}

//
// O(n) time | O(n) space
// Because accessing the hash table (htabl.find) is O(1)
// and we are traversing the array only one time
//
vector<int> twoNumberSum(vector<int> array, int targetSum) {
    int complement = 0;
    unordered_map<int,bool> htable;

    for(auto data: array)
    {
        complement = targetSum - data;
        if( htable.find(complement) == htable.end() )
        {
            htable[data] = true;
        }
        else
        {
            return vector<int>{data, complement};
        }
    }

  return {};
}

//
// O(n.log) time | O(1) space
// Sorting the array using an optimal algorithm is going
// to take O(n.log) like merge sort.
//
vector<int> twoNumberSum(vector<int> array, int targetSum) {
	int left = 0;
	int right = array.size()-1;
	int currentSum = 0;

	sort(array.begin(), array.end());

	while(left < right)
	{
		currentSum = array[left] + array[right];
		if(currentSum == targetSum)
		{
			return vector<int>{array[left], array[right]};
		}
		else if(currentSum < targetSum)
		{
			left++;
		}
		else
		{
			right--;
		}
	}

  return {};
}
