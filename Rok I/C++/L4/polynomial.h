#include<iostream>
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial{
    int degree;
    int* coefficients;

public:
    Polynomial(int p_degree=0, double p_coefficient=1.0);
    Polynomial(int p_degree, const double p_coefficients[]);
    Polynomial(std::initializer_list<double> list);
    Polynomial(const Polynomial &p);
    Polynomial(Polynomial &&p1);
    Polynomial& operator= (const Polynomial &p);
    Polynomial& operator= (Polynomial &&p);
    ~Polynomial();

    friend istream & operator >> (istream &is, Polynomial &p);
    friend ostream & operator << (ostream &os, const Polynomial &p);

    friend Polynomial operator+ (const Polynomial &p1, const Polynomial &p2);
    friend Polynomial operator- (const Polynomial &p1, const Polynomial &p2);
    friend Polynomial operator* (const Polynomial &p1, const Polynomial &p2);
    friend Polynomial operator* (double c);
    Polynomial operator+= (const Polynomial &p);
    Polynomial operator-= (const Polynomial &p);
    Polynomial operator*= (const Polynomial &p);
    Polynomial operator*= (double c);
    double operator () (double x) const;
    double operator [] (int i) const;
};


#endif
