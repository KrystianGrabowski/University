#include<stdio.h>

float FastInvSqrt(float x) {
  float xhalf = 0.5f * x;
  printf("%d\n", (int)(x));     // 0 10000000 10101010001111010111000 = 1079320248
  int i = *(int*)&x;         // evil floating point bit level hacking castujemy wskaźniki dzięki czemu inaczej interpretujemy liczbę 
  //i = 0x5f3759df - (i >> 1);  // what the fuck?
  //x = *(float*)&i;
  //x = x*(1.5f-(xhalf*x*x));
  return i;
}

int main(){
    float a = FastInvSqrt(2);
    printf("%f\n", a);
    return 0;
}