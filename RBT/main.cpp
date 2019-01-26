#include "RedBlackTree.h"
#include <iostream>

using namespace std;

int main(){
    RedBlackTree *tree = new RedBlackTree();
    int keys[] = {1,2,3,4,5,6,7};

    for(uint i=0; i<sizeof(keys)/sizeof(int); ++i){
        tree->insert(new RedBlackTreeNode(keys[i]));
    }

    tree->print_tree();

    // int del[] = {4, 5, 6};
    // for(uint i=0; i<sizeof(del)/sizeof(int); ++i){
    //     tree->remove(del[i]);
    // }

    // tree->print_tree();

    return 0;
}
/*
    2
1         4
       5         6
                    7   
*/