/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/*
 * Private helper function thatswaps two nodes. 
 * No new nodes are created.
 */

template <typename T>
void BinaryTree<T>::swap(Node* subRoot) {
    Node* temp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = temp;
}
/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}


/*
 * Private helper function for the public mirror function.
 */
template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) {
    if (subRoot != NULL) {
        swap(subRoot);
        mirror(subRoot->right);
        mirror(subRoot->left);
    }
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    InorderTraversal<T> iot(root);
    Node* prev = *(iot.begin());
    for (typename TreeTraversal<T>::Iterator it = iot.begin(); it != iot.end(); ++it) {
        if (prev->elem > (*it)->elem) return false;
        prev = *it;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    /*
    bool a = isOrderedR(root->left, root->left, root);
    bool b = isOrderedR(root->right, root, root->right);
    return a & b;
    */
    return isOrderedR(root, minNode(root, root), maxNode(root, root));
}

/*
 * Private helper function for public function 
 * isOrderedRecursive
 * @param subRoot of current subtree
 * @return if in-order traversal of tree gives 
 * nondecreasing list of output values.
 */

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::maxNode(Node* subRoot, Node* max) const {
    if (subRoot == NULL) return max;
    if (subRoot->elem > max->elem) max = subRoot;
    
    Node* left = maxNode(subRoot->left, max);
    Node* right = maxNode(subRoot->right, max);

    return (left->elem > right->elem) ? left : right; 
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::minNode(Node* subRoot, Node* min) const {
    if (subRoot == NULL) return min;
    if (subRoot->elem < min->elem) min = subRoot;
    
    Node* left = minNode(subRoot->left, min);
    Node* right = minNode(subRoot->right, min);

    return (left->elem < right->elem) ? left : right; 
}

template <typename T>
bool BinaryTree<T>::isOrderedR(Node* subRoot, Node* min, Node* max) const {
    //base cases
    if (subRoot == NULL) return true;
    if (min == NULL || max == NULL) return true;
    if (subRoot->elem < min->elem || subRoot->elem > max->elem) return false;

    return isOrderedR(subRoot->left, min, subRoot) && isOrderedR(subRoot->right, subRoot, max);
}
