#pragma once
#include "TNode.h"
#include <iostream>
using namespace std;

template <class Tkey, class TData>
class TList
{
public:
    TNode<Tkey, TData>* p_first;
    TNode<Tkey, TData>* p_previous;
    TNode<Tkey, TData>* p_current;
    TNode<Tkey, TData>* p_next;

    TList();
    TList(const TList<Tkey, TData>& list);
    TList(TNode<Tkey, TData>* tmp);
    ~TList();

    bool is_ended()const;
    void go_next();
    void reset();

    TNode<Tkey, TData>* Search(Tkey key);
    void insert_to_end(const TNode<Tkey, TData>&);
    void insert_to_start(const TNode<Tkey, TData>&);
    void insert_after(const TNode<Tkey, TData>&, Tkey key);
    void insert_before(const TNode<Tkey, TData>&, Tkey key);
    void remove(Tkey key);

    friend ostream& operator<<(ostream& out, TList<Tkey, TData>& list)
    {
        list.reset();
        while (!(list.is_ended()))
        {
            out << list->p_current << endl;
            list.go_next();
        }
        return out;
    }
};

template <class Tkey, class TData>
TList<Tkey, TData>::TList()
{
    p_first = nullptr;
    p_previous = nullptr;
    p_current = nullptr;
    p_next = nullptr;
}
template <class Tkey, class TData>
TList<Tkey, TData>::TList(const TList<Tkey, TData>& list)
{
    if (list.p_first == nullptr)
    {
        p_first = nullptr;
        p_previous = nullptr;
        p_current = nullptr;
        p_next = nullptr;
        return;
    }
    p_first = new TNode<Tkey, TData>(*(list.p_first));
    p_current = p_first;
    TNode<Tkey, TData>* node = list.p_first;
    node = node->p_next;
    while (node != nullptr)
    {
        p_current->p_next = new TNode<Tkey, TData>(*node);
        p_current = p_current->p_next;
        node = node->p_next;
    }
    reset();
}
template <class Tkey, class TData>
TList<Tkey, TData>::TList(TNode<Tkey, TData>* list)
{
    p_first = new TNode<Tkey, TData>(*list);
    p_current = p_first;
    TNode<Tkey, TData>* node = list;
    node = node->p_next;
    while (node != nullptr)
    {
        p_current->p_next = new TNode<Tkey, TData>(*node);
        p_current = p_current->p_next;
        node = node->p_next;
    }
    reset();
}
template <class Tkey, class TData>
TList<Tkey, TData>::~TList()
{
    reset();
    while (!is_ended())
    {
        go_next();
        delete p_previous;
    }
    delete p_current;
    p_first = nullptr;
    p_current = nullptr;
    p_previous = nullptr;
    p_next = nullptr;
}
template <class Tkey, class TData>
bool TList<Tkey, TData>::is_ended()const
{
    return (p_current == nullptr);
}
template <class Tkey, class TData>
void TList<Tkey, TData>::go_next()
{
    if (is_ended())
        return;
    p_previous = p_current;
    p_current = p_current->p_next;
    if (p_next != nullptr)
        p_next = p_next->p_next;
}
template <class Tkey, class TData>
void TList<Tkey, TData>::reset()
{
    p_previous = nullptr;
    p_current = p_first;
    if (p_first != nullptr)
    {
        p_next = p_current->p_next;
    }
    else
    {
        p_next = nullptr;
    }
}
template <class Tkey, class TData>
TNode<Tkey, TData>* TList<Tkey, TData>::Search(Tkey _key)
{
    reset();
    while ((!is_ended()) && (p_current->key != _key))
        go_next();
    if (is_ended())
    {
        reset();
        return nullptr;
    }
    return p_current;
}
template <class Tkey, class TData>
void TList<Tkey, TData>::insert_to_end(const TNode<Tkey, TData>& tmp)
{
    if (p_first == nullptr)
    {
        p_first = new TNode<Tkey, TData>(tmp);
        p_current = p_first;
    }
    else
    {
        TNode<Tkey, TData>* pprev = p_previous;
        TNode<Tkey, TData>* pcurr = p_current;
        TNode<Tkey, TData>* pnext = p_next;
        while (!is_ended())
            go_next();
        p_current = new TNode<Tkey, TData>(tmp);
        p_previous->p_next = p_current;

        p_previous = pprev;
        p_current = pcurr;
        p_next = pnext;
    }
}
template <class Tkey, class TData>
void TList<Tkey, TData>::insert_to_start(const TNode<Tkey, TData>& tmp)
{
    TNode<Tkey, TData>* tmp1 = new TNode<Tkey, TData>(tmp.key, tmp.data, p_first);
    if (p_current == p_first)
    {
        p_previous = tmp1;
    }
    p_first = tmp1;
}
template <class Tkey, class TData>
void TList<Tkey, TData>::insert_after(const TNode<Tkey, TData>& s, Tkey n)
{
    if (p_first == nullptr)
        throw "er";
    TNode<Tkey, TData>* pprev = p_previous;
    TNode<Tkey, TData>* pcurr = p_current;
    TNode<Tkey, TData>* pnext = p_next;

    if (Search(n) == nullptr)
    {
        p_previous = pprev;
        p_current = pcurr;
        p_next = pnext;
        return;
    }
    TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(s.key, s.data, p_next);
    p_current->p_next = tmp;

    p_previous = pprev;
    p_current = pcurr;
    p_next = pnext;
}
template <class Tkey, class TData>
void TList<Tkey, TData>::insert_before(const TNode<Tkey, TData>& s, Tkey n)
{
    if (p_first == nullptr)
        throw "er";
    TNode<Tkey, TData>* pprev = p_previous;
    TNode<Tkey, TData>* pcurr = p_current;
    TNode<Tkey, TData>* pnext = p_next;

    if (Search(n) == nullptr)
    {
        p_previous = pprev;
        p_current = pcurr;
        p_next = pnext;
        return;
    }

    if (p_first == p_current)
    {
        TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(s.key, s.data, p_first);
        if (pcurr == p_first)
        {
            p_previous = tmp;
        }
        else
        {
            p_previous = pprev;
            p_current = pcurr;
            p_next = pnext;
        }
        p_first = tmp;
        return;
    }

    TNode<Tkey, TData>* tmp = new TNode<Tkey, TData>(s.key, s.data, p_current);
    p_previous->p_next = tmp;

    p_previous = pprev;
    p_current = pcurr;
    p_next = pnext;
}
template <class Tkey, class TData>
void TList<Tkey, TData>::remove(Tkey s)
{
    if (p_first == nullptr)
        throw "er";
    TNode<Tkey, TData>* pprev = p_previous;
    TNode<Tkey, TData>* pcurr = p_current;
    TNode<Tkey, TData>* pnext = p_next;

    if (Search(s) == 0)
    {
        p_previous = pprev;
        p_current = pcurr;
        p_next = pnext;
        return;
    }
    if (p_first == p_current)
    {
        if (pcurr == p_first)
        {
            if (p_next != nullptr)
                if (p_next == 0)
                {
                    p_next = p_next->p_next;
                }
                p_current = p_next;
                p_previous->p_next = p_current;
        }
        delete p_first;
        p_first = p_next;

        return;
    }

    if (pcurr == p_current)
    {
        delete p_current;
        p_current = pnext;
        p_previous->p_next = p_current;
        if (p_next == 0)
        {
            p_next = p_next->p_next;
        }
        return;
    }

    p_previous->p_next = p_current->p_next;
    delete p_current;
    p_current = p_next;
    if (p_next == 0)
    {
        p_next = p_next->p_next;
    }
    p_previous = pprev;
    p_current = pcurr;
    p_next = pnext;
}
