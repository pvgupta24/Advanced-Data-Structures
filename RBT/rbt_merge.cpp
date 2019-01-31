#include "RedBlackTree.h"
#include <iostream>

using namespace std;

/**
 * Merges a redblack tree l with smaller red black height and smaller keys in
 * another redblack tree r.
 * 
 * Extract max element from l, find a node by traversing the left spine of r whose
 * red black height is same as root of l and replace it.
 * Then fix the violated red black tree properties
 * 
 */ 
RedBlackTree *merge_in_left(RedBlackTree *l, RedBlackTree *r){
    RedBlackTreeNode *root_l = l->GetRoot();

    // Extracting maximum element from l
    RedBlackTreeNode *max_l = l->tree_maximum(root_l);
    int max_key_l = max_l->key;
    l->remove(max_l);
    root_l = l->GetRoot();

    // Red Black heights of roots of the trees
    int black_height_l = l->get_black_height();
    int black_height_r = r->get_black_height();

    // Traverse on left spine of r till a node with same black is found
    RedBlackTreeNode *node_r = r->GetRoot();
    while(node_r != r->GetNil() && black_height_r > 1 + black_height_l){
        if(node_r->colour == BLACK){
            black_height_r--;
        }
        node_r = node_r ->left;
    }

    // Orignal left node in r to be replaced by maximum node of l
    RedBlackTreeNode *prev_l_child = node_r->left;

    // Outward connections of new node
    RedBlackTreeNode *new_l_child 
        = new RedBlackTreeNode(max_key_l, node_r, root_l, prev_l_child, RED);

    // Inward connections of new node
    prev_l_child->parent = root_l->parent = node_r->left = new_l_child;

    // Fix violated red black tree Properties
    RedBlackTreeNode *parent = new_l_child->parent;
    RedBlackTreeNode *sibling = node_r->right;

    if (parent != r->GetRoot())
    {
        if (sibling->colour == RED)
        {
            sibling->colour = BLACK;
            new_l_child->colour = BLACK;
            parent->colour = RED;
            r->insert_colour(parent);
        }
        else
        {
            if (new_l_child->right->colour == RED)
            {
                new_l_child->parent->colour = RED;
                new_l_child->right->colour = BLACK;
                r->left_rotate(new_l_child);
                r->right_rotate(parent);
            }
        }
    }   
    return r;
}


RedBlackTree *merge_in_right(RedBlackTree *l, RedBlackTree *r){
    RedBlackTreeNode *root_l = l->GetRoot();
    RedBlackTreeNode *max_l = l->tree_minimum(root_l);
    int max_key_l = max_l->key;
    l->remove(max_l);
    root_l = l->GetRoot();

    int black_height_l = l->get_black_height();
    int black_height_r = r->get_black_height();

    RedBlackTreeNode *node_r = r->GetRoot();
    while(node_r != r->GetNil() && black_height_r > 1 + black_height_l){
        if(node_r->colour == BLACK){
            black_height_r--;
        }
        node_r = node_r ->right;
    }

    RedBlackTreeNode *prev_l_child = node_r->right;

    RedBlackTreeNode *new_l_child 
        = new RedBlackTreeNode(max_key_l, node_r, prev_l_child, root_l, RED);
    prev_l_child->parent = root_l->parent = node_r->right = new_l_child;

    // Fix Properties
    RedBlackTreeNode *parent = new_l_child->parent;
    RedBlackTreeNode *sibling = node_r->left;
    if (parent != r->GetRoot())
    {
        if (sibling->colour == RED)
        {
            sibling->colour = BLACK;
            new_l_child->colour = BLACK;
            parent->colour = RED;
            r->insert_colour(parent);
        }
        else
        {
            if (new_l_child->left->colour == RED)
            {
                new_l_child->parent->colour = RED;
                new_l_child->left->colour = BLACK;
                r->right_rotate(new_l_child);
                r->left_rotate(parent);
            }
        }
    }   
    return r;
}

int main(){

    // Tree with smaller elements
    RedBlackTree *root_1 = new RedBlackTree();
    // Tree with larger elements
    RedBlackTree *root_2 = new RedBlackTree();

    // Merged tree
    RedBlackTree *root_3 = NULL;

    int n, m;
    cin >> n >> m;
    int a1, insert_val;
    for( a1 = 0 ; a1 < n ; ++a1 ) {
        cin >> insert_val;
        root_1->insert(new RedBlackTreeNode(insert_val));
    }

    for( a1 = 0 ; a1 < m ; ++a1 ) {
        cin >> insert_val;
        root_2->insert(new RedBlackTreeNode(insert_val));
    }

    cout << "Red Black tree 1:" << endl;
    root_1->print_tree();

    cout << endl;
    cout << "Red Black tree 2:" << endl;
    root_2->print_tree();

    if(n > m){
        if(root_1->GetRoot()->key > root_2->GetRoot()->key)
            root_3 = merge_in_left(root_2, root_1);
        else
            root_3 = merge_in_right(root_2, root_1);
    }else{
        if(root_1->GetRoot()->key > root_2->GetRoot()->key)
            root_3 = merge_in_left(root_1, root_2);
        else
            root_3 = merge_in_right(root_1, root_2);
    }

    cout << endl;
    cout << "Merged Tree is:" << endl;
    root_3->print_tree();
    cout << endl;

    return 0;
}