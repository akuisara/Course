//
//  bst.cpp
//  lab
//
//  Created by Qi Zhang on 9/6/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//  Summary: This program prompts user to enter some positive integers and then stores them in a binary search tree, and then user can search for any integer to check if it is in the tree. In the end, the program prints out all the elements in the tree from the smallest number to the greatest to the console.

#include <iostream>
using namespace std;

// --------------------------------
class treeNode
{ // this class define the elements and functions to build a node
  public:
    int value;
    treeNode *left, *right;
    treeNode(int number);
};

treeNode::treeNode(int number)
{ // Constructor
  // PRE: an integer is assigned
    this->value = number;
    this->left = NULL;
    this->right = NULL;
}


// --------------------------------
class binarySearchTree
{ // This class define the elements and functions of a binary search tree
  public:
    binarySearchTree();
    ~binarySearchTree();
    void insert(int key);
    bool search(int key);
    void inOrderTraversal();
  private:
    treeNode *root;
    void destroy_tree(treeNode *leaf);
    void insert_help(int key, treeNode *leaf);
    bool search_help(int key, treeNode *leaf);
    void inOrder_help(treeNode *leaf);
};

binarySearchTree::binarySearchTree()
{ // Constructor
    root = NULL;
}

binarySearchTree::~binarySearchTree()
{ // Destructor
    destroy_tree(root);
}

void binarySearchTree::destroy_tree(treeNode *leaf)
{ // This is the helper function of destructor
  // PRE: a node is assigned
    if (leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void binarySearchTree::insert(int key)
{ // This function insert the integer entered by user to the tree
  // PRE: an integer is assigned
    if (root == NULL) {
        root = new treeNode(key);
    }
    else
        insert_help(key, root);
}

void binarySearchTree::insert_help(int key, treeNode *leaf)
{ // This is the helper function of insert()
  // PRE: an integer && a node are assigned
    if ((key < leaf->value) && (leaf->left != NULL))
        insert_help(key, leaf->left);
    else if ((key < leaf->value) && (leaf->left == NULL))
        leaf->left = new treeNode(key);
    else if ((key > leaf->value) && (leaf->right != NULL))
        insert_help(key, leaf->right);
    else if ((key > leaf->value) && (leaf->right == NULL))
        leaf->right = new treeNode(key);
}

bool binarySearchTree::search(int key)
{ // This function can search for an integer entered by user in the tree
  // PRE: an integer is assigned
  // POST: return a boolean value
    return search_help(key, root);
}

bool binarySearchTree::search_help(int key, treeNode *leaf)
{ // This is the helper function of search()
  // PRE: an integer && a node are assigned
  // POST: return a boolean value
    if (leaf == NULL)
        return false;
    else if (leaf->value == key)
        return true;
    else if (key < leaf->value)
        return search_help(key, leaf->left);
    else
        return search_help(key, leaf->right);
}

void binarySearchTree::inOrderTraversal()
{ // This function can print out all the elements in the tree to the console
    cout << "\nTree = {";
    inOrder_help(root);
    cout << "}\n";
}

void binarySearchTree::inOrder_help(treeNode *leaf)
{ // This is the helper function of inOrderTraversal()
    if (leaf != NULL) {
        inOrder_help(leaf->left);
        cout << leaf->value << "\t";
        inOrder_help(leaf->right);
    }
}


// ------------------------------------------------
int main(int argc, const char * argv[])
{
    binarySearchTree T;             // Declare a binary search tree T
    int user_integer, user_search;  // integers entered by user
    bool find_integer;              // boolean value to check if an integer is in the tree
    
    // Storing integers in the tree until 0 or negative numbers is entered
    cout << "Please enter a positive integer:";
    cin >> user_integer;
    while (user_integer > 0) {
        T.insert(user_integer);
        cout << "\nPlease enter a positive integer:";
        cin >> user_integer;
    }
    
    // search for integers in the tree until 0 or negative numbers is entered
    cout << "\n\nEnter a positive integer to search in the tree:";
    cin >> user_search;
    while (user_search > 0) {
        find_integer = T.search(user_search);
        if (find_integer)
            cout << "Find: " << user_search << " in the tree.";
        else
            cout << "Cannot find: " << user_search << " in the tree.";
        cout << "\n\nEnter a positive integer to search in the tree:";
        cin >> user_search;
    }
    
    // call function to print out the elements in the tree
    T.inOrderTraversal();
    
    return 0;
}

