#ifndef COP4530_BST_H
#define COP4530_BST_H
/********************************
 * COP 4530
 * FSU Department of Computer Sience
 ********************************/

#include <string>
#include <utility>

// namespace cop4530
//{
template <typename T>
class BST
{
public:
    BST();                                              // constructor. Parameter th specifies the value for the single-rotation threshold. The default value default_threshold_value should be 1.
    BST(const std::string input);                       // constructor. The first parameter is a string containing the values (separated by spaces) to be inserted into the BST. An example could be string "1 23 34 30" for an integer-valued BST, which indicates to insert integers 1, 23, 34, and 30 into the tree in that order. The second parameter specifies the value for the single-rotation threshold. The default value default_threshold_value should be 1.
    BST(const BST &);                                   // copy constructor. You need to copy both the element and the corresponding search count in each node.
    BST(BST &&);                                        // move constructor
    ~BST();                                             // destructor
    void buildFromInputString(const std::string input); // parameter "input" is string containing the values to be inserted to the tree (separated by spaces), as we have discussed above. The tree should be built based on the input string. If the tree contains nodes before the function is called, you need to first delete all the existing nodes.
    const BST &operator=(const BST &);                  // copy assignment operator. You need to copy both the element and the corresponding search count in each node.
    const BST &operator=(BST &&);                       // move assignment operator.
    bool empty();                                       // return true if the tree is empty. Return false otherwise.
    // The following public functions will call the corresponding private versions of the functions to perform certain tasks:
    void printInOrder() const;    // print out the elements in the tree in the in-order traversal.
    void printLevelOrder() const; // print out the elements in the tree in the level-order traversal.
    int numOfNodes() const;       // return the number of nodes in the tree.
    int height() const;           // return the height of the tree.
    void makeEmpty();             // delete all nodes from the tree (make the tree empty)
    void insert(const T &v);      // insert v into the tree.
    void insert(T &&v);           // insert v into the tree (move instead of copy)
    void remove(const T &v);      // delete value v from the tree.
    bool contains(const T &v);    // search to determine if v is the tree.

private:
    struct BSTNode
    {
        T element;
        int searchcount;
        BSTNode *left;
        BSTNode *right;
        BSTNode(const T &theElement, BSTNode *lt, BSTNode *rt)
            : element{theElement}, left{lt}, right{rt} {}
        BSTNode(T &&theElement, BSTNode *lt, BSTNode *rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
    };
    int threshold;
    BSTNode *root;
    void printInOrder(BSTNode *t) const;    // print the elements in the subtree rooted at t in the in-order traversal.
    void printLevelOrder(BSTNode *t) const; // print the elements in the subtree rooted at t in the level-order traversal.
    void makeEmpty(BSTNode *&t);            // delete all nodes in the subtree rooted at t. Called by functions such as the destructor.
    void insert(const T &v, BSTNode *&t);   // insert v into the subtree rooted at t. No duplicated elements are allowed. If value v is already in the subtree, this function does nothing. Initialize the search count to 0 for the newly added node.
    void insert(T &&v, BSTNode *&t);        // insert v into the subtree rooted at t (move instead of copy). No duplicated elements are allowed. If value v is already in the subtree, this function does nothing. Initialize the search count to 0 for the newly added node.
    void remove(const T &v, BSTNode *&t);   // remove value v from the subtree rooted at t (if it is in the subtree). If the node x containing v has two child nodes, replace the value of node x with the smallest value in the right subtree of the node x.
    bool contains(const T &v, BSTNode *&t); // return true if v is in the subtree rooted at t; otherwise, return false. Note that the search count of the corresponding node containing v should be increased by 1. If search count reaches the threshold, perform the single rotation discussed above. Reset search count to 0. If the node containing the value v is already the root of the tree, do not rotate (but you do need to reset the search count to 0). Note that you can add other parameters if necessary. You may or may need to add additional parameters depending on your design and implementation of BST.
    int numOfNodes(BSTNode *t) const;       // return the number of nodes in the subtree rooted at t.
    int height(BSTNode *t) const;           // return the height of the subtree rooted at t. Recall that the height of a tree is the number of the links along the longest path from the root to any of the leaf nodes. The height is an empty tree is -1.
    BSTNode *clone(BSTNode *t) const;       // clone all nodes in the subtree rooted at t. Called by functions such as the assignment operator=. Note that you also need to copy the search count in the original node to the corresponding cloned node.
};
#include "BST.hpp"
//}
#endif