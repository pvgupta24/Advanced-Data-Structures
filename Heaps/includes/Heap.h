#ifndef _HEAPS
#define _HEAPS

#define MAX_NODE_COUNT 1000000
#define INF 999999

template <class T>
struct Node
{
  public:
    Node<T> *prev;
    Node<T> *next;
    Node<T> *child;
    Node<T> *parent;
    T value;
    int degree;
    bool marked;
};

template <class T>
class Heap
{
protected:
    int node_count;
    void deleteAll(Node<T> *n)
    {
        if (n)
        {
            Node<T> *c = n;
            do
            {
                Node<T> *d = c;
                c = c->next;
                deleteAll(d->child);
                delete d;
            } while (c != n);
        }
    }

public:
    Node<T> *heap; // Root Node of Heap

    Heap()
    {
        node_count = 0;
        heap = NULL;
    }

    virtual ~Heap()
    {
        deleteAll(heap);
    }

    // Makes Heap an abstract class
    virtual void insert(T value) = 0;
    virtual T get_min() = 0;
    virtual T extract_min() = 0;
    virtual void decrease_key(T i, T value) = 0;

    int getNodeCount(){

        return node_count;
    }

};

#endif
