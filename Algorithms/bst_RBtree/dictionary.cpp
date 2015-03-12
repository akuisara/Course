//
//  dictionary.cpp
//  lab_program
//
//  Created by Qi Zhang on 11/12/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#include "dictionary.h"
#include <fstream>
#include <sstream>

dictionary::dictionary (searchTree *d) {
    dict = d;
}

dictionary::~dictionary(){
    delete dict;
}

string dictionary::search(string s) {

    cout << s << endl;
    
    if (dict == NULL) {
        cout << "Empty dictionary." << endl;
    }
    
    treeNode *p = dict->search(s);
    if (p == NULL) {
        cout << "The word " << s << " is was not found in the dictionary." << endl;
    }else{
        cout << p->data->getWord() << ": " << p->data->getDefinition() << endl;
    }
    return s;
}

void dictionary::add(dictEntry *d) {
    dict->insert(d);
    cout << "Inserted successfully." << endl;
}

void dictionary::remove(string s) {
    for(int i=0;s.c_str()[i]!='\0';i++)
        s[i]=toupper(s[i]);
    
    dict->remove(s);
    cout << "Removed successfully." << endl;
}

dictionary* dictionary::readFile(dictionary *tree, string filename){
    ifstream input_file;
    input_file.open(filename);
    
    if (!input_file.is_open())
    {  //exit if cannot open the file
        cout<<"Exit";
        exit(-1);
    }
    
    string a_line, a_word, a_definition;
    string delimiter = ": ";
    size_t pos = 0;
    dictEntry *A;
    int count = 0;
    while (!input_file.eof()) {
        getline(input_file, a_line, '\n');
        
        // Skip blank lines
        if((a_line.length() != 0) && (a_line.length() != 1)){
            pos = a_line.find(delimiter);
            
            a_word = a_line.substr(0, pos);
            
            a_definition = a_line.erase(0, pos + delimiter.length());
            
            A = new dictEntry(a_word, a_definition);
            
            cout << count << '\t' << a_word<< endl;
            cout << a_definition << endl;
            
            tree->add(A);
            
            delete A;
            A = NULL;
            
            pos = 0;
            
            cout << endl;
            count++;
        }
    }
    input_file.close();
    
    return tree;
}

void dictionary::writeFilePreorder(string filename) {
    dict->preOrder(filename);
}

void dictionary::writeFileInorder(string filename){
    dict->inOrder(filename);
}

void dictionary::writeFilePostorder(string filename) {
    dict->postOrder(filename);
}