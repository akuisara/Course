//
//  binarySearchTree.h
//  lab_program
//
//  Created by Qi Zhang on 11/5/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#ifndef lab_program_binarySearchTree_h
#define lab_program_binarySearchTree_h

#include "searchTree.h"
#include <fstream>

class binarySearchTree: public searchTree {
protected:
    searchTreeNode* root;
    ofstream fout;
    
    void destroy_tree(searchTreeNode *leaf);
    void insert_h(dictEntry*, searchTreeNode*);
    searchTreeNode* search_h(string w, searchTreeNode *current);
    void preOrder_h(searchTreeNode*);
    void postOrder_h(searchTreeNode*);
    void inOrder_h(searchTreeNode*);
    void visit(searchTreeNode*);
    
public:
    binarySearchTree();
    ~binarySearchTree();
    virtual void insert(dictEntry*);
    virtual searchTreeNode* search(string w);
    virtual void remove(string w);
    virtual void preOrder(string filename);
    virtual void postOrder(string filename);
    virtual void inOrder(string filename);
};

#endif
