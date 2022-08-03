# Difficulty: Easy
# Category: Sorting
# 
# Write a function that takes in an array of integers and returns a sorted version of that array.
# Use the Bubble Sort Algorithm to sort the array.
# 
# If you are unfamiliar with Bubble Sort, we recommend watching the Conceptual Overview section of
# this question's video explanation before starting to code
# 
# Sample Input
# array = [8, 5, 2, 9, 5, 6, 3]
# 
# Sample Output
# [2, 3, 5, 5, 6, 8, 9]
# 

def bubbleSort(array):
    notSorted = True

    while(notSorted):
        notSorted = False
        for i in range(0,len(array)-1):
            if array[i] > array[i+1]:
                aux = array[i]
                array[i] = array[i+1]
                array[i+1] = aux
                notSorted = True

    return array
