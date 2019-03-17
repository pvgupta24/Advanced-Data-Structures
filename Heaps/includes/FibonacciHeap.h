#include "heap.h"

#ifndef FIBO_HEAP
#define FIBO_HEAP

struct Node {
    pair<int, int> data;
    int degree;
    bool marked;
    Node *child, *sibling, *parent;

    explicit Node(pair<int, int>);
}

class FibonacciHeap: public Heap
{
    public:
        FibonacciHeap();
        pair<int,int> top();
        pair<int,int> pop();
        void push(pair<int,int>);
        int getOps();
        bool decreaseKey(pair<int,int> value, pair<int,int> newKey);
    protected:
        pait<int,int> extractMin();
        void insertAtTreeInHeap(Node *tree);
        list<Node*> removeMinFromTreeReturnHeap(Node *tree, Node* &n);
        Node* mergeFibonacciTrees(Node* t1, Node* t2);
        list<Node*> unionFibonacciHeap(list<Node*> l1, list<Node*> l2,Node*);
        void adjust();
        void insert(pair<int,int> key);
        Node* getMin();
        void cut(Node* node);
    private:
        int ops;
        list<Node*> heap;
        Node *minNode;

}


#endif