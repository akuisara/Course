//
//  dictionary.h
//  lab_program
//
//  Created by Qi Zhang on 11/12/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#ifndef __lab_program__dictionary__
#define __lab_program__dictionary__

#include <iostream>
#include "searchTree.h"

class dictionary {
protected:
    searchTree *dict;
    
public:
    dictionary(searchTree *d);
    ~dictionary();
    string search(string);
    void add(dictEntry*);
    void remove(string);
    dictionary* readFile(dictionary*, string);
    void writeFilePreorder(string);
    void writeFileInorder(string);
    void writeFilePostorder(string);
};

#endif /* defined(__lab_program__dictionary__) */
