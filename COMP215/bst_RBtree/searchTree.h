//
//  searchTree.h
//  lab_program
//
//  Created by Qi Zhang on 11/5/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#ifndef lab_program_searchTree_h
#define lab_program_searchTree_h

#include "searchTreeNode.h"

class searchTree {
public:
    virtual void insert(dictEntry*) = 0;
    virtual treeNode* search(string) = 0;
    virtual void remove(string) = 0;
    virtual void preOrder(string) = 0;
    virtual void postOrder(string) = 0;
    virtual void inOrder(string) = 0;
    virtual ~searchTree(){};
};

#endif
