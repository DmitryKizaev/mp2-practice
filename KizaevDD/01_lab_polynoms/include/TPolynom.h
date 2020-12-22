#pragma once
#include "TList.h"
#include "TMonom.h"
#include <iostream>

using namespace std;

typedef TNode<unsigned int, double> TMonom;

class TPolynom
{
private:
    TList<unsigned int, double>* polynomial;
    void insert_into(TMonom node);
    bool is_double(string a);
    void check_lim(const TList<unsigned int, double>*)const;
public:
    TPolynom();
    TPolynom(const TList<unsigned int, double>*);
    TPolynom(const string&);
    TPolynom(const TPolynom&);
    ~TPolynom();

    TPolynom operator+(const TPolynom&);
    TPolynom operator-(const TPolynom&);
    TPolynom operator*(const TPolynom&);
    TPolynom operator+(const TMonom&);
    TPolynom operator-(const TMonom&);
    TPolynom operator*(const TMonom&);
    TPolynom operator*(double);
    TPolynom& operator+=(const TPolynom&);
    TPolynom& operator-=(const TPolynom&);
    TPolynom& operator*=(const TPolynom&);
    TPolynom& operator+=(const TMonom&);
    TPolynom& operator-=(const TMonom&);
    TPolynom& operator*=(const TMonom&);
    TPolynom& operator*=(double);
    TPolynom& operator=(const TPolynom&);
    bool operator==(const TPolynom&)const;
    TPolynom operator-() const;

    friend ostream& operator<<(ostream& out, TPolynom& tmp)
    {
        TMonom* saved_prev = tmp.polynomial->p_previous;
        TMonom* saved_curr = tmp.polynomial->p_current;
        TMonom* saved_next = tmp.polynomial->p_next;
        tmp.polynomial->reset();
        while (!tmp.polynomial->is_ended())
        {
            out << *(tmp.polynomial->p_current);
            tmp.polynomial->go_next();
        }
        tmp.polynomial->p_previous = saved_prev;
        tmp.polynomial->p_current = saved_curr;
        tmp.polynomial->p_next = saved_next;
        return out;
    }
};