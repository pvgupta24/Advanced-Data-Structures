/**
 * Implementation of red black trees
 * 
 * @author Praveen Gupta
 * @author Dibyadarshan Hota
 */

#define RESET  "\x1B[0m"
#define FORE_RED  "\x1B[31m"
#define FORE_BLU  "\x1B[34m"

#define SYMBOL_TICK "✓"
#define SYMBOL_CROSS "✘"


enum COLOUR {
    RED,
    BLACK,
    DOUBLE_BLACK
};

// template<typename T>
class RedBlackTreeNode{
public:
    int key;
    COLOUR colour;
    RedBlackTreeNode *left, *right, *parent;

public:
    RedBlackTreeNode(int key,
                    RedBlackTreeNode* parent,
                    RedBlackTreeNode* left,
                    RedBlackTreeNode* right,
                    COLOUR colour = BLACK)
    {
        this->key = key;
        this->colour = colour;
        this->left = left;
        this->right = right;
        this->parent = parent;
    }

    RedBlackTreeNode(int key){
        this->key = key;
        this->colour = RED;
        this->left = this->right = this->parent = nullptr;
    }
};

/**
 * 
1) Every node has a color either red or black.
2) Root of tree is always black.
3) There are no two adjacent red nodes (A red node cannot have a red parent or red child).
4) Every path from a node (including root) to any of its descendant NULL node has the same
    number of black nodes.

**/
// TODO: template<typename Key, typename Value>
class RedBlackTree
{
    RedBlackTreeNode *root;
    static RedBlackTreeNode *nil;

public:
    RedBlackTree(){
        initialize();
    }

    RedBlackTreeNode *GetRoot(){
        return this->root;
    }
    
    RedBlackTreeNode *GetNil(){
        return this->nil;
    }

    void initialize();

    void insert(RedBlackTreeNode *z);
    void remove(RedBlackTreeNode *z);
    bool remove(int key);
    RedBlackTreeNode *search(int key);

    // Helper functions
    void left_rotate(RedBlackTreeNode *x);
    void right_rotate(RedBlackTreeNode *y);
    void insert_fixup(RedBlackTreeNode *z);
    void transplant(RedBlackTreeNode *u, RedBlackTreeNode *v);
    void remove_fixup(RedBlackTreeNode *z);
    RedBlackTreeNode *tree_minimum(RedBlackTreeNode *z);
    RedBlackTreeNode *tree_maximum(RedBlackTreeNode *z);
    void print_tree();
    void preorder(RedBlackTreeNode *node);
    int get_black_height();
    void insert_colour(RedBlackTreeNode *newNode);
};
