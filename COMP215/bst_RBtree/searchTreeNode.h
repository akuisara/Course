//
//  searchTreeNode.h
//  lab_program
//
//  Created by Qi Zhang on 11/5/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#ifndef lab_program_searchTreeNode_h
#define lab_program_searchTreeNode_h

#include "treeNode.h"

class searchTreeNode: public treeNode {
public:
    searchTreeNode *left, *right, *parent;
    
    searchTreeNode(dictEntry *d);
    searchTreeNode(dictEntry *d, searchTreeNode *p);
    searchTreeNode(dictEntry *d, searchTreeNode *l, searchTreeNode *r, searchTreeNode *p);
    
    searchTreeNode* successor(searchTreeNode *n);
};


#endif
