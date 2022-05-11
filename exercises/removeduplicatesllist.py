# You're given the head of a Singly Linked List whose nodes are in sorted
# order with respect to ther values. Write a function that returns a 
# modufied version of the Linked List that doesn't contain any nodes
# with duplicate values. The Linked List should be modified in place
# (i.e., you shouldn't create a brand new list), and the modified Linked
# List should still have its nodes sorted with respect to their values.
#
# Each LinkedList node has an integer value as ewll as a next node pointing
# to the next node in the list or to None / null if it's the tail of the list.
#
# Sample Input:
# linkedList = 1 -> 1 -> 3 -> 4 -> 4 -> 4 -> 5 -> 6 -> 6
#
# Sample Output:
# 1 -> 3 -> 4 -> 5 -> 6

# This is an input class. Do not edit.
class LinkedList:
    def __init__(self, value):
        self.value = value
        self.next = None

#
# O(n) time | O(1) space
# Traversing the entire list one time
#
def removeDuplicatesFromLinkedList(linkedList):
    node = linkedList
    while node.next is not None:
    if node.value == node.next.value:
        node.next = node.next.next
    else:
        node = node.next
    
    return linkedList
