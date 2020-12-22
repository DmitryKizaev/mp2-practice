#pragma once
#include "TList.h"
#include <iostream>

using namespace std;

template <>
class TNode<unsigned int, double>
{
public:
    unsigned int key;
    double data;
    TNode* p_next;

    TNode();
    TNode(const string tmp);
    TNode(const TNode<unsigned int, double>&);
    TNode(unsigned int, double, TNode<unsigned int, double>*  next = 0);
    ~TNode();

    TNode<unsigned int, double>& operator=(const TNode<unsigned int, double>&);
    bool operator==(const TNode<unsigned int, double>&)const;
    TNode<unsigned int, double> operator+(const TNode<unsigned int, double>&);
    TNode<unsigned int, double> operator-(const TNode<unsigned int, double>&);
    TNode<unsigned int, double> operator*(const TNode<unsigned int, double>&);
    TNode<unsigned int, double> operator*(double);
    TNode<unsigned int, double>& operator+=(const TNode<unsigned int, double>&);
    TNode<unsigned int, double>& operator-=(const TNode<unsigned int, double>&);
    TNode<unsigned int, double>& operator*=(const TNode<unsigned int, double>&);
    TNode<unsigned int, double>& operator*=(double);
    TNode<unsigned int, double> operator-() const;

    friend ostream& operator<<(ostream& out, TNode<unsigned int, double>& node)
    {
        if (node.data > 0)
            out << "+";
        out << node.data;
        if (node.key / 100 != 0)
            out << "(x^" << node.key / 100 << ")";
        if ((node.key / 10) % 10 != 0)
            out << "(y^" << (node.key / 10) % 10 << ")";
        if (node.key % 10 != 0)
            out << "(z^" << node.key % 10 << ")";
        out << " ";
        return out;
    }
};


