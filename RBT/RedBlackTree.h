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

// TODO: template<typename Key, typename Value>
class RedBlackTree
{
    RedBlackTreeNode *root, *nil, *anchor;

public:
    RedBlackTree(){
        initialize();
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
    void print_tree();
    void preorder(RedBlackTreeNode *node);
};
