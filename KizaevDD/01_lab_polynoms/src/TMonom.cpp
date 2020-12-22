#include "TMonom.h"
#include <iostream>
#include <string>

using namespace std;

typedef TNode<unsigned int, double> TMonom;

TNode<unsigned int, double>::TNode()
{
    key = 0;
    data = 0;
    p_next = nullptr;
}

TNode<unsigned int, double>::TNode(const string input_str)
{
    int i = 0;
    char sign = '+';
    int power = 0;
    char current = 'n';
    if (input_str[0] == '-')
    {
        sign = '-';
        i++;
    }
    string coef = "";
    int num = 0;
    while (i < input_str.length())
    {
        switch (input_str[i])
        {
        case 'x':
            power += 100;
            if (current == 'n')
            {
                if (coef == "")
                    num = 1;
                else
                    num = stoi(coef);
                coef = "";
            }
            current = 'x';
            break;
        case 'y':
            power += 10;
            if (current == 'n')
            {
                if (coef == "")
                    num = 1;
                else
                    num = stoi(coef);
                coef = "";
            }
            else if (current == 'x')
            {
                if (coef == "")
                    num = 1;
                else if (coef == "^")
                    num = stoi(coef);
                power += 100 * (num - 1);
                coef = "1";
            }
            current = 'y';
            break;
        case 'z':
            power += 1;
            if (current == 'n')
            {
                if (coef == "")
                    num = 1;
                else
                    num = stoi(coef);
                coef = "1";
            }
            else if (current == 'x')
            {
                if (coef == "")
                    num = 1;
                else
                    num = stoi(coef);
                power += 100 * (num - 1);
                coef = "";
            }
            else if (current == 'y')
            {
                if (coef == "")
                    num = 1;
                else
                    num = stoi(coef);
                power += 10 * (num - 1);
                coef = "";
            }
            current = 'z';
            break;
        case '^':
            break;
        default:
            coef += input_str[i];
            break;
        }
        i++;
    }
    if (coef == "")
        num = 1;
    else
        num = stoi(coef);
    if (current == 'x')
        power += 100 * (num - 1);
    else if (current == 'y')
        power += 10 * (num - 1);
    else if (current == 'z')
        power += num - 1;
    key = power;
    data = num;
    p_next = nullptr;
}

TNode<unsigned int, double>::TNode(const TMonom& tmp)
{
    key = tmp.key;
    data = tmp.data;
    p_next = nullptr;
}

TNode<unsigned int, double>::TNode(unsigned int _conv, double _coeff, TNode<unsigned int, double> * next)
{
    key = _conv;
    data = _coeff;
    p_next = next;
}
TNode<unsigned int, double>::~TNode()
{}

TMonom& TNode<unsigned int, double>::operator=(const TNode<unsigned int, double> & tmp)
{
    if (*this == tmp)
        return *this;
    key = tmp.key;
    data = tmp.data;
    p_next = nullptr;
}
bool TNode<unsigned int, double>::operator==(const TNode<unsigned int, double> & tmp)const
{
    if ((tmp.key != key) || (tmp.data != data))
        return false;
    return true;
}
TMonom TNode<unsigned int, double>::operator+(const TNode<unsigned int, double> & tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    TMonom rez(tmp);
    rez.data += data;
    return rez;
}
TMonom TNode<unsigned int, double>::operator-(const TNode<unsigned int, double> & tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    TMonom rez(*this);
    rez.data -= tmp.data;
    return rez;
}
TMonom TNode<unsigned int, double>::operator*(const TNode<unsigned int, double> & tmp)
{
    if (((tmp.key / 100) + (key / 100) > 9) || (((tmp.key / 10) % 10) + ((key / 10) % 10) > 9) ||
        ((tmp.key % 10) + (key % 10) > 9))
        throw "!limit power";
    TMonom rez;
    rez.data = data * tmp.data;
    rez.key = key + tmp.key;
    return rez;
}
TMonom TNode<unsigned int, double>::operator*(double c)
{
    TMonom rez(*this);
    rez.data *= c;
    return rez;
}

TMonom& TNode<unsigned int, double>::operator+=(const TNode<unsigned int, double> & tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    data += tmp.data;
    return *this;
}
TMonom& TNode<unsigned int, double>::operator-=(const TNode<unsigned int, double> & tmp)
{
    if (key != tmp.key)
        throw "!diff conv";
    data -= tmp.data;
    return *this;
}
TMonom& TNode<unsigned int, double>::operator*=(const TNode<unsigned int, double> & tmp)
{
    if (((tmp.key / 100 + key / 100) > 9) || ((tmp.key / 10 + key / 10) > 90)
        || ((tmp.key % 10 + key % 10) > 9))
        throw "!limit power";
    key += tmp.key;
    data *= tmp.data;
    return *this;
}
TMonom& TNode<unsigned int, double>::operator*=(double c)
{
    data *= c;
    return *this;
}
TMonom TNode<unsigned int, double> ::operator-() const
{
    TMonom rez(*this);
    rez *= (-1);
    return rez;
}