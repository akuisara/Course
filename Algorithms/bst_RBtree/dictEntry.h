//
//  dictEntry.h
//  lab_program
//
//  Created by Qi Zhang on 11/5/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#ifndef lab_program_dictEntry_h
#define lab_program_dictEntry_h
#include <iostream>
using namespace std;

class dictEntry {
protected:
    string word = "";
    string definition = "";
public:
    dictEntry();
    ~dictEntry();
    dictEntry(string w, string d);
    string getDefinition();
    string getWord();
    void updateDefinition(string def);
    bool operator==(string const &x);
    bool operator>(string const &x);
    bool operator<(string const &x);
    bool operator>=(string const &x);
    bool operator<=(string const &x);
};


#endif
