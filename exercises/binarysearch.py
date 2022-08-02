# Dificulty: Easy
# Category: Search
#
# Write a function that takes in a sorted array of integers as well as a
# target integer. The function should use the Binary Search algorithm to
# determine if the target integer is contained in the array and should
# return its index if it is, otherwise -1.
#
# Sample Input:
# array = [0, 1, 21, 33, 45, 61, 71, 72, 73]
# target 33
#
# Sample Output:
# 3

def binarySearchHelper(array, target, index):
    half = int(len(array) / 2)

    if(len(array) == 0):
        return -1
    elif(array[half] == target):
        return index + half
    elif(array[half] > target):
        return binarySearchHelper(array[:half], target, index)
    else:
        return binarySearchHelper(array[half+1:], target, index+half+1)
    
def binarySearch(array, target):
    return binarySearchHelper(array, target, 0)
