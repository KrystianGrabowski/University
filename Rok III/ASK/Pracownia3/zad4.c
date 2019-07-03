#include<stdio.h>
#include <stdint.h>

uint64_t sqrf(uint32_t);

int main(){
  printf("%lx", sqrf(0b00111111101000000000000000000000));
  return 0;
}
