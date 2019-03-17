#ifndef _BINARY_HEAP
#define _BINARY_HEAP

#include "Heap.h"

template <class T>
class BinaryHeap : public virtual Heap<T>
{

public:
    T *data;

    BinaryHeap()
    {
        data = new T[MAX_NODE_COUNT];
    }

    ~BinaryHeap()
    {
        delete data;
    }

    void min_heapify(int i)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest;

        if (l <= this->node_count && data[l] < data[i])
        {
            smallest = l;
        }
        else
        {
            smallest = i;
        }

        if (r <= this->node_count && data[r] < data[smallest])
        {
            smallest = r;
        }

        if (smallest != i)
        {
            T temp = data[i];
            data[i] = data[smallest];
            data[smallest] = temp;
            min_heapify(smallest);
        }
    }

    T get_min()
    {
        if (this->node_count == 0)
            return T();

        return data[0];
    }

    T extract_min()
    {
        if (this->node_count == 0)
            return T();
        T min = data[0];
        data[0] = data[this->node_count - 1];
        this->node_count--;
        min_heapify(0);

        return min;
    }

    void insert(T element)
    {
        this->node_count++;
        data[this->node_count - 1] = element;

        int i = this->node_count - 1;
        while (i != 0 && data[(i - 1) / 2] > data[i])
        {
            T temp = data[i];
            data[i] = data[(i - 1) / 2];
            data[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }

    void swap(T *x, T *y)
    {
        T temp = *x;
        *x = *y;
        *y = temp;
    }

    void decrease_key(T elem, T new_val)
    {
        int i = -1;
        for (int k = 0; k < this->node_count; k++)
        {
            if (data[k] == elem)
            {
                i = k;
                break;
            }
        }

        if (i == -1 || data[i] <= new_val)
            return;

        data[i] = new_val;
        while (i != 0 && data[(i - 1) / 2] > data[i])
        {
            swap(&data[i], &data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
};

#endif