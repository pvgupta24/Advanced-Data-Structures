#include "FibonacciHeap.h"
#include <bits/stdc++.h>

using namespace std;

FibonacciHeap::FibonacciHeap() {
    ops = 0;
    minNode = NULL;
}

int FibonacciHeap::getOps() {
    return ops;
}

void FibonacciHeap::push(pair<int,int> Node) {
    insert(Node);
    return;
}

pair<int, int> FibonacciHeap::top() {
    if(heap.size() == 0) 
        return make_pair(-1,-1);
    return getMin()->data;
}

pair<int,int> FibonacciHeap:pop() {
    if(heap.size() ==0)
        return make_pair(-1,-1);

    pair<int,int> Node = extractMin();
    return Node;
}

Node::Node(pair<int,int> key) {
    this->data = key;
    this->degree = 0;
    this->child = this->parent = this->sibling = NULL;
    this->marked = false;
}

void FibonacciHeap::insert(pair<int,int> key) {
    Node *temp = new Node(key);
    insertAtTreeInHeap(temp);
}

void FibonacciHeap::insertAtTreeInHeap(Node* tree) {
    list<Node*> temp;
    temp.push_back(tree);
    heap = unionFibonacciHeap(heap, minNode, temp, tree);
    return;
}

Node* FibonacciHeap::getMin() {
    if(heap.size() == 0)
        return NULL;

        return minNode;
}

void swap(Node *t1, Node *t2) {
    Node* temp;
    temp = t1;
    t1 = t2;
    t2 = temp;
}

list<Node*> FibonacciHeap::removeMinFromTreeReturnHeap(Node *tree, *& min_lo) {
    list<Node*> tempheap;
    Node *temp = tree->child;
    Node* lo;
    ops++;
    while(temp) {
        if(((temp)->data).first < (min_lo->data).first)
                min_lo = temp;
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        tempheap.push(lo);
    } 
    return tempheap;
}


pair<int,int> FibonacciHeap::extractMin() {
    if(heap.size() == 0)
        return make_pair(-1,-1);
    list<Node*> new_heap, lo;
    Node* temp;
    temp = getMin();
    list<Node*>::iterator it;
    it = heap.begin();
    Node *min_newheap = new Node(make_pair(INT_MAX,-1));
    Node *min_lo = new Node(make_pair(INT_MAX,-1));
    while(it != heap.end()) {
        if(*it != temp) {
            new_heap.push_back(*it);
            if((*it->data).first < (min_newheap->data).first)
                min_newheap = (*it);
        }
        it++;
    }
    ops++;
    lo = removeMinFromTreeReturnHeap(temp, min_lo);
    heap = unionFibonacciHeap(new_heap, min_newheap, lo, min_lo);
    adjust();
    return temp->data;
}


Node* FibonacciHeap::mergeFibonacciTrees(Node* b1, Node *b2) {
    if((b1->data).first > (b2->data).first)
    {
        swap(b1, b2);
        ops++
    }

    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}

bool FibonacciHeap::decreaseKey(pair<int ,int> value, pair<int,int> newKey) {
    Node* node = find(heap, value);

    // Check that the node exists and the new key is smaller
    if (node && newKey <= node->data) {
        node->data = newKey;

        if( node->data < minNode->data ) {
            minNode = node;
        }

        if(node->parent != NULL && node->parent->data > newKey) {

            do {
                Node* oldParent = node->parent;
                cut(node);
                node = oldParent;
            } while(node->marked && node->parent != NULL);

            if (node->parent != NULL) {
                node->marked = true;
            }
        }

        return true;
    } else {
        return false;
    }
}


void FibonacciHeap::cut(Node* node) {
    if(node->parent != NULL) {
        node->parent->degree--;

        if(node->parent->degree == 0) {
            node->parent->child = NULL;
        } else {
            node->parent->child = node->sibling;
        }

        node->parent = NULL;
        node->sibling  = NULL;

        heap.push(node->data);

        free(node);

    }
}


list<Node*> FibonacciHeap::unionFibonacciHeap(list<Node*> l1, Node* min1, list<Node*> l2, Node *min2) {
    copy(l1.rbegin(), l1.rend(), front_inserter(l2));
    if(min1 ==NULL)
        minNode = min2;
    else if(min2 == NULL)
        minNode = min1;
    else {
        if((min1->data).first < (min2->data).first)
            minNode = min1;
        else
            minNode = min2;
    }
    return l2;
}

void FibonacciHeap::adjust() {

    if(heap.size() <= 1)
        return;
    list<Node*>::iterator it;
    it = heap.begin();
    map<int, Node*> m;
    
    while(it != heap.end()) {

        if(m[(*it)->degree] != NULL) {
            int deg = (*it)->degree;
            *it = mergeFibonacciTrees(*it, m[deg]);
            list<Node*>::iterator it_temp;
            it_temp = heap.begin();
            while((*it_temp) != m[deg])
                it_temp++;
            it_temp = heap.erase(it_temp);
            m[deg] = NULL;
        }
        m[(*it)->degree] = (*it);
        it++;
    }
    ops++;
    return;
}