#ifndef _BINOMIAL_HEAP
#define _BINOMIAL_HEAP

#include "Heap.h"

/*
    virtual void insert(T value) = 0;
    virtual T get_min() = 0;
    virtual T extract_min() = 0;
    virtual void decrease_key(T i, T value) = 0;
*/

template <class T>
class BinomialHeap : public virtual Heap<T>
{

public:
    T *data;

    BinomialHeap()
    {
        data = new T[MAX_NODE_COUNT];
    }

    ~BinomialHeap()
    {
        delete data;
    }

    void min_heapify(int i)
    {
        
    }

    T get_min()
    {

    }

    T extract_min()
    {

    }

    void insert(T element)
    {
        
    }

    void swap(T *x, T *y)
    {

    }

    void decrease_key(T elem, T new_val)
    {
        
    }
};

#endif