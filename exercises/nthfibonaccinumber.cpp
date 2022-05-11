// Dificulty: Easy
// Category: Recursion
//
// Fibonacci sequence is defined as follows: the first number of the sequence
// is 0, the second number is 1, and the nth number is the sum of the (n-1)th
// and (n-2)th numbers. Write a function that takes in an integer n and
// returns the nth Fibonacci number.
//
// Important note: the Fibonacci sequence is often defined with its first two
// numbers as F0 = 0 and F1 = 1. For the purpose of this question, the first
// Fibonacci number is F0; therefore, getNthFib(1) is equal to F0, getNthFib(2)
// is equal to F1, etc...
//
// Sample Input: 2
// Sample Output: 1 (0, 1)
//
// Sample Input: 6
// Sample Output: 5 (0, 1, 1, 2, 3, 5)
//

using namespace std;

//
// O(2^n) time | O(n) space
// Each iteration is going to call 2 fibs which each one of them
// is going to call 2 fibs again (or 4 fibs in total), and so on
//
int getNthFib(int n)
{
    if(n <= 1)
    {
        return 0;
    }
    else if(n == 2)
    {
        return 1;
    }
    
    return getNthFib(n -1) + getNthFib(n - 2);
    
  return -1;
}

//
// O(n) time | O(n) space (becase of the hash table
//
int getNthFibHelper(int n, map<int,int> &hashTable)
{
    if(hashTable.find(n) != hashTable.end())
    {
        return hashTable[n];
    }
    else
    {
        hashTable[n] = getNthFibHelper(n-1, hashTable) + getNthFibHelper(n-2, hashTable);
        return hashTable[n];
    }
}

int getNthFib(int n)
{
    map<int,int> hashTable {{0,0}, {1,0}, {2,1}};
  return getNthFibHelper(n, hashTable);
}

//
// O(n) time | O(1) space
//
int getNthFib(int n)
{
    if(n <= 1)
    {
        return 0;
    }
    
    int current = 1;
    int last = 0;
    int aux = 0;
    
    for(int i = 2; i < n; i++)
    {
        aux = current;
        current += last;
        last = aux;
    }
    
    return current;
}
