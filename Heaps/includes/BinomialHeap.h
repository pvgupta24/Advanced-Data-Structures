#ifndef _BINOMIAL_HEAP
#define _BINOMIAL_HEAP

#include "Heap.h"
#include <list>
using namespace std;

/*
    virtual void insert(T value) = 0;
    virtual T get_min() = 0;
    virtual T extract_min() = 0;
*/

template <class T>
class BinomialHeap : public virtual Heap<T>
{

public:
    list<Node<T> *> data;

    BinomialHeap()
    {
        
    }

    ~BinomialHeap()
    {
        data.erase(data.begin(), data.end());
    }

    void insert(T element)
    {
        Node<T> *temp = newNode(element); 
        data = insertATreeInHeap(temp); 
        
    }
    
    Node<T> * getMin()
    {
        typename list<Node<T> *>::iterator it = data.begin(); 
        Node<T> *temp = *it; 
        while (it != data.end()) 
        { 
            if ((*it)->value < temp->value) 
                temp = *it; 
            it++; 
        } 
        return temp; 
    }

    T get_min(){
        typename list<Node<T> *>::iterator it = data.begin(); 
        Node<T> *temp = *it; 
        while (it != data.end()) 
        { 
            if ((*it)->value < temp->value) 
                temp = *it; 
            it++; 
        } 
        return temp->value;
    }

    T extract_min()
    {
        list<Node<T> *> new_heap,lo; 
        Node<T> *temp; 
    
        temp = getMin(); 
        typename list<Node<T> *>::iterator it; 
        it = data.begin(); 
        while (it != data.end()) 
        { 
            if (*it != temp) 
            { 
                new_heap.push_back(*it); 
            } 
            it++; 
        } 
        lo = removeMinFromTreeReturnBHeap(temp); 
        new_heap = unionBionomialHeap(new_heap,lo); 
        new_heap = adjust(new_heap); 
        data = new_heap; 

    }

    list<Node<T> *> removeMinFromTreeReturnBHeap(Node<T> *tree) 
    { 
        list<Node<T> *> heap; 
        Node<T> *temp = tree->child; 
        Node<T> *lo; 
    
        while (temp) 
        { 
            lo = temp; 
            temp = temp->sibling; 
            lo->sibling = NULL; 
            heap.push_front(lo); 
        } 
        return heap; 
    } 

    
    Node<T> * newNode(T element) 
    { 
        Node<T> *temp = new Node<T>; 
        temp->value = element; 
        temp->degree = 0; 
        temp->child = temp->parent = temp->sibling = NULL; 
        return temp; 
    } 

    list<Node<T> *> insertATreeInHeap(Node<T> *tree) 
    { 
        list<Node<T> *> temp; 
        temp.push_back(tree); 
        temp = unionBionomialHeap(data, temp); 
        return adjust(temp); 
    }

    list<Node<T> *> unionBionomialHeap(list<Node<T> *> l1, list<Node<T> *> l2) 
    { 
        list<Node<T> *> _new; 
        typename list<Node<T> *>::iterator it = l1.begin(); 
        typename list<Node<T> *>::iterator ot = l2.begin(); 
        while (it!=l1.end() && ot!=l2.end()) 
        { 
            if((*it)->degree <= (*ot)->degree) 
            { 
                _new.push_back(*it); 
                it++; 
            } 
            else
            { 
                _new.push_back(*ot); 
                ot++; 
            } 
        } 
    
        while (it != l1.end()) 
        { 
            _new.push_back(*it); 
            it++; 
        } 
    
        while (ot!=l2.end()) 
        { 
            _new.push_back(*ot); 
            ot++; 
        } 
        return _new; 
    } 

    list<Node<T> *> adjust(list<Node<T> *> _heap) 
    { 
        if (_heap.size() <= 1) 
            return _heap; 
        list<Node<T> *> new_heap; 
        typename list<Node<T> *>::iterator it1,it2,it3; 
        it1 = it2 = it3 = _heap.begin(); 
    
        if (_heap.size() == 2) 
        { 
            it2 = it1; 
            it2++; 
            it3 = _heap.end(); 
        } 
        else
        { 
            it2++; 
            it3=it2; 
            it3++; 
        } 
        while (it1 != _heap.end()) 
        { 
            if (it2 == _heap.end()) 
                it1++; 
    
            else if ((*it1)->degree < (*it2)->degree) 
            { 
                it1++; 
                it2++; 
                if(it3!=_heap.end()) 
                    it3++; 
            } 
    
            else if (it3!=_heap.end() && 
                    (*it1)->degree == (*it2)->degree && 
                    (*it1)->degree == (*it3)->degree) 
            { 
                it1++; 
                it2++; 
                it3++; 
            } 
    
            else if ((*it1)->degree == (*it2)->degree) 
            { 
                Node<T> *temp; 
                *it1 = mergeBinomialTrees(*it1,*it2); 
                it2 = _heap.erase(it2); 
                if(it3 != _heap.end()) 
                    it3++; 
            } 
        } 
        return _heap; 
    } 

    Node<T> * mergeBinomialTrees(Node<T> *b1, Node<T> *b2) 
    { 
        if (b1->value > b2->value) 
            swap(b1, b2); 
    
        b2->parent = b1; 
        b2->sibling = b1->child; 
        b1->child = b2; 
        b1->degree++; 
    
        return b1; 
    } 
};

#endif