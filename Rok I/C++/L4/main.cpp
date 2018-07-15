#include<iostream>
#include"polynomial.h"

int main(){
  Polynomial a{1,2,3,4};
  std::cout << a << "\n";
  std::cin >> a;
  std::cout << a << "\n";
  return 0;
}
