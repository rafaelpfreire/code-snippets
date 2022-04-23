# Dificulty: Medium
# Category: Dynamic Programming
#
# Write a function that takes in an array of positive integers and returns
# the maximum sum of non-adjacent elements in the array.
#
# If the input array is empty, the function should return 0.
#
# Sample Input:
# array = [75, 105, 120, 75, 90, 135]
#
# Sample Output:
# 330 = 75 + 120 + 135


#
# O(n) time | O(n) space
# We're traversing the array one time and using another
# array to store its sums
#
def maxSubsetSumNoAdjacent(array):
    if not array:
        return 0
    elif len(array) == 1:
        return array[0]
    
    maxSumsArray = array[:]
    maxSumsArray[1] = max(array[1], array[0])
    
    for i in range(2,len(array)):
        maxSumsArray[i] = max( maxSumsArray[i-1], maxSumsArray[i-2] + array[i] )
    
    return maxSumsArray[-1]
