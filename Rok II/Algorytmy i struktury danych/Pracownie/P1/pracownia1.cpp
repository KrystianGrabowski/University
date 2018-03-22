#include<iostream>
#include <stdio.h>

int main(){

  int a = 0;
  int b = 0;
  if(scanf("%d %d", &a, &b) != 2){
    printf("ERROR");
  }
  int i = a;
  if (a > b){
    a = b;
    b = i;
  }
  i = a;
  while (i <= b){
    printf("%d\n", i );
    i++;
  }

  return 0;
}
