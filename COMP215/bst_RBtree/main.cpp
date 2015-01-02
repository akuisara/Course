//
//  main.cpp
//  Project 1
//
//  Created by Qi Zhang on 9/24/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "binarySearchTree.h"
#include "RBSearchTree.h"
#include "dictionary.h"

using namespace std;

void menu(dictionary *tree, string);

int main(int argc, const char * argv[])
{
    string choice;
    cout << "1. Binary Search Tree.\n2. Red-Black Tree\n" << "Choose a tree from 1 and 2: ";
    cin >> choice;
    
    string option;
    
    if (atoi(choice.c_str()) == 1) {
        
        binarySearchTree *a = new binarySearchTree();
        dictionary *tree = new dictionary(a);
        cout << "\nMenu\n-----------\n" << "1. Read a file.\n" << "2. Manually add an entry.\n" <<
        "3. Search for a word in the dictionary.\n" << "4. Remove a word from the dictionary.\n" <<
        "5. Write the dictionary on file.\n" << "6. End the program.\nChoice: ";
        cin >> option;
        
        menu(tree, option);
        
    } else if (atoi(choice.c_str()) == 2) {
        
        RBSearchTree *b = new RBSearchTree();
        dictionary *tree = new dictionary(b);
        
        cout << "\nMenu\n-----------\n" << "1. Read a file.\n" << "2. Manually add an entry.\n" <<
        "3. Search for a word in the dictionary.\n" << "4. Remove a word from the dictionary.\n" <<
        "5. Write the dictionary on file.\n" << "6. End the program.\nChoice: ";
        cin >> option;
        
        menu(tree, option);
        
    } else {
        
        cout << "Invalid Input" << endl;
        exit(-1);
        
    }
    
    return 0;
}

void menu(dictionary *tree, string option) {
    while (atoi(option.c_str()) != 0) {
        string filename, word, definition;
        
        if (atoi(option.c_str()) == 1) {
            filename = "dictionary.txt";
            cout << "\nEnter file name: ";
            cin >> filename;
            tree->readFile(tree, filename);
        }else if (atoi(option.c_str()) == 2) {
            cout << "\nEnter a word: ";
            cin >> word;
            for(int i=0;word.c_str()[i]!='\0';i++)
                word[i]=toupper(word[i]);
            
            cout << "\nEnter the definition for " << word << ": \n";
            cin.ignore();
            getline(cin, definition);
            
            dictEntry *d = new dictEntry(word, definition);
            tree->add(d);
            delete d;
        }else if (atoi(option.c_str()) == 3) {
            cout << "\nEnter a word to search: ";
            cin >> word;
            for(int i=0;word.c_str()[i]!='\0';i++)
                word[i]=toupper(word[i]);
            
            tree->search(word);
        }else if (atoi(option.c_str()) == 4) {
            cout << "\nEnter a word to remove: ";
            cin >> word;
            tree->remove(word);
        }else if (atoi(option.c_str()) == 5) {
            filename = "dictionary_output.txt";
            string traversal_choice;
            cout << "\t1. Write the file in-order\n" <<
            "\t2. Write the file pre-order\n" <<
            "\t3. Write the file post-order\n";
            
            cout << "Please choose traversal function: ";
            
            cin >> traversal_choice;
            
            if (atoi(traversal_choice.c_str()) == 1) {
                tree->writeFileInorder(filename);
            } else if (atoi(traversal_choice.c_str()) == 2) {
                tree->writeFilePreorder(filename);
            } else if (atoi(traversal_choice.c_str()) == 3) {
                tree->writeFilePostorder(filename);
            }else {
                cout << "Invalid input\n";
                exit(-1);
            }

        }else if (atoi(option.c_str()) == 6) {
            cout << "Thanks for using!" << endl;
            exit(-1);
        }else {
            cout << "Invalid Input" << endl;
            exit(-1);
        }
        
        cout << "\nMenu\n-----------\n" << "1. Read a file.\n" << "2. Manually add an entry.\n" <<
        "3. Search for a word in the dictionary.\n" << "4. Remove a word from the dictionary.\n" <<
        "5. Write the dictionary on file.\n" << "6. End the program.\nChoice: ";
        cin >> option;
    }
}