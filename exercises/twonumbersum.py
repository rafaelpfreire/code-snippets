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
# Two nested for loops traversing the array
#
def twoNumberSum(array, targetSum):
    for i in range(0, len(array)):
        for j in range(i+1, len(array)):
            if (array[i] + array[j]) == targetSum:
                return [array[i], array[j]]

    return []

#
# O(n) time | O(n) space
# Because accessing the hash table (x in dict) is O(1)
# and we are traversing the array only one time
#
def twoNumberSum(array, targetSum):
    htable = dict()

    for data in array:
        complement = targetSum - data
        if complement not in htable:
            htable[data] = True
        else:
            return [complement, data]
    
    return []

#
# O(n.log) time | O(1) space
# Sorting the array using an optimal algorithm is going
# to take O(n.log) like merge sort.
#
def twoNumberSum(array, targetSum):
    array.sort()
    left = 0
    right = len(array) - 1
    
    while left < right:
        currentSum = array[left] + array[right]
        if currentSum == targetSum:
            return [array[left], array[right]]
        elif currentSum < targetSum:
            left += 1
        else:
            right -= 1
    
    return []
