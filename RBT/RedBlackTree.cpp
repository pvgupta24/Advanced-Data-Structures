#include "RedBlackTree.h"
#include <limits.h>
#include <iostream>

using namespace std;

RedBlackTreeNode *RedBlackTree::nil = new RedBlackTreeNode(INT_MIN, nullptr, nullptr, nullptr);

/**
 * Initializes root node and nil node
 */ 
void RedBlackTree::initialize(){
    // this->nil = new RedBlackTreeNode(INT_MIN, nullptr, nullptr, nullptr);
    (this->nil)->left = (this->nil)->right = (this->nil)->parent = this->nil;
    
    // this->root = new RedBlackTreeNode(INT_MIN, nullptr, nullptr, nullptr);
    // (this->root)->left = (this->root)->right = (this->root)->parent = this->nil;

    this->root = this->nil;
}

void RedBlackTree::left_rotate(RedBlackTreeNode *x){
    RedBlackTreeNode *y = x->right;
    x->right = y->left;

    if(y->left != this->nil)
        y->left->parent = x;

    y->parent = x->parent;
    if(x->parent == this->nil)
        this->root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void RedBlackTree::right_rotate(RedBlackTreeNode *x){
    RedBlackTreeNode *y = x->left;
    x->left = y->right;

    if(y->right != this->nil)
        y->right->parent = x;
    
    y->parent = x->parent;    
    if(x->parent == this->nil)
        this->root = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void RedBlackTree::insert(RedBlackTreeNode *z){
    RedBlackTreeNode *x = this->root;
    RedBlackTreeNode *y = this->nil;

    while(x != this->nil){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;

    if(y == this->nil)
        this->root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = z->right = this->nil;
    z->colour = RED;
    this->insert_fixup(z);
}

/**
 * Ensures that red black tree properties are preserved after insertion
 */ 
void RedBlackTree::insert_fixup(RedBlackTreeNode *z){
    while(z->parent->colour == RED){
        if(z->parent == z->parent->parent->left){
            RedBlackTreeNode *y = z->parent->parent->right;
            if(y->colour == RED){
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    this->left_rotate(z);
                }
                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                this->right_rotate(z->parent->parent);
            }
        }
        else{
            RedBlackTreeNode *y = z->parent->parent->left;
            if(y->colour == RED){
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    this->right_rotate(z);
                }
                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                this->left_rotate(z->parent->parent);
            }
        }
    }

    this->root->colour = BLACK;
    this->root->parent = this->nil;
}

void RedBlackTree::remove(RedBlackTreeNode *z){
    RedBlackTreeNode *x;
    RedBlackTreeNode *y = z;
    COLOUR y_original_colour = y->colour;

    if(z->left == this->nil){
        x = z->right;
        this->transplant(z, z->right);
    }
    else if(z->right == this->nil){
        x = z->left;
        this->transplant(z, z->left);
    }
    else{
        y = tree_minimum(z->right);
        y_original_colour = y->colour;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        }
        else{
            this->transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        this->transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->colour = z->colour;
    }

    delete z;

    if(y_original_colour == BLACK){
        this->remove_fixup(x);
    }
}

void RedBlackTree::transplant(RedBlackTreeNode *u, RedBlackTreeNode *v){
    if(u->parent == this->nil){
        this->root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    v->parent = u->parent;
}

RedBlackTreeNode *RedBlackTree::tree_minimum(RedBlackTreeNode *x)
{
    while (x->left != this->nil){
        x = x->left;
    }

    return x;
}

RedBlackTreeNode *RedBlackTree::tree_maximum(RedBlackTreeNode *x)
{
    while (x->right != this->nil){
        x = x->right;
    }

    return x;
}

void RedBlackTree::remove_fixup(RedBlackTreeNode *x){
    RedBlackTreeNode *w;
    while (x != this->root && x->colour == BLACK){
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->colour == RED){
                w->colour = BLACK;
                x->parent->colour = RED;
                this->left_rotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->colour == BLACK && w->right->colour == BLACK){
                w->colour = RED;
                x = x->parent;
            }
            else{ if(w->right->colour == BLACK){
                w->left->colour = BLACK;
                w->colour = RED;
                this->right_rotate(w);
                w = x->parent->right;
            }
            w->colour = x->parent->colour;
            x->parent->colour = BLACK;
            w->right->colour = BLACK;
            this->left_rotate(x->parent);
            x = this->root;}
        }
        else{
            w = x->parent->left;
            if(w->colour == RED){
                w->colour = BLACK;
                x->parent->colour = RED;
                this->right_rotate(x->parent);
                w = x->parent->left;
            }
            if(w->right->colour == BLACK && w->left->colour == BLACK){
                w->colour = RED;
                x = x->parent;
            }
            else{ if(w->left->colour == BLACK){
                w->right->colour = BLACK;
                w->colour = RED;
                this->left_rotate(w);
                w = x->parent->left;
            }
            w->colour = x->parent->colour;
            x->parent->colour = BLACK;
            w->left->colour = BLACK;
            this->right_rotate(x->parent);
            x = this->root;}
        }
    }

    x->colour = BLACK; 
}

RedBlackTreeNode *RedBlackTree::search(int key){
    RedBlackTreeNode *x = this->root;

    while(x != this->nil){
        if(x->key == key)
            return x;
        else if(x->key < key)
            x = x->right;
        else
            x = x->left;
    }

    return this->nil;
}

bool RedBlackTree::remove(int key){
    RedBlackTreeNode *x = this->search(key);

    if(x == this->nil)
        return false;
    
    this->remove(x);

    return true;
}

void RedBlackTree::preorder(RedBlackTreeNode *node){
    if(node != this->nil){
        cout << ((node->colour == BLACK) ? FORE_BLU : FORE_RED) << node->key << RESET;
        cout << " ( ";
        this->preorder(node->left);
        cout << ", ";
        this->preorder(node->right);
        cout << ")";
    }
}

void RedBlackTree::inorder(RedBlackTreeNode *node){
    if(node != this->nil){
        this->inorder(node->left);
        cout << ((node->colour == BLACK) ? FORE_BLU : FORE_RED) << node->key <<" "<< RESET;
        this->inorder(node->right);
    }
}

void RedBlackTree::print_tree(int type){
    switch (type)
    {
        case INORDER:
            this->inorder(this->root);
            break;
        case PREORDER:
            this->preorder(this->root);
            break;
    }
    cout << endl;
}

int RedBlackTree::get_black_height(){
    RedBlackTreeNode *x = this->root;
    int black_height = 0;

    while(x!=this->nil){
        if(x->colour == BLACK)
            black_height++;
        
        x = x->right;
    }

    return black_height;
}

void RedBlackTree::insert_colour(RedBlackTreeNode *newNode) {
    RedBlackTreeNode *y;
    RedBlackTreeNode *x;

    x = newNode;
    x->colour = RED;
    while (x->parent->colour == RED) {
        if (x->parent == x->parent->parent->left) {
            y = x->parent->parent->right;
            if (y->colour == RED) {
                x->parent->colour = BLACK;
                y->colour = BLACK;
                x->parent->parent->colour = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                x = x->parent;
                this->left_rotate(x);
                }
                x->parent->colour = BLACK;
                x->parent->parent->colour = RED;
                this->right_rotate(x->parent->parent);
            }
        } else {
            y = x->parent->parent->left;
            if (y->colour == RED) {
                x->parent->colour = BLACK;
                y->colour = BLACK;
                x->parent->parent->colour = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                x = x->parent;
                this->right_rotate(x);
                }
                x->parent->colour = BLACK;
                x->parent->parent->colour = RED;
                this->left_rotate(x->parent->parent);
            }
        }
    }
    root->left->colour = BLACK;

    return;
}