# Dificulty: Easy
# Category: Recursion
#
# Fibonacci sequence is defined as follows: the first number of the sequence
# is 0, the second number is 1, and the nth number is the sum of the (n-1)th
# and (n-2)th numbers. Write a function that takes in an integer n and
# returns the nth Fibonacci number.
#
# Important note: the Fibonacci sequence is often defined with its first two
# numbers as F0 = 0 and F1 = 1. For the purpose of this question, the first
# Fibonacci number is F0; therefore, getNthFib(1) is equal to F0, getNthFib(2)
# is equal to F1, etc...
#
# Sample Input: 2
# Sample Output: 1 (0, 1)
#
# Sample Input: 6
# Sample Output: 5 (0, 1, 1, 2, 3, 5)
#

#
# O(2^n) time | O(n) space
# Each iteration is going to call 2 fibs which each one of them
# is going to call 2 fibs again (or 4 fibs in total), and so on
#
def getNthFib(n):
    if n <= 1:
        return 0
    elif n == 2:
        return 1

    return getNthFib(n-2) + getNthFib(n-1)

#
# O(n) time | O(n) space (becase of the hash table
#
def getNthFibHelper(n: int, memory: dict):
    if n in memory:
        return memory[n]
    else:
        memory[n] = getNthFibHelper(n-1, memory) + getNthFibHelper(n-2, memory)
    return memory[n]

def getNthFib(n):
    return getNthFibHelper(n , {0:0, 1:0, 2:1});

#
# O(n) time | O(1) space
#
def getNthFib(n):
    if n <= 1:
        return 0
    
    current = 1
    last = 0
 
    for i in range(2, n):
        aux = current
        current += last
        last = aux
    
    return current
