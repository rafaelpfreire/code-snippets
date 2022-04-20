# Dificulty: Easy
# Category: Arrays

# Write a function that takes in a non-empty array of distinct integers and
# an integer representing a target sum. If any two numbers in the input array
# sum up to the target sum, the function should return them un an array, in 
# any order. If no two numbers sum up to the target sum, the function return
# an empty array.
#
# Note that the target sum has to be obtained by summing two different integers
# in the array; you can't add a single integer to itself in order to obtain
# the target sum.
#
# You can assume that there will be at most one pair of numbers summing up
# to the target sum.
#
# Sample input: 
# array = [3, 5, -1, 8, 1, -1, 6]
# targetSum = 10
#
# Sample output:
# [-1, 11]
#
# O(n^2) time | O(1) space

def twoNumberSum(array, targetSum):
    for i in range(len(array)-1):
        firstNum = array[i]
        for j in range(i+1, len(array)):
            secondNum = array[j]
            if (firstNum + secondNum) == targetSum:
                return [firstNum, secondNum]

    return list()
