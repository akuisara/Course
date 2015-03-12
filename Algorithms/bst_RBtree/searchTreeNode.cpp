//
//  searchTreeNode.cpp
//  lab_program
//
//  Created by Qi Zhang on 11/5/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#include "searchTreeNode.h"


searchTreeNode::searchTreeNode(dictEntry *d){
    data = new dictEntry(d->getWord(), d->getDefinition());
    left = NULL;
    right = NULL;
    parent = NULL;
};

searchTreeNode::searchTreeNode(dictEntry *d, searchTreeNode *p) {
    data = new dictEntry(d->getWord(), d->getDefinition());
    left = NULL;
    right = NULL;
    parent = p;
}

searchTreeNode::searchTreeNode(dictEntry *d, searchTreeNode *l, searchTreeNode *r, searchTreeNode *p){
    data = new dictEntry(d->getWord(), d->getDefinition());
    left = l;
    right = r;
    parent = p;
}

searchTreeNode* searchTreeNode::successor(searchTreeNode *n){
    if (n == NULL) {
        return NULL;
    } else if (n->right == NULL) {
        return NULL;
    } else {
        searchTreeNode *current = n->right;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }
}