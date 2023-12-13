#include "BST.h"
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;
// Public functions
// namespace cop4530
//{
template <typename T>
BST<T>::BST() : threshold{1}, root{nullptr} {} // threshold{1} is equivalent to threshold = 1

template <typename T>
BST<T>::BST(const string input) : threshold{1}, root{nullptr}
{
    buildFromInputString(input);
}

template <typename T>
BST<T>::BST(const BST &rhs) : threshold{rhs.threshold}, root{nullptr}
{
    root = clone(rhs.root);
}

template <typename T>
BST<T>::BST(BST &&rhs) : threshold{rhs.threshold}, root{rhs.root}
{
    rhs.root = nullptr;
}

template <typename T>
BST<T>::~BST()
{
    makeEmpty();
}

template <typename T>
void BST<T>::buildFromInputString(const string input)
{
    // clear the tree, delete all nodes
    makeEmpty();
    // parse string into values
    stringstream ss(input);
    T value;
    // insert values into tree
    while (ss >> value)
    {
        insert(value);
    }
}
//}
template <typename T>
const BST<T> &BST<T>::operator=(const BST &rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        threshold = rhs.threshold;
        root = clone(rhs.root);
    }
    return *this;
}

template <typename T>
const BST<T> &BST<T>::operator=(BST &&rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        threshold = rhs.threshold;
        root = rhs.root;
        rhs.root = nullptr;
    }
    return *this;
}

template <typename T>
bool BST<T>::empty()
{
    return root == nullptr;
}

template <typename T>
void BST<T>::printInOrder() const
{
    printInOrder(root);
    cout << endl;
}

template <typename T>
void BST<T>::printLevelOrder() const
{
    printLevelOrder(root);
    cout << endl;
}

template <typename T>
int BST<T>::numOfNodes() const
{
    return numOfNodes(root);
}

template <typename T>
int BST<T>::height() const
{
    return height(root);
}

template <typename T>
void BST<T>::makeEmpty()
{
    makeEmpty(root);
}

template <typename T>
void BST<T>::insert(const T &v)
{
    insert(v, root);
}

template <typename T>
void BST<T>::insert(T &&v)
{
    insert(move(v), root);
}

template <typename T>
void BST<T>::remove(const T &v)
{
    remove(v, root);
}

template <typename T>
bool BST<T>::contains(const T &v)
{
    return contains(v, root);
}

// Private functions

template <typename T>
void BST<T>::printInOrder(BSTNode *t) const
{
    if (t != nullptr)
    {
        printInOrder(t->left);
        cout << t->element << " ";
        printInOrder(t->right);
    }
}

template <typename T>
void BST<T>::printLevelOrder(BSTNode *t) const
{
    if (t == nullptr)
        return;

    queue<BSTNode *> q;
    q.push(t);

    while (!q.empty())
    {
        BSTNode *current = q.front();
        q.pop();

        cout << current->element << " ";

        if (current->left != nullptr)
            q.push(current->left);

        if (current->right != nullptr)
            q.push(current->right);
    }
}

// adapted from book
template <typename T>
void BST<T>::makeEmpty(BSTNode *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

// adapted from book
template <typename T>
void BST<T>::insert(const T &v, BSTNode *&t)
{
    if (t == nullptr)
    {
        t = new BSTNode{v, nullptr, nullptr};
    }
    else if (v < t->element)
    {
        insert(v, t->left);
    }
    else if (t->element < v)
    {
        insert(v, t->right);
    }
    else
    {
        // Duplicate; do nothing
    }
}

template <typename T>
void BST<T>::insert(T &&v, BSTNode *&t)
{
    if (t == nullptr)
    {
        t = new BSTNode{move(v), nullptr, nullptr};
    }
    else if (v < t->element)
    {
        insert(move(v), t->left);
    }
    else if (v > t->element)
    {
        insert(move(v), t->right);
    }
    else
    {
        // Duplicate value, do nothing
    }
}

// adapted from book
template <typename T>
void BST<T>::remove(const T &v, BSTNode *&t)
{
    if (t == nullptr)
    {
        // Item not found, do nothing
        return;
    }

    if (v < t->element)
    {
        remove(v, t->left);
    }
    else if (t->element < v)
    {
        remove(v, t->right);
    }
    else if (t->left != nullptr && t->right != nullptr) // two children
    {
        BSTNode *minRight = t->right;
        while (minRight->left != nullptr)
        {
            minRight = minRight->left;
        }
        t->element = move(minRight->element);
        remove(t->element, t->right);
    }
    else
    {
        BSTNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}

template <typename T>
bool BST<T>::contains(const T &v, BSTNode *&t)
{
    if (t == nullptr)
    {
        // Value not found
        return false;
    }
    else if (v < t->element)
    {
        // Search in the left subtree
        bool result = contains(v, t->left);
        if (result)
        {
            t->searchcount++;
            if (t->searchcount == threshold)
            {
                // Perform single rotation
                // Your single rotation implementation goes here
                // Reset search count to 0
                t->searchcount = 0;
            }
        }
        return result;
    }
    else if (v > t->element)
    {
        // Search in the right subtree
        bool result = contains(v, t->right);
        if (result)
        {
            t->searchcount++;
            if (t->searchcount == threshold)
            {
                // Perform single rotation
                // Your single rotation implementation goes here
                // Reset search count to 0
                t->searchcount = 0;
            }
        }
        return result;
    }
    else
    {
        // Node with the value v found
        t->searchcount++;
        if (t->searchcount == threshold)
        {
            // Perform single rotation
            // Your single rotation implementation goes here
            // Reset search count to 0
            t->searchcount = 0;
        }
        return true;
    }
}

template <typename T>
int BST<T>::numOfNodes(BSTNode *t) const
{
    if (t == nullptr)
        return 0;

    return 1 + numOfNodes(t->left) + numOfNodes(t->right);
}

template <typename T>
int BST<T>::height(BSTNode *t) const
{
    if (t == nullptr)
        return -1;

    int leftHeight = height(t->left);
    int rightHeight = height(t->right);

    return 1 + max(leftHeight, rightHeight);
}

// adapted from book
template <typename T>
typename BST<T>::BSTNode *BST<T>::clone(BSTNode *t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new BSTNode{t->element, clone(t->left), clone(t->right)};
}
//}