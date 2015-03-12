//
//  RBSearchTree.cpp
//  lab_program
//
//  Created by Qi Zhang on 11/12/14.
//  Copyright (c) 2014 QZ. All rights reserved.
//

#include "RBSearchTree.h"
#include <queue>

RBSearchTree::RBSearchTree() {
    root = NULL;
}

RBSearchTree::~RBSearchTree(){
    destroy_tree(root);
}

void RBSearchTree::destroy_tree(RBsearchTreeNode *leaf)
{ // This is the helper function of destructor
    // PRE: a node is assigned
    if (leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void RBSearchTree::rotate_left(RBsearchTreeNode *x){
    RBsearchTreeNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBSearchTree::rotate_right(RBsearchTreeNode *x){
    RBsearchTreeNode *y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

RBsearchTreeNode* RBSearchTree::uncle(RBsearchTreeNode *z){
    if (z->parent != NULL) {
        RBsearchTreeNode *p = z->parent;
        if (p->parent != NULL) {
            RBsearchTreeNode *g = p->parent;
            if (p == g->left) {
                return g->right;
            }else
                return g->left;
        }
    }
    return NULL;
}

RBsearchTreeNode* RBSearchTree::sibling(RBsearchTreeNode *n){
    if (n == NULL) {
        return NULL;
    }else if (n->parent == NULL){
        return NULL;
    }else if (n == n->parent->left){
        return n->parent->right;
    }else
        return n->parent->left;
}

void RBSearchTree::insert_fixup(RBsearchTreeNode *n){
    RBsearchTreeNode *p, *g, *u, *swapper;
    if (n->parent == NULL) {
        n->color = RBsearchTreeNode::BLACK;
    }else if (n->parent->color == RBsearchTreeNode::BLACK){}
    else{
        p = n->parent;
        g = p->parent;
        u = uncle(n);
        if ((u == NULL) || (u->color == RBsearchTreeNode::BLACK)) {
            if ((n == p->right) && (p == g->left)) {
                rotate_left(p);
                //swap(p, n);
                swapper = p;
                p = n;
                n = swapper;
            }
            if ((n == p->left) && (p == g->right)) {
                rotate_right(p);
                //swap(p, n);
                swapper = p;
                p = n;
                n = swapper;
            }
            p->color = RBsearchTreeNode::BLACK;
            g->color = RBsearchTreeNode::RED;
            if (n == p->left) {
                rotate_right(g);
            }else
                rotate_left(g);
        }else {
            u->color = RBsearchTreeNode::BLACK;
            p->color = RBsearchTreeNode::BLACK;
            g->color = RBsearchTreeNode::RED;
            insert_fixup(g);
        }
    }
}

void RBSearchTree::insert(dictEntry* d){
    RBsearchTreeNode *z;
    if (root == NULL) {
        root = new RBsearchTreeNode(d, RBsearchTreeNode::BLACK);
        z = root;
    }else {
        z = insert_h(d, root);
    }
    if (z != NULL) {
        insert_fixup(z);
    }
}

RBsearchTreeNode* RBSearchTree::search(string w) {
    return search_h(w, root);
}

void RBSearchTree::remove(string w) {
    RBsearchTreeNode *z = search(w), *y;
    if (z == NULL) {}
    if ((z->left == NULL) || (z->right == NULL)) {
        y = z;
    }else {
        y = z->successor(z);
        z->data = y->data;
    }
    
    if (y->left != NULL) {
        y->data = y->left->data;
        delete y->left;
        y->left = NULL;
    }
    if (y->right != NULL) {
        y->data = y->right->data;
        delete y->right;
        y->right = NULL;
    }
    
    if (y->color == RBsearchTreeNode::BLACK) {
        remove_fixup(y);
    }
    if (y->parent == NULL) {
        root = NULL;
    }else if (y == y->parent->left){
        y->parent->left = NULL;
    }else
        y->parent->right = NULL;
    delete y;
}

void RBSearchTree::preOrder(string filename) {
    fout.open(filename);
    if (!fout.is_open())
    {  //exit if cannot open the file
        cout<<"Exit";
        exit(-1);
    }
    preOrder_h(root);
    fout.close();
}

void RBSearchTree::postOrder(string filename) {
    fout.open(filename);
    if (!fout.is_open())
    {  //exit if cannot open the file
        cout<<"Exit";
        exit(-1);
    }
    postOrder_h(root);
    fout.close();
}

void RBSearchTree::inOrder(string filename) {
    fout.open(filename);
    if (!fout.is_open())
    {  //exit if cannot open the file
        cout<<"Exit";
        exit(-1);
    }
    inOrder_h(root);
    fout.close();
}

RBsearchTreeNode* RBSearchTree::insert_h(dictEntry *d, RBsearchTreeNode *n) {
    if ((n->left != NULL) && (d->getWord() < n->left->data->getWord())) {
        return insert_h(d, n->left);
    }else if ((d->getWord() < n->data->getWord())){
        n->left = new RBsearchTreeNode(d, n, n->color);
        n->left->data->updateDefinition(d->getDefinition());
        return n->left;
    }else if ((n->right != NULL) && (d->getWord() > n->right->data->getWord())){
        return insert_h(d, n->right);
    }else if ((d->getWord() > n->data->getWord())){
        n->right = new RBsearchTreeNode(d, n, n->color);
        n->right->data->updateDefinition(d->getDefinition());
        return n->right;
    }else
        return NULL;
}

RBsearchTreeNode* RBSearchTree::search_h(string w, RBsearchTreeNode *current) {
    if (current == NULL)
        return NULL;
    else if (((current->data)->getWord()) == w)
        return current;
    else if ((current->data->getWord()) > w)
        return search_h(w, current->left);
    else
        return search_h(w, current->right);
}

void RBSearchTree::remove_fixup(RBsearchTreeNode *n) {
    if (n->parent == NULL) {}
    
    RBsearchTreeNode *s = sibling(n);
    
    if (s->color == RBsearchTreeNode::RED) {
        n->parent->color = RBsearchTreeNode::RED;
        s->color = RBsearchTreeNode::BLACK;
        if (n == n->parent->left) {
            rotate_left(n->parent);
        }else
            rotate_right(n->parent);
        s = sibling(n);
    }
    
    if ((n == n->parent->left) && (s->right->color == RBsearchTreeNode::BLACK) && (s->left->color == RBsearchTreeNode::RED)) {
        s->color = RBsearchTreeNode::RED;
        s->left->color = RBsearchTreeNode::BLACK;
        rotate_right(s);
    } else if ((n == n->parent->right) && (s->left->color == RBsearchTreeNode::BLACK) && (s->right->color == RBsearchTreeNode::RED)) {
        s->color = RBsearchTreeNode::RED;
        s->right->color = RBsearchTreeNode::BLACK;
        rotate_left(s);
    }
    
    if ((n == n->parent->left) && (s->right->color == RBsearchTreeNode::RED)) {
        s->color = n->parent->color;
        n->parent->color = RBsearchTreeNode::BLACK;
        n->right->color = RBsearchTreeNode::BLACK;
        rotate_left(n->parent);
    }
    
    if ((n == n->parent->right) && (s->left->color == RBsearchTreeNode::RED)) {
        s->color = n->parent->color;
        n->parent->color = RBsearchTreeNode::BLACK;
        n->left->color = RBsearchTreeNode::BLACK;
        rotate_right(n->parent);
    }
}

void RBSearchTree::preOrder_h(RBsearchTreeNode *n) {
    if (n != NULL) {
        preOrder_h(n->left);
        visit(n);
        preOrder_h(n->right);
    }
}

void RBSearchTree::postOrder_h(RBsearchTreeNode *n) {
    if (n != NULL) {
        postOrder_h(n->right);
        visit(n);
        postOrder_h(n->left);
    }
}

void RBSearchTree::inOrder_h(RBsearchTreeNode *n) {
    queue<RBsearchTreeNode*> Q;
    Q.push(n);
    while (!Q.empty()) {
        RBsearchTreeNode *current = Q.front();
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

void RBSearchTree::visit(RBsearchTreeNode* n) {
    string def = n->data->getDefinition();
    size_t def_len = def.length();
    char ch = def.back();
    // Check if the last character is a newline;
    if (ch == '\r') {
        def = def.erase(def_len-1, def_len);
    }
    
    fout << "[" << n->data->getWord() << "]: [" << def << "]\n\n";}