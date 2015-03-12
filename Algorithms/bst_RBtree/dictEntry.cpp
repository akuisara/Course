//
//  dictEntry.cpp
//  lab_program
//
//  Created by Qi Zhang on 11/5/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#include "dictEntry.h"

dictEntry::dictEntry() {
    word = "";
    definition = "";
}

dictEntry::dictEntry(string w, string d) {
    word = w;
    definition = d;
}

dictEntry::~dictEntry() {
    word = "";
    definition = "";
}

string dictEntry::getWord(){
    return word;
}

string dictEntry::getDefinition() {
    return definition;
}

void dictEntry::updateDefinition(string def) {
    definition = def;
}

bool dictEntry::operator==(string const &x){
    if (strcmp (this->word.c_str(),x.c_str()) == 0) {
        return true;
    } else
        return false;
}

bool dictEntry::operator<(string const &x){
    if (strcmp (this->word.c_str(),x.c_str()) < 0) {
        return true;
    } else
        return false;
}

bool dictEntry::operator>(string const &x){
    if (strcmp (this->word.c_str(),x.c_str()) > 0) {
        return true;
    } else
        return false;
}

bool dictEntry::operator>=(string const &x){
    if (strcmp (this->word.c_str(),x.c_str()) >= 0) {
        return true;
    } else
        return false;
}

bool dictEntry::operator<=(string const &x){
    if (strcmp (this->word.c_str(),x.c_str()) <= 0) {
        return true;
    } else
        return false;
}