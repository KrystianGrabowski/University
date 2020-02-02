#include<iostream>
#include"polynomial.h"

int main(){
    //constructors
    Polynomial cons1;
    std::cout << "Cons1: " << cons1 << std::endl;
    double elem[4] = {4,3,4,3};
    Polynomial cons2(3,elem);
    std::cout << "Cons2: " << cons2 << std::endl;
    Polynomial cons3{96,5,22,1};
    std::cout << "Cons3: " << cons3 << std::endl;
    Polynomial cons4(cons2);
    Polynomial cons5(std::move(cons3));
    std::cout << "Cons4: " << cons4 << std::endl;
    std::cout << "Cons5: " << cons5 << std::endl;
    std::cout << "\n";

    //assignment
    Polynomial aop;
    aop = cons2;
    std::cout << "Assig1: " << aop << std::endl;
    Polynomial aop1;
    aop1 = std::move(cons4);
    std::cout << "Assig2: " << aop1 << std::endl;
    std::cout << "\n";


    //+ - * *
    Polynomial a{2,2,2,2,2,2};
    Polynomial b{1,1,1,1};
    std::cout << "Add1: " << a + b << std::endl;
    std::cout << "Sub1: " << a - b << std::endl;
    std::cout << "Add1: " << b + a << std::endl;
    std::cout << "Sub1: " << b - a << std::endl;
    Polynomial m1{-4,1,-2,2};
    Polynomial m2{0,-3,1};
    std::cout <<"Mult1: " << m1*m2 << std::endl;
    Polynomial m3{0,3,-6,0,0,4};
    Polynomial m4{3,0,-2,0,5};
    std::cout << "Mult2: " << m3*m4 << std::endl;
    Polynomial mc1{1,-5,4};
    Polynomial mc2{1,18,-2,-7};
    std::cout << "Multconst1: " << mc1 * -6 << std::endl;
    std::cout << "Multconst2: " << mc2 * -2 << std::endl;

    std::cout << "\n";
    //+= -= *= *=
    a += b;
    std::cout << "Add1=: "<< a << std::endl;
    a -= b;
    std::cout << "Sub1=: "<< a << std::endl;
    a -= b;
    std::cout << "Sub2=: "<< a << std::endl;
    m1 *= m2;
    std::cout << "Mult1=: " << m1 << std::endl;
    m3 *= m4;
    std::cout << "Mult2=: " << m3 << std::endl;
    mc1 *= -6;
    mc2 *= -2;
    std::cout << "Multconst=1: " << mc1 << std::endl;
    std::cout << "Multconst=2: " << mc2 << std::endl;

    //Horner
    Polynomial h1{1,4,-5,0,2};
    std::cout << h1(3/2.0) << std::endl;
    Polynomial h2{-1,0,2,-5,3};
    std::cout << h2(-2) << std::endl;

    std::cout << h2[0] << std::endl;
    std::cout << h1[4] << std::endl;
    std::cout << h1[2] << std::endl;

    return 0;
}
