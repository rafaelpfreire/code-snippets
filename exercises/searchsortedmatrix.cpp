// Dificulty: Medium
// Category: Search
//
// You're given a two-dimensional array (a matrix) of distinct integers and a target integer.
// Each row in the matrix is sorted, and each column is also sorted; the matrix doesn't
// necessarily have the same height and width
//
// Write a function that returns an array of the row and column indices of the target integer.
// If it's contained in the matrix, otherwise return [-1, -1]
//
// Sample Input:
// {
//   "matrix": [
//     [1, 4, 7, 12, 15, 1000],
//     [2, 5, 19, 31, 32, 1001],
//     [3, 8, 24, 33, 35, 1002],
//     [40, 41, 42, 44, 45, 1003],
//     [99, 100, 103, 106, 128, 1004]
//   ],
//   "target": 44
// }
//
// Sample Output:
// [3, 3]

#include <vector>
using namespace std;

vector<int> searchInSortedMatrix(vector<vector<int>> matrix, int target) {
    int i = -1;
    int j = -1;
    for(auto row: matrix)
    {
        auto itemit = std::find(row.begin(), row.end(), target);
        if(itemit != row.end())
        {
            auto rowit = std::find(matrix.begin(), matrix.end(), row);

            i = rowit - matrix.begin();
            j = itemit - row.begin();
        }
    }
    return {i, j};
}
