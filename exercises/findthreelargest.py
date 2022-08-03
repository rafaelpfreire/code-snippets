# Dificulty: Easy
# Category: Search
#
# Write a function that thakes in an array of at least three integers and,
# without sorting the array, returns a sorted array of the three largest integers
# in the input array
#
# The function should return duplicate integers if necessary; for example, it should
# return [10, 10, 12] for an input array of [10, 5, 9, 10, 12].
#
# Sample Input:
# array = [141, 1, 17, -7, -17, -27, 18, 541, 8, 7, 7]
#
# Sample Output:
# [18, 141, 541]

def findThreeLargestNumbers(array):
    output = list()
    for i in range(3):
        largest = max(array)
        output.append(largest)
        array.remove(largest)

    return sorted(output)

def findThreeLargestNumbers(array):
    output = [float('-inf')] * 4
    for item in array:
        output[0] = item
        output.sort()

    return output[-3:]
