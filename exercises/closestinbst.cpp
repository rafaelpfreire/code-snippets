// Dificulty: Easy
// Category: Binary Search Tree
//
// Write a function that takes in a Binary Search Tree (BST) and a target
// interger value and returns the closest value to that target value
// contained in the BST.
//
// You can assume that there will be one closest value
//
// Each BST node has an integer value, a left child node, and a right child
// node. A node is said to be a valid BST node if and only if it satisfies
// thr BST property: its value is strictly greater than the values of every
// node to its left; its value is less than or equal to the values of every
// node to its right; and its children nodes are either valid BST nodes
// themselves or None / null.
//
// Sample Input:
// tree =   10
//        /    \
//       5     15
//      / \   /  \
//     2  5  13  22
//    /        \
//   1         14
//
// Sample Output:
// 13


class BST {
public:
  int value;
  BST *left;
  BST *right;

  BST(int val);
  BST &insert(int val);
};

//
// Avarage: O(log) time | O(1) space
// Worst: O(n) time | O(1) space
// Each iteration we're eliminating half of the tree
// and just using some variables to store the result
//
int findClosestValueInBst(BST *tree, int target) {
    BST *auxtree = tree;
    int ret = tree->value;
    int distance = target - auxtree->value;
    int dsmaller = distance;
    
    while( auxtree != nullptr )
    {
        distance = target - auxtree->value;
        
        if(abs(distance) < abs(dsmaller))
        {
            dsmaller = distance;
            ret = auxtree->value;
        }
        
        if(distance < 0)
        {
            auxtree = auxtree->left;
        }
        else if(distance > 0)
        {
            auxtree = auxtree->right;
        }
        else
        {
            break;
        }
    }
    
    return ret;
}

//
// Avarage: O(log) time | O(log) space
// Worst: O(n) time | O(n) space
// Each iteration we're eliminating half of the tree
// but we're are using the same number of memory
// as function calls
//
int findClosestValueInBst(BST *tree, int target) {
    int ret = INT_MAX;
    int distance;
    int newdistance = INT_MAX;
    int newvalue = tree->value;
    
    distance = target - tree->value;
    if((distance < 0) && (tree->left != nullptr))
    {
        newvalue = findClosestValueInBst(tree->left, target);
        newdistance = target - newvalue;
    }
    else if((distance > 0) && (tree->right != nullptr))
    {
        newvalue = findClosestValueInBst(tree->right, target);
        newdistance = target - newvalue;
    }
    
    if(abs(distance) <= abs(newdistance))
    {
        ret = tree->value;
    }
    else
    {
        ret = newvalue;
    }
    
  return ret;
}

