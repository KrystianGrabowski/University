#include<stdio.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    int c;

    for (c=a; c%2018!=0; c++){}
    while(c <= b){
        printf("%d ", c);
        c += 2018;
    }
    return 0;
}