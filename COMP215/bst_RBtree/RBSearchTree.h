//
//  RBSearchTree.h
//  lab_program
//
//  Created by Qi Zhang on 11/12/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#ifndef __lab_program__RBSearchTree__
#define __lab_program__RBSearchTree__

#include <iostream>
#include <fstream>
#include "searchTree.h"
#include "RBsearchTreeNode.h"

class RBSearchTree : public searchTree {
protected:
    RBsearchTreeNode *root;
    ofstream fout;
    
    void destroy_tree(RBsearchTreeNode *leaf);
    RBsearchTreeNode* insert_h(dictEntry*, RBsearchTreeNode *current);
    RBsearchTreeNode* search_h(string w, RBsearchTreeNode *current);
    
    void preOrder_h(RBsearchTreeNode*);
    void postOrder_h(RBsearchTreeNode*);
    void inOrder_h(RBsearchTreeNode*);
    void visit(RBsearchTreeNode*);
    
    void rotate_left(RBsearchTreeNode *x);
    void rotate_right(RBsearchTreeNode *x);
    RBsearchTreeNode* uncle(RBsearchTreeNode *n);
    RBsearchTreeNode* sibling(RBsearchTreeNode *n);
    void insert_fixup(RBsearchTreeNode *n);
    void remove_fixup(RBsearchTreeNode *n);

public:
    RBSearchTree();
    ~RBSearchTree();
    virtual void insert(dictEntry*);
    virtual RBsearchTreeNode* search(string w);
    virtual void remove(string w);
    virtual void preOrder(string filename);
    virtual void postOrder(string filename);
    virtual void inOrder(string filename);
};

#endif /* defined(__lab_program__RBSearchTree__) */
