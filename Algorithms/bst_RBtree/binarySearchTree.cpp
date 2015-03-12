//
//  binarySearchTree.cpp
//  lab_program
//
//  Created by Qi Zhang on 11/5/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#include "binarySearchTree.h"
#include <queue>

binarySearchTree::binarySearchTree() {
    root = NULL;
}

binarySearchTree::~binarySearchTree()
{ // Destructor
    destroy_tree(root);
}

void binarySearchTree::destroy_tree(searchTreeNode *leaf)
{ // This is the helper function of destructor
    // PRE: a node is assigned
    if (leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void binarySearchTree::insert(dictEntry *d){
    if (root == NULL) {
        root = new searchTreeNode(d, NULL, NULL, NULL);
    }
    else
        insert_h(d, root);
}

searchTreeNode* binarySearchTree::search(string w) {
    return search_h(w, root);
}

void binarySearchTree::remove(string w) {
    searchTreeNode *todelete = search(w);
    if (todelete != NULL) {
        if (todelete->parent != NULL) {
            if(todelete->left == NULL) {
                if (todelete == todelete->parent->left) {
                    todelete->parent->left = todelete->right;
                    delete todelete;
                } else {
                    todelete->parent->right = todelete->right;
                    delete todelete;
                }
            } else if (todelete->right == NULL) {
                if (todelete == todelete->parent->left) {
                    todelete->parent->left = todelete->left;
                    delete todelete;
                } else {
                    todelete->parent->right = todelete->left;
                    delete todelete;
                }
            } else {
                searchTreeNode *todeleteSucc = todelete->successor(todelete);
                todelete->data = todeleteSucc->data;
                if (todelete == todelete->parent->left) {
                    todelete->parent->left = todelete->right;
                    delete todelete;
                } else {
                    todelete->parent->right = todelete->right;
                    delete todelete;
                }
            }
        } else {
            if((todelete->left == NULL) && (todelete->right == NULL)) {
                root = NULL;
                delete todelete;
            } else if ((todelete->left == NULL) || (todelete->right == NULL)) {
                if (todelete->left == NULL) {
                    root = todelete->right;
                    delete todelete;
                } else {
                    root = todelete->left;
                    delete todelete;
                }
            } else {
                searchTreeNode *todeleteSucc = todelete->successor(todelete);
                todelete->data = todeleteSucc->data;
                if (todelete == todelete->parent->left) {
                    todelete->parent->left = todelete->right;
                    delete todelete;
                } else {
                    todelete->parent->right = todelete->right;
                    delete todelete;
                }
            }
        }
    }
}

void binarySearchTree::preOrder(string filename) {
    fout.open(filename);
    if (!fout.is_open())
    {  //exit if cannot open the file
        cout<<"Exit";
        exit(-1);
    }
    preOrder_h(root);
    fout.close();
}

void binarySearchTree::postOrder(string filename) {
    fout.open(filename);
    if (!fout.is_open())
    {  //exit if cannot open the file
        cout<<"Exit";
        exit(-1);
    }
    postOrder_h(root);
    fout.close();
}

void binarySearchTree::inOrder(string filename) {
    fout.open(filename);
    if (!fout.is_open())
    {  //exit if cannot open the file
        cout<<"Exit";
        exit(-1);
    }
    inOrder_h(root);
    fout.close();
}

void binarySearchTree::insert_h(dictEntry *d, searchTreeNode *current) {
    if (d->getWord() == current->data->getWord()){}
    else if (d->getWord() < current->data->getWord()){
        if (current->left == NULL) {
            current->left = new searchTreeNode(d, NULL, NULL, current);
            current->left->data->updateDefinition(d->getDefinition());
        } else {
            insert_h(d, current->left);
        }
    } else {
        if (current->right == NULL) {
            current->right = new searchTreeNode(d, NULL, NULL, current);
            current->right->data->updateDefinition(d->getDefinition());
        } else {
            insert_h(d, current->right);
        }
    }
}

searchTreeNode* binarySearchTree::search_h(string w, searchTreeNode *current) {
    if (current == NULL)
        return NULL;
    else if (((current->data)->getWord()) == w)
        return current;
    else if ((current->data->getWord()) > w)
        return search_h(w, current->left);
    else
        return search_h(w, current->right);
}

void binarySearchTree::preOrder_h(searchTreeNode *n) {
    if (n != NULL) {
        preOrder_h(n->left);
        visit(n);
        preOrder_h(n->right);
    }
}

void binarySearchTree::postOrder_h(searchTreeNode *n) {
    if (n != NULL) {
        postOrder_h(n->right);
        visit(n);
        postOrder_h(n->left);
    }
}

void binarySearchTree::inOrder_h(searchTreeNode *n) {
    queue<searchTreeNode*> Q;
    Q.push(n);
    while (!Q.empty()) {
        searchTreeNode *current = Q.front();
        Q.pop();
        visit(current);
        if (current->left != NULL) {
            Q.push(current->left);
        }
        if (current->right != NULL) {
            Q.push(current->right);
        }
    }
}

void binarySearchTree::visit(searchTreeNode* n) {
    string def = n->data->getDefinition();
    size_t def_len = def.length();
    char ch = def.back();
    // Check if the last character is a newline;
    if (ch == '\r') {
        def = def.erase(def_len-1, def_len);
    }
    
    fout << "[" << n->data->getWord() << "]: [" << def << "]\n\n";
}