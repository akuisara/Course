//
//  RBsearchTreeNode.cpp
//  lab_program
//
//  Created by Qi Zhang on 11/5/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#include "RBsearchTreeNode.h"
using namespace std;

RBsearchTreeNode::RBsearchTreeNode(dictEntry *d, RBcolor color){
    data = new dictEntry(d->getWord(), d->getDefinition());
    left = NULL;
    right = NULL;
    parent = NULL;
    color = RED;
}

RBsearchTreeNode::RBsearchTreeNode(dictEntry *d, RBsearchTreeNode *p, RBcolor color) {
    data = new dictEntry(d->getWord(), d->getDefinition());
    left = NULL;
    right = NULL;
    parent = p;
    color = RED;
}

RBsearchTreeNode::RBsearchTreeNode(dictEntry *d, RBsearchTreeNode *l, RBsearchTreeNode *r, RBsearchTreeNode *p, RBcolor color){
    data = new dictEntry(d->getWord(), d->getDefinition());
    left = l;
    right = r;
    parent = p;
    color = RED;
}

RBsearchTreeNode* RBsearchTreeNode::successor(RBsearchTreeNode *n){
    if (n == NULL) {
        return NULL;
    } else if (n->right == NULL) {
        return NULL;
    } else {
        RBsearchTreeNode *current = n->right;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }
}