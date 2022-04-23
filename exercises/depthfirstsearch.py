# Dificulty: Easy
# Category: Graphs

# You're given a Node class that has a name and an array of optional
# children nodes. When put together nodes form an acyclic tree-like
# structure.
# 
# Implement the depthFirstSearch method on the Node cass, which takes
# an empty array, traverses the tree using the Depth-first Search
# approach (specifically navigating the tree from left to right),
# stores all of the nodes' names in the input array, and returns it
# 
# Sample Input: 
# graph =      A
#           /  |  \
#          B   C   D
#         / \     / \
#        E   F   G   H
#           / \   \
#          I  J    K
# 
# Sample Output:
# ["A","B","E","F","I","J","C","D","G","K", "H"]

# Do not edit the class below except
# for the depthFirstSearch method.
# Feel free to add new properties
# and methods to the class.
class Node:
    def __init__(self, name):
        self.children = []
        self.name = name

    def addChild(self, name):
        self.children.append(Node(name))
        return self
    #
    # O(v+e) time | O(v) space
    # Given v as vertices (or nodes) and e as edges (or connections)
    # in a graph.
    # We traverse through all the vertices of the graph (v) and for
    # each vertice we call the function again for each edge of the
    # vertice. In this specific case v i roughly equals e.
    #
    def depthFirstSearch(self, array: list) -> list:
        array.append(self.name)
        for child in self.children:
            child.depthFirstSearch(array)
        return array
