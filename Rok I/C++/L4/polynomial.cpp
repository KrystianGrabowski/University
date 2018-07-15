#include<iostream>
#include"polynomial.h"

Polynomial::Polynomial(int p_degree, double p_coefficient){
    if (p_coefficient == 0 && p_degree != 0){
        throw "Incorrect coefficient";
    }
    else{
        degree = p_degree;
        coefficients = new double[degree+1]();
        coefficients[degree] = p_coefficient;
    }
}

Polynomial::Polynomial(int p_degree, const double p_coefficients[]){
    if(p_coefficients[p_degree] == 0){
        throw "Incorrect coefficient";
    }
    else{
        degree = p_degree;
        coefficients = new double[degree + 1];
        for (int i=0; i<= degree; i++){
            coefficients[i] = p_coefficients[i];
        }
    }
}

Polynomial::Polynomial(std::initializer_list<double> list)
    : degree(list.size()-1){
    coefficients = new double[degree + 1];
    int i = 0;
    for(double el : list){
        coefficients[i] = el;
        i++;
    }
    if (coefficients[degree] == 0 && degree != 0){
        throw "Incorrect coefficient";
    }
}

Polynomial::Polynomial(const Polynomial &p) :degree(p.degree) {
    coefficients = new double[degree + 1];
    for(int i=0; i <= degree; i++){
        coefficients[i] = p.coefficients[i];
    }
}

Polynomial::Polynomial(Polynomial &&p)
    :degree(p.degree), coefficients(p.coefficients){
    p.degree = 0;
    p.coefficients = nullptr;
}

Polynomial& Polynomial::operator= (const Polynomial &p){
    if(this != &p){
        degree = p.degree;
        delete coefficients;
        coefficients = new double[degree + 1];
        for (int i=0; i<=degree; i++){
            coefficients[i] = p.coefficients[i];
        }
    }
    return *this;
}

Polynomial& Polynomial::operator= (Polynomial &&p){
    if(this != &p){
        degree = p.degree;
        delete coefficients;
        coefficients = p.coefficients;

        p.coefficients = nullptr;
        p.degree = 0;
    }
    return *this;
}

std::istream & operator >> (std::istream &is, Polynomial &p){
    is >> p.degree;
    delete p.coefficients;
    p.coefficients = new double[p.degree + 1];
    for (int i=0; i<=p.degree; i++){
        is >> p.coefficients[i];
    }
    return is;
}

std::ostream & operator << (std::ostream &os, const Polynomial &p){
    for(int i=p.degree; i>=0; i--){
        std::cout << p.coefficients[i] << "x^" << i << " ";
    }
    return os;
}



Polynomial::~Polynomial(){
    delete[] coefficients;
}
