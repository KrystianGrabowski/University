#include <iostream>
#include "123.h"

using namespace std;



wielomian::wielomian(int st, double wsp)
{
    if (wsp == 0 && st != 0)
    {
        cerr << "Zerowy wspolczynnik przy najwyzszej potedze !"<<endl;
    }
    else
    {
    n = st;
    a = new double[st + 1];
    for (int i=0; i<st; i++)
    {
        a[i] = 0;
    }
    a[st] = wsp;

    }

}
wielomian::wielomian (int st, const double wsp[])
{
    if (wsp[st] == 0)
    {
        cerr << "Zerowy wspolczynnik przy najwyzszej potedze !"<<endl;
    }
    else
    {
        n = st;
        a = new double[st + 1];
        for (int i=0; i<=st; i++)
        {
            a[i] = wsp[i];
            a[i] = wsp[i];
        }
    }
}
wielomian::wielomian (initializer_list<double> wsp)
{
    int poj = wsp.size();
    if (wsp.end() == 0)
    {
        cerr << "Zerowy wspolczynnik przy najwyzszej potedze !"<<endl;
    }
    else
    {
        n = poj - 1 ;
        a = new double[poj];
        int o = 0;
        for (int i : wsp)
        {
            a[o] = i;
            o++;
        }
    }
}

wielomian::wielomian (const wielomian &w)
{
    n = w.n;
    a = new double[n + 1];
    for (int i=0; i<=n; i++)
    {
        a[i]=w.a[i];
    }
}
wielomian::wielomian (wielomian &&w)
{
    n = w.n;
    a = w.a;
    w.a = nullptr;
}
wielomian & wielomian::operator = (const wielomian &w)
{
    if(this != &w)
    {
    n = w.n;
    a = new double[n + 1];
    for (int i=0; i<=n; i++)
    {
        a[i]=w.a[i];
    }
    }

    return *this;

}
wielomian & wielomian::operator = (wielomian &&w)
{
    if (this != &w)
    {
    n = w.n;
    a = w.a;
    w.a = nullptr;
    }

    return *this;
}
wielomian::~wielomian()
{
    delete [] a;

}

istream& operator >> (istream &we, wielomian &w)
{
    cout << "Podaj stopien wielomianu:";
    we >> w.n;
    w.a = new double[w.n + 1];
    cout << "Podaj "<<w.n + 1<<" elementow:"<<endl;
    for (int i=0; i<=w.n; i++)
    {
        we >> w.a[i];
    }
    return we;
}
ostream& operator << (ostream &wy, const wielomian &w)
{
    for (int i=w.n; i>=0; i--)
    {
        wy << w.a[i] << "x^" << i << " ";
        if (i != 0)
        {
        wy << "+ ";
        }
    }

    return wy;
}
wielomian operator + (const wielomian &u, const wielomian &v)
{
    int st = max(u.n, v.n);
    double wsp[st + 1];
    if(u.n > v.n)
    {
        for (int i=0; i<= v.n; i++)
            {wsp[i] = u.a[i] + v.a[i];}
        for (int j=v.n + 1; j<= u.n; j++)
            {wsp[j] = u.a[j];}
    }
    else
    {
        for (int i=0; i<= u.n; i++)
            {wsp[i] = u.a[i] + v.a[i];}
        for (int j=u.n + 1; j<= v.n; j++)
            {wsp[j] = v.a[j];}
    }
    wielomian d(st,wsp);
    return d;
}
wielomian operator - (const wielomian &u, const wielomian &v)
{
    int st = max(u.n, v.n);
    double wsp[st + 1];
    if(u.n > v.n)
    {
        for (int i=0; i<= v.n; i++)
            {wsp[i] = u.a[i] - v.a[i];}
        for (int j=v.n + 1; j<= u.n; j++)
            {wsp[j] = (-1) * u.a[j];}
    }
    else
    {
        for (int i=0; i<= u.n; i++)
            {wsp[i] = u.a[i] - v.a[i];}
        for (int j=u.n + 1; j<= v.n; j++)
            {wsp[j] = (-1) * v.a[j];}
    }
    wielomian o(st,wsp);
    return o;
}
wielomian operator * (const wielomian &u, const wielomian &v)
{
    int st = u.n + v.n;
    double wsp[st + 1];

    for (int i=0; i<=u.n; i++)
        for(int j=0; j<=v.n; j++)
            wsp[i + j] += u.a[i] * v.a[j];


    wielomian m(st,wsp);
    return m;
}
wielomian operator * (const wielomian &u, double c)
{
    wielomian s = u;
    for (int i = 0; i <= s.n; i++)
        s.a[i] = s.a[i] * c;
    return s;
}
wielomian& wielomian::operator += (const wielomian &v)
{
    *this = *this + v;
    return *this;
}
wielomian& wielomian::operator -= (const wielomian &v)
{
    *this = *this - v;
    return *this;
}
wielomian& wielomian::operator *= (const wielomian &v)
{
    *this = *this * v;
    return *this;
}
wielomian& wielomian::operator *= (double c)
{
    *this = *this * c;
    return *this;
}
double wielomian::operator()(double x) const
{
    double wartosc = a[n];
    for(int i=n-1; i>=0; i--)
        wartosc = x*wartosc + a[i];
    return wartosc;
}

double wielomian::operator[](int i) const
{
    if (i>n || i<0)
    {
        cerr << "Bledny index"<<endl;
    }
    return a[i];
}

