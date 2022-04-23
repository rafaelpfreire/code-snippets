# Dificulty: Easy
# Category: Binary Trees

# Write a function that takes in a Binary Tree and returns a list of
# its branch sums ordered from leftmost branch sum to rightmost branch
# sum.
#
# A branch sum is the sum of all values in a Binary Tree branch. A Binary
# Tree branch is a path of nodes in a tree that starts at the root node
# and ends at any leaf node.
#
# Each Binary Tree node has an integer value, a left child node, and a
# right child node. Children nodes ca either be Binary Tree nodes themselves
# or None / null.
#
# Sample Input:
# tree =     1
#         /     \
#        2       3
#      /   \   /   \
#     4     5 6    7
#    / \   /
#   8   9 10
#
# Sample Output:
# [15, 16, 18, 10, 11]

#
# O(n) time | O(n) space
# We need to traverse all the elements of the tree
# and and store the acc in a list which has a size
# equals to the number of leafs (avarage n/2).
#
def branchSumsHelper(node, acc, sumList):
    if node is None:
        return
    
    acc += node.value
    
    # Check if node is a leaf
    if (node.left is None) and (node.right is None):
        sumList.append(acc)
        return
    
    branchSumsHelper(node.left, acc, sumList)
    branchSumsHelper(node.right, acc, sumList)

def branchSums(root):
    sumList = list()
    branchSumsHelper(root, 0, sumList)
    return sumList
