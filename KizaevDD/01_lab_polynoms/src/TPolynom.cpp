#include "TPolynom.h"
#include <iostream>
#include <string>

using namespace std;

TPolynom::TPolynom()
{
    polynomial = new TList<unsigned int, double>();
}
TPolynom::TPolynom(const TList<unsigned int, double>* tm)
{
    TList<unsigned int, double>* tmp = new TList<unsigned int, double>(*tm);
    polynomial = new TList<unsigned int, double>(tmp->p_first);
    check_lim(tmp);
    tmp->reset();
    tmp->go_next();
    int conv = tmp->p_first->key;
    while (!tmp->is_ended())
    {
        if (tmp->p_current->key < conv)
        {
            polynomial->insert_before(*tmp->p_current, conv);
        }
        else
        {
            polynomial->insert_after(*tmp->p_current, conv);
        }
        conv = tmp->p_current->key;
    }
}
TPolynom::TPolynom(const string& st)
{
    if (st == "")
        throw "!empty line";
    polynomial = new TList<unsigned int, double>();
    string tmp = "";
    string powerst = "";
    char sign = '+';
    char current = ' ';
    unsigned int power = 0;
    double num = 0;
    int i = 0;
    TMonom rez;
    rez.p_next = NULL;
    while (i < st.length())
    {
        if (st[i] != ' ')
        {
            switch (st[i])
            {
            case 'x':
                power += 100;
                current = 'x';
                break;
            case 'y':
                power += 10;
                current = 'y';
                break;
            case 'z':
                power += 1;
                current = 'z';
                break;
            case '+':
                if ((tmp == "") && (power != 0))
                    num = 1;
                else if (tmp != "")
                    num = stoi(tmp);
                if (sign == '-')
                    num *= (-1);
                rez.key = power;
                rez.data = num;
                insert_into(rez);
                power = 0;
                num = 0; 
                tmp = "";
                sign = '+';
                break;
            case '-':
                if ((tmp == "") && (power != 0))
                    num = 1;
                else if (tmp != "")
                    num = stoi(tmp);
                if (sign == '-')
                    num *= (-1);
                rez.key = power;
                rez.data = num;
                insert_into(rez);
                power = 0;
                num = 0;
                tmp = "";
                sign = '-';
                break;
            case '*':
                break;
            case '^':
                i++;
                powerst += st[i];
                switch (current)
                {
                case 'x':
                    power += (stoi(powerst) - 1) * 100;
                    break;
                case 'y':
                    power += (stoi(powerst) - 1) * 10;
                    break;
                case 'z':
                    power += stoi(powerst) - 1;
                    break;
                }
                powerst = st[i + 1];
                if (is_double(powerst))
                    throw "limit power";
                else
                    powerst = "";
                break;
            default:
                tmp += st[i];
                break;
            }
        }
        i++;
    }
    if (tmp == "")
        num = 1;
    else if (tmp != "")
        num = stoi(tmp);
    if (sign == '-')
        num *= (-1);
    rez.key = power; 
    rez.data = num;
    insert_into(rez);
}
TPolynom::TPolynom(const TPolynom& tmp)
{
    polynomial = new TList<unsigned int, double>(*tmp.polynomial);
}
TPolynom::~TPolynom()
{
    delete polynomial;
}

TPolynom TPolynom::operator+(const TPolynom& tm)
{
    TPolynom tmp(tm);
    tmp.polynomial->reset();
    TPolynom rez(*this);
    rez.polynomial->reset();
    while (tmp.polynomial->p_current != NULL)
    {
        rez = rez + *tmp.polynomial->p_current;
        tmp.polynomial->go_next();
    }
    return rez;
}

TPolynom TPolynom::operator-(const TPolynom& tm)
{
    TPolynom rez = (*this) + (-tm);
    return rez;
}

TPolynom TPolynom::operator*(const TPolynom& tm)
{
    TPolynom tmp(tm);
    TPolynom tmp1(*this);
    tmp1.polynomial->reset();
    tmp.polynomial->reset();
    TPolynom rez;
    while (!tmp1.polynomial->is_ended())
    {
        rez += tmp * *tmp1.polynomial->p_current;
        tmp1.polynomial->go_next();
    }
    return rez;
}

TPolynom TPolynom::operator+(const TMonom& tmp)
{
    TPolynom rez(*this);
    rez.polynomial->reset(); 
    if (rez.polynomial->p_first == NULL)
    {
        rez.polynomial->insert_to_end(tmp);
        return rez;
    }
    while ((rez.polynomial->p_current != NULL) && (rez.polynomial->p_current->key < tmp.key))
        rez.polynomial->go_next();
    if (rez.polynomial->p_current == NULL)
    {
        rez.polynomial->insert_to_end(tmp);
        return rez;
    }
    if (rez.polynomial->p_current->key == tmp.key)
    {
        if (rez.polynomial->p_current->data + tmp.data == 0)
        {
            rez.polynomial->remove(rez.polynomial->p_current->key);
        }
        else
        {
            *rez.polynomial->p_current += tmp;
        }
    }
    else if (rez.polynomial->p_current->key > tmp.key)
    {
        rez.polynomial->insert_before(tmp, rez.polynomial->p_current->key);
    }
    return rez;
}

TPolynom TPolynom::operator-(const TMonom& tmp)
{
    TPolynom rez = *this + (-tmp);
    return rez;
}

TPolynom TPolynom::operator*(const TMonom& tmp)
{
    TPolynom rez;
    if (tmp.data == 0)
        return rez;
    rez = *this;
    rez.polynomial->reset();
    while (rez.polynomial->p_current != NULL)
    {
        *rez.polynomial->p_current *= tmp;
        rez.polynomial->go_next();
    }
    return rez;
}

TPolynom TPolynom::operator*(double c)
{
    
    TPolynom rez;
    if (c == 0)
        return rez;
    rez = *this;
    rez.polynomial->reset();
    while (!rez.polynomial->is_ended())
    {
        *rez.polynomial->p_current *= c;
        rez.polynomial->go_next();
    }
    return rez;
}

TPolynom& TPolynom::operator=(const TPolynom& tm)
{
    if (*this == tm)
        return *this;
    delete polynomial;
    polynomial = new TList<unsigned int, double>(*tm.polynomial);
    return *this;
}

TPolynom& TPolynom::operator+=(const TPolynom& tm)
{
    TPolynom tmp = (*this) + tm;
    *this = tmp;
    return *this;
}

TPolynom& TPolynom::operator-=(const TPolynom& tm)
{
    TPolynom tmp = (*this) - tm;
    *this = tmp;
    return *this;
}

TPolynom& TPolynom::operator*=(const TPolynom& tm)
{
    TPolynom tmp = (*this) * tm;
    *this = tmp;
    return *this;
}

TPolynom& TPolynom::operator+=(const TMonom& tm)
{
    TPolynom tmp = (*this) * tm;
    *this = tmp;
    return *this;
}

TPolynom& TPolynom::operator-=(const TMonom& tm)
{
    TPolynom tmp = (*this) - tm;
    *this = tmp;
    return *this;
}

TPolynom& TPolynom::operator*=(const TMonom& tm)
{
    TPolynom tmp = (*this) * tm;
    *this = tmp;
    return *this;
}

TPolynom& TPolynom::operator*=(double c)
{
    TPolynom tmp = (*this) * c;
    *this = tmp;
    return *this;
}

TPolynom TPolynom::operator-() const
{
    TPolynom rez(*this);
    rez *= (-1);
    return rez;
}

bool TPolynom::operator==(const TPolynom& tmp)const
{
    TPolynom a(*this);
    TPolynom b(tmp);
    while ((!a.polynomial->is_ended()) || (!b.polynomial->is_ended()))
    {
        if (a.polynomial->p_current != b.polynomial->p_current)
            return false;
        a.polynomial->go_next();
        b.polynomial->go_next();
    }
    if ((a.polynomial->is_ended()) && (b.polynomial->is_ended()))
        return true;
    return false;
}
bool TPolynom::is_double(string a)
{
    for (int i = 0; i < a.length(); i++)
    {
        if ((a[i] != '0') && (a[i] != '1') && (a[i] != '2') && (a[i] != '3') && (a[i] != '4') &&
            (a[i] != '5') && (a[i] != '6') && (a[i] != '7') && (a[i] != '8') && (a[i] != '9') && (a[i] != ' '))
            return false;
    }
    return true;
}
void TPolynom::insert_into(TMonom node)
{
    if ((node.key == 0) && (node.data == 0))
        return;
    if (node.data == 0)
        return;
    if (polynomial->p_first == NULL)
    {
        polynomial->insert_to_end(node);
        return;
    }
    polynomial->reset(); 
    while ((polynomial->p_current->key < node.key) && (polynomial->p_current->p_next != NULL))
    {
        polynomial->go_next(); 
    }
    if (polynomial->p_current->key == node.key)
    {
        polynomial->p_current->data = polynomial->p_current->data + node.data;
        return;
    }
    else if (polynomial->p_current->key > node.key)
    {
        polynomial->insert_before(node, polynomial->p_current->key);
        return;
    }
    polynomial->insert_to_end(node);
}
void TPolynom::check_lim(const TList<unsigned int, double>* tm)const
{
    TList<unsigned int, double> tmp(*tm);
    tmp.reset();
    while (!tmp.is_ended())
    {
        if (tmp.p_current->key > 999)
        {
            throw "!limit power";
        }
        tmp.go_next();
    }
}