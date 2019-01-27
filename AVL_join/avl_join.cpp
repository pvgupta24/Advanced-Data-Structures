/**
 * Merging AVL trees
 * 
 * @author Praveen Gupta
 * @author Dibyadarshan Hota
 */

#include <bits/stdc++.h>
using namespace std;

struct node {
    int value;
    int height;
    struct node *left;
    struct node *right;
};

void display (struct node *root) {
    if(root == NULL) return;
    display(root->left);
    cout << root->value << " ";
    display(root->right);
}

struct node *new_node(int new_val) {
    struct node *temp = new struct node;
    temp->right = NULL;
    temp->left = NULL;
    temp->height = 1;
    temp->value = new_val;
    return temp;
}

int height (struct node *root) {
    if(root == NULL) return 0;
    return (root->height);
}

struct node *rightRotate (struct node *y) { 
    struct node *x = y->left; 
    struct node *T2 = x->right; 
    x->right = y; 
    y->left = T2; 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
    return x; 
} 
  
struct node *leftRotate(struct node *x) { 
    struct node *y = x->right; 
    struct node *T2 = y->left; 
    y->left = x; 
    x->right = T2; 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
    return y; 
} 
  
int getBalance (struct node *root) { 
    if (root == NULL) { 
        return 0; 
    }
    return (height(root->left) - height(root->right)); 
} 

struct node *insert (struct node *root, int new_val) {
    if(root == NULL) {
        return (new_node(new_val));
    }
    if(new_val < root->value) {
        root->left = insert(root->left, new_val);
    }
    else{
        root->right = insert(root->right, new_val);
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root); 
  
    if (balance > 1 && new_val < root->left->value) {
        return rightRotate(root); 
    }
        
    if (balance < -1 && new_val > root->right->value) {
        return leftRotate(root); 
    } 
        
    if (balance > 1 && new_val > root->left->value) { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    if (balance < -1 && new_val < root->right->value) { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
  
    return root;
}

struct node *minNode (struct node *root) { 
    struct node *current = root; 
    while (current->left != NULL) 
        current = current->left; 
    return current; 
} 

struct node *deleteNode (struct node *root, int key) { 
    if (root == NULL) 
        return root; 
  
    if (key < root->value) 
        root->left = deleteNode(root->left, key); 
  
    else if(key > root->value) 
        root->right = deleteNode(root->right, key); 
  
    else { 
        if( (root->left == NULL) || (root->right == NULL) ) { 
            struct node *temp = root->left ? root->left : root->right; 
            if (temp == NULL) { 
                temp = root; 
                root = NULL; 
            } 
            else 
                *root = *temp; 
            delete(temp); 
        } 
        else { 
            struct node *temp = minNode(root->right); 
            root->value = temp->value; 
            root->right = deleteNode(root->right, temp->value); 
        } 
    } 
  
    if (root == NULL) 
      return root; 
  
    root->height = 1 + max(height(root->left), height(root->right)); 
  
    int balance = getBalance(root); 
  
    if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
    if (balance > 1 && getBalance(root->left) < 0) { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
    
    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    if (balance < -1 && getBalance(root->right) > 0) { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 

    return root; 
} 

int find_large(struct node *root) {
    if(root->right == NULL) {
        return root->value;
    }
    return find_large(root->right);
}

int find_small(struct node *root) {
    if(root->left == NULL) {
        return root->value;
    }
    return find_small(root->left);
}

int insert_value, flag = 0;

struct node *mergeSmall (struct node *root_1, struct node *root_2) {
    if((height(root_2->left) == height(root_1)+1) || height(root_2->left) == height(root_1)) {
        // cout << root_2->value << "<---";
        struct node *temp = new_node(insert_value);
        temp->right = root_2->left;
        temp->left = root_1;
        root_2->left = temp; 
        temp->height = 1 + max(height(temp->left), height(temp->right));
    }
    else {
        // cout << root_2->value << "<--";
        root_2->left = mergeSmall(root_1, root_2->left);
    }
    // cout << root_2->value << "<-";
    root_2->height = 1 + max(height(root_2->left), height(root_2->right));

    int balance = getBalance(root_2); 
  
    // if(flag == 0) {
    //     if(balance > 1) {
    //         flag = 1;
    //         root_2->left =  leftRotate(root_2->left); 
    //         return rightRotate(root_2);
    //     }
    // }
    // else {
    //     if(balance > 1) {
    //         return rightRotate(root_2);
    //     }
    // }

    if (balance > 1 && height(root_2->left->left)>height(root_2->left->right)) {
        return rightRotate(root_2); 
    }
        
    if (balance < -1 && height(root_2->right->left)<height(root_2->right->right)) {
        return leftRotate(root_2); 
    } 
        
    if (balance > 1 && height(root_2->left->left)<height(root_2->left->right)) { 
        root_2->left =  leftRotate(root_2->left); 
        return rightRotate(root_2); 
    } 
  
    if (balance < -1 && height(root_2->right->left)>height(root_2->right->right)) { 
        root_2->right = rightRotate(root_2->right); 
        return leftRotate(root_2); 
    } 
    return root_2;
}

struct node *mergeLarge (struct node *root_1, struct node *root_2) {
    if((height(root_1->right) == height(root_2)+1) || height(root_1->right) == height(root_2)) {
        // cout << root_1->value << "<---";
        struct node *temp = new_node(insert_value);
        temp->right = root_2;
        temp->left = root_1->right;
        root_1->right = temp; 
        temp->height = 1 + max(height(temp->left), height(temp->right));
    }
    else {
        // cout << root_1->value << "<--";
        root_1->right = mergeLarge(root_1->right, root_2);
    }
    // cout << root_1->value << "<-";
    root_1->height = 1 + max(height(root_1->left), height(root_1->right));

    int balance = getBalance(root_1); 
  
    // if(flag == 0) {
    //     if(balance < 1) {
    //         flag = 1;
    //         root_1->right =  rightRotate(root_1->right); 
    //         return leftRotate(root_1);
    //     }
    // }
    // else {
    //     if(balance < 1) {
    //         return leftRotate(root_1);
    //     }
    // }
    if (balance > 1 && height(root_1->left->left)>height(root_1->left->right)) {
        return rightRotate(root_1); 
    }
        
    if (balance < -1 && height(root_1->right->left)<height(root_1->right->right)) {
        return leftRotate(root_1); 
    } 
        
    if (balance > 1 && height(root_1->left->left)<height(root_1->left->right)) { 
        root_1->left =  leftRotate(root_1->left); 
        return rightRotate(root_1); 
    } 
  
    if (balance < -1 && height(root_1->right->left)>height(root_1->right->right)) { 
        root_1->right = rightRotate(root_1->right); 
        return leftRotate(root_1); 
    } 

    return root_1;
}

void check (struct node *root) {
    if(root == NULL) return;
    if(abs(height(root->left)-height(root->right)) > 1) {
        for(int i = 0; i < 3 ; ++i) {
            cout << "\n------ERROR-----\n";
        }
        cout << root->value;
        return;
    }
    check(root->right);
    check(root->left);
}

int main () {
    // Small tree
    struct node *root_1 = NULL;
    // Large tree
    struct node *root_2 = NULL;
    // Final tree
    struct node *root_3 = NULL;
    int n, m;
    // cout << "Number of nodes in small tree, nodes in big tree: \n";
    cin >> n >> m;
    // cout << "Nodes in small tree, nodes in big tree: \n";
    int a1, insert_val;
    for( a1 = 0 ; a1 < n ; ++a1 ) {
        cin >> insert_val;
        root_1 = insert(root_1, insert_val);
    }
    display(root_1); cout << "\n";

    for( a1 = 0 ; a1 < m ; ++a1 ) {
        cin >> insert_val;
        root_2 = insert(root_2, insert_val);
    }
    display(root_2); cout << "\n";

    // ---------- merging ----------
    // Heights
    cout << "Small height, large height: " << height(root_1) << ", " << height(root_2) << "\n";
    // Case equal heights or root_1 + 1 == root_2
    if(height(root_1) == height(root_2) || (height(root_1) == height(root_2)+1)) {
        // Make max(root_1) as root and join the other 2 trees
        cout<<"\nCase 1\n";
        int left_large = find_large(root_1);
        root_1 = deleteNode(root_1, left_large);
        root_3 = new_node(left_large);
        root_3->left = root_1;
        root_3->right = root_2;
        root_3->height= 1 + max(height(root_3->left), height(root_3->right));
    }
    // Case root_2 + 1 == root_1
    else if(height(root_1)+1 == height(root_2)) {
        // Make min(root_2) as root and join the other 2 trees
        cout<<"\nCase 2\n";
        int right_small = find_small(root_2);
        root_2 = deleteNode(root_2, right_small);
        root_3 = new_node(right_small);
        root_3->left = root_1;
        root_3->right = root_2;
        root_3->height= 1 + max(height(root_3->left), height(root_3->right));
    }
    // Case root_1 is smaller
    else if (height(root_1) < height(root_2)) {
        // Delete max(root_1)
        cout<<"\nCase 3\n";
        insert_value = find_large(root_1);
        root_1 = deleteNode(root_1, insert_value);
        root_2 = mergeSmall(root_1, root_2);
        root_3 = root_2;
    }
    // Case root_2 is smaller
    else {
        // Delete min(root_2)
        cout<<"\nCase 4\n";
        insert_value = find_small(root_2);
        root_2 = deleteNode(root_2, insert_value);
        root_1 = mergeLarge(root_1, root_2);
        root_3 = root_1;
    }
    display(root_3);
    check(root_3);
    cout << "\n";
    return 0;
}