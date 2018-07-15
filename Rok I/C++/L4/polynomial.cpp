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

Polynomial::~Polynomial(){
    delete[] coefficients;
}
