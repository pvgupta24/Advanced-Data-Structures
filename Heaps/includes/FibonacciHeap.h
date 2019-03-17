#ifndef _FIBONACCI_HEAP
#define _FIBONACCI_HEAP

#include "Heap.h"

template <class T>
class FibonacciHeap : public virtual Heap<T>
{
  public:
    Node<T> *heap; /*root Node of heap*/

    FibonacciHeap()
    {
        heap = NULL;
    }

    ~FibonacciHeap()
    {
        if (heap)
        {
            deleteAll(heap);
        }
    }

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

    Node<T> *create_node(T value)
    {
        Node<T> *n = new Node<T>;
        n->value = value;
        n->prev = n->next = n;
        n->degree = 0;
        n->marked = false;
        n->child = NULL;
        n->parent = NULL;
        return n;
    }

    Node<T> *merge_heaps(Node<T> *a, Node<T> *b)/**/
    {
        if (!a)
            return b;
        if (!b)
            return a;
        if (a->value > b->value)
        {
            Node<T> *temp = a;
            a = b;
            b = temp;
        }
        Node<T> *an = a->next;
        Node<T> *bp = b->prev;
        a->next = b;
        b->prev = a;
        an->prev = bp;
        bp->next = an;
        return a;
    }

    void insert(T value)/**/
    {
        this->node_count++;
        Node<T> *ret = create_node(value);
        heap = merge_heaps(heap, ret);
    }

    T get_min()/**/
    {
        if(heap==NULL)
            return T();
            
        return heap->value;
    }

    void addChild(Node<T> *parent, Node<T> *child)
    {
        child->prev = child->next = child;
        child->parent = parent;
        parent->degree++;
        parent->child = merge_heaps(parent->child, child);
    }

    Node<T> *extract_min_helper(Node<T> *n)
    {
        /* mark all childs as false and set their parent to null */
        if (n->child != NULL)
        {
            Node<T> *c = n->child;
            do
            {
                c->marked = false;
                c->parent = NULL;
                c = c->next;
            } while (c != n->child);
        }
        /* done */

        if (n->next == n)
        {
            n = n->child;
        }
        else
        {
            n->next->prev = n->prev; /* detach n from doubly LL */
            n->prev->next = n->next; /* detach n from doubly LL */
            n = merge_heaps(n->next, n->child);
        }

        if (n == NULL)
            return n;

        Node<T> *trees[64] = {NULL};

        while (true)
        {
            if (trees[n->degree] != NULL)
            {
                Node<T> *t = trees[n->degree];
                if (t == n)
                    break;
                trees[n->degree] = NULL;
                if ((n->value) < (t->value))
                {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    addChild(n, t);
                }
                else
                {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    if (n->next == n)
                    {
                        t->next = t;
                        t->prev = t;
                        addChild(t, n);
                        n = t;
                    }
                    else
                    {
                        n->prev->next = t;
                        n->next->prev = t;
                        t->next = n->next;
                        t->prev = n->prev;
                        addChild(t, n);
                        n = t;
                    }
                }
                continue;
            }
            else
            {
                trees[n->degree] = n;
            }
            n = n->next;
        }
        Node<T> *min = n;
        Node<T> *start = n;
        do
        {
            if (n->value < min->value)
                min = n;
            n = n->next;
        } while (n != start);
        return min;
    }

    T extract_min()/**/
    {
        if(heap == NULL) return T();
        Node<T> *old = heap;
        heap = extract_min_helper(heap);
        T ret = old->value;
        this->node_count--;
        delete old;
        return ret;
    }

    Node<T> *find_helper(Node<T> *heap, T value)
    {
        Node<T> *n = heap;
        if (n == NULL)
            return NULL;
        do
        {
            if (n->value == value)
                return n;
            Node<T> *ret = find_helper(n->child, value);
            if (ret)
                return ret;
            n = n->next;
        } while (n != heap);
        return NULL;
    }

    Node<T> *find(T value)
    {
        return find_helper(heap, value);
    }

    Node<T> *cut(Node<T> *heap, Node<T> *n)
    {
        if (n->next == n)
        {
            n->parent->child = NULL;
        }
        else
        {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n->parent->child = n->next;
        }
        n->next = n->prev = n;
        n->marked = false;
        return merge_heaps(heap, n);
    }

    Node<T> *decrease_key_helper(Node<T> *heap, Node<T> *n, T value)
    {
        if (n->value < value)
            return heap;
        n->value = value;
        if (n->parent)
        {
            if (n->value < n->parent->value)
            {
                heap = cut(heap, n);
                Node<T> *parent = n->parent;
                n->parent = NULL;
                while (parent != NULL && parent->marked)
                {
                    heap = cut(heap, parent);
                    n = parent;
                    parent = n->parent;
                    n->parent = NULL;
                }
                if (parent != NULL && parent->parent != NULL)
                    parent->marked = true;
            }
        }
        else
        {
            if (n->value < heap->value)
            {
                heap = n;
            }
        }
        return heap;
    }

    void decrease_key(T i, T value)/**/
    {
        Node<T> *n = find(i);
        if(n==NULL)
        {
            return;
        }
        heap = decrease_key_helper(heap, n, value);
    }
};

#endif