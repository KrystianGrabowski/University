#include<iostream>
#include"polynomial.h"

int main(){
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
    return 0;
}
