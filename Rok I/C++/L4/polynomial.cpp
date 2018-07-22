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

Polynomial operator+ (const Polynomial &p1, const Polynomial &p2){
    int tempdeg = std::max(p1.degree, p2.degree);
    double tempcoef[tempdeg + 1];
    if(p1.degree > p2.degree){
        for(int i=0; i<=p2.degree; i++){
            tempcoef[i] = p2.coefficients[i] + p1.coefficients[i];}
        for(int j=p2.degree+1; j<=p1.degree; j++){
            tempcoef[j] = p1.coefficients[j];}
    }
    else{
        for(int i=0; i<=p1.degree; i++){
            tempcoef[i] = p1.coefficients[i] + p2.coefficients[i];}
        for(int j=p1.degree+1; j<=p2.degree; j++){
            tempcoef[j] = p2.coefficients[j];}
    }
    return Polynomial(tempdeg, tempcoef);
}

Polynomial operator- (const Polynomial &p1, const Polynomial &p2){

    int tempdeg = std::max(p1.degree, p2.degree);
    double tempcoef[tempdeg + 1];
    if(p1.degree > p2.degree){
        for(int i=0; i<=p2.degree; i++){
            tempcoef[i] = p1.coefficients[i] - p2.coefficients[i];}
        for(int j=p2.degree+1; j<=p1.degree; j++){
            tempcoef[j] = p1.coefficients[j];}
    }
    else{
        for(int i=0; i<=p1.degree; i++){
            tempcoef[i] = p1.coefficients[i] - p2.coefficients[i];}
        for(int j=p1.degree+1; j<=p2.degree; j++){
            tempcoef[j] = (-1) * p2.coefficients[j];}
    }
    return Polynomial(tempdeg, tempcoef);
}

Polynomial operator* (const Polynomial &p1, const Polynomial &p2){

    int tempdeg = p1.degree + p2.degree;
    double tempcoef[tempdeg + 1] = {};
    for(int i=0; i<=p1.degree; i++){
        for(int j=0; j<=p2.degree; j++){
            tempcoef[i+j] += p1.coefficients[i] * p2.coefficients[j];
        }
    }
    return Polynomial(tempdeg, tempcoef);
}

Polynomial operator* (const Polynomial &p, double c){
    int tempdeg = p.degree;
    double tempcoef[tempdeg + 1];
    for(int i=0; i<=p.degree; i++){
        tempcoef[i] = p.coefficients[i] * c;
    }
    return Polynomial(tempdeg, tempcoef);
}
Polynomial& Polynomial::operator+= (const Polynomial &p){
    *this = *this + p;
    return *this;
}
Polynomial& Polynomial::operator-= (const Polynomial &p){
    *this = *this - p;
    return *this;
}
Polynomial& Polynomial::operator*= (const Polynomial &p){
    *this = *this * p;
    return *this;
}
Polynomial& Polynomial::operator*= (double c){
    *this = *this * c;
    return *this;
}

double Polynomial::operator () (double x) const{
    double value = coefficients[degree];
    for(int i=degree-1; i>=0; i--){
        value = value * x + coefficients[i];
    }
}

double Polynomial::operator [] (int i) const{
    if(i<0 || i>degree){
        throw "Incorrect index";
    }
    return coefficients[i];
}

Polynomial::~Polynomial(){
    delete[] coefficients;
}
