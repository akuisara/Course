//
//  RBsearchTreeNode.h
//  lab_program
//
//  Created by Qi Zhang on 11/5/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#ifndef __lab_program__RBsearchTreeNode__
#define __lab_program__RBsearchTreeNode__

#include <iostream>
#include "treeNode.h"

class RBsearchTreeNode: public treeNode {
public:
    RBsearchTreeNode *left, *right, *parent;
    enum RBcolor {RED, BLACK};
    RBcolor color;
    RBsearchTreeNode(dictEntry *d, RBcolor color);
    RBsearchTreeNode(dictEntry *d, RBsearchTreeNode *p, RBcolor color);
    RBsearchTreeNode(dictEntry *d, RBsearchTreeNode *l, RBsearchTreeNode *r, RBsearchTreeNode *p, RBcolor color);
    
    RBsearchTreeNode* successor(RBsearchTreeNode *n);
};

#endif /* defined(__lab_program__RBsearchTreeNode__) */
