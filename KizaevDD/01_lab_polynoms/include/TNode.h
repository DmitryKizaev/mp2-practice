#pragma once
#include <iostream>

using namespace std;

template <class Tkey, class TData>
class TNode
{
public:
    Tkey key;
    TData data;
    TNode* p_next;
    TNode();
    TNode(const TNode&);
    TNode(Tkey, TData, TNode* next = 0);
    ~TNode();

    friend ostream& operator<<(ostream& out, TNode<Tkey, TData>& node)
    {
        out << node.key << " - " << node.data;
        return out;
    }
};

template <class Tkey, class TData>
TNode<Tkey, TData>::TNode()
{
    p_next = nullptr;
}
template <class Tkey, class TData>
TNode<Tkey, TData>::TNode(const TNode<Tkey, TData>& tmp)
{
    key = tmp.key;
    data = tmp.data;
    p_next = nullptr;
}
template <class Tkey, class TData>
TNode<Tkey, TData>::TNode(Tkey _key, TData _data, TNode* next)
{
    key = _key;
    data = _data;
    p_next = next;
}
template <class Tkey, class TData>
TNode<Tkey, TData>::~TNode()
{
    key = nullptr;
    data = nullptr;
}