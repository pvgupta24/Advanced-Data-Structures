r, l
RedBlackTree *GetMergeTreeToLeft(RedBlackTree *red_black_tree1, RedBlackTree *red_black_tree2)
{
    int rank_rbtree1 = red_black_tree1->GetRank();
    int rank_rbtree2 = red_black_tree2->GetRank();
    int val = red_black_tree2->ExtractMaximum();
    rank_rbtree2 = red_black_tree2->GetRank();
    int count1 = rank_rbtree1;
    RedBlackTreeNode *root1 = (red_black_tree1->GetRoot())->left;
    while (root1 != red_black_tree1->nil)
    {
        if (count1 == rank_rbtree2 + 1)
        {
            break;
        }
        if (root1->red == 0)
        {
            count1--;
        }
        root1 = root1->left;
    }
    RedBlackTreeNode *orig_left_child = root1->left;
    struct RedBlackKey *rbk = (struct RedBlackKey *)malloc(sizeof(struct RedBlackKey *));
    rbk->key = val;
    struct RedBlackTreeNode *newNode = (struct RedBlackTreeNode *)malloc(sizeof(struct RedBlackTreeNode));
    newNode->key = (void *)rbk;
    newNode->parent = newNode->right = newNode->left = red_black_tree1->GetLeaf();
    rbk->RBnode = newNode;
    root1->left = newNode;
    newNode->parent = root1;
    newNode->red = 1;
    newNode->left = (red_black_tree2->GetRoot())->left;
    // assert (newNode->left != red_black_tree1.nil);
    newNode->left->parent = newNode;
    RedBlackTreeNode *node1 = newNode->left;
    newNode->right = orig_left_child;
    orig_left_child->parent = newNode;

    RedBlackTreeNode *parent = newNode->parent;
    RedBlackTreeNode *sibling = red_black_tree1->nil;
    if (parent != red_black_tree1->GetRoot())
    {
        if (newNode == parent->right)
        {
            sibling = parent->left;
        }
        else
        {
            sibling = parent->right;
        }
        if (sibling->red)
        {
            sibling->red = 0;
            newNode->red = 0;
            parent->red = 1;
            red_black_tree1->InsertColour(parent);
        }
        else
        {
            if (newNode->right->red)
            {
                newNode->parent->red = 1;
                newNode->right->red = 0;
                red_black_tree1->LeftRotate(newNode);
                red_black_tree1->RightRotate(parent);
            }
        }
    }
    return red_black_tree1;
}

RedBlackTree *GetMergedRBTree(RedBlackTree *red_black_tree1, RedBlackTree *red_black_tree2, bool is_elements_in_tree1_greater)
{
    RedBlackTree *join_red_black_tree;
    int rank_rbtree1 = red_black_tree1->GetRank();
    int rank_rbtree2 = red_black_tree2->GetRank();
    // Elements of red_black_tree1 is greater than red_black_tree2.
    if (is_elements_in_tree1_greater)
    {
        // Rank of red_black_tree1 is greater than red_black_tree2.
        if (rank_rbtree1 > rank_rbtree2)
        {
            // Method: Extract maximum from red_black_tree2. Move on the left spine of red_black_tree1 till there are rank_red_black_tree2.
            // Place the vertex to the left child of the node and place the rbtree as left child of the vertex and place the original left
            // child as right child of the vertex.
            join_red_black_tree = GetMergeTreeToLeft(red_black_tree1, red_black_tree2);
        }
        else
        {
            // Rank of red_back_tree1 is lesser than red_black_tree2.

            // Extract minimum from rbtree1. Move on the right spine till the node down which the number of black nodes = rank of rbtree1.
            // Place the vertex as right child, place the original right child as the left child of the vertex and place rbtree1 as right
            // child as of the vertex.
            join_red_black_tree = GetMergeTreeToRight(red_black_tree1, red_black_tree2);
        }
    }
    else
    {
        // Elements of red_black_tree1 is lesser than red_black_tree2.
        if (rank_rbtree1 > rank_rbtree2)
        {
            // Rank of red_black_tree1 is greater than red_black_tree2.
            // Method same as the case above but with swapping rbtree1 and rbtree2.
            join_red_black_tree = GetMergeTreeToRight(red_black_tree2, red_black_tree1);
        }
        else
        {
            // Rank of red_black_tree1 is less than red_black_tree2.
            // Method same as the case above but with swapping rbtree1 and rbtree2.
            join_red_black_tree = GetMergeTreeToLeft(red_black_tree2, red_black_tree1);
        }
    }
    return join_red_black_tree;
}