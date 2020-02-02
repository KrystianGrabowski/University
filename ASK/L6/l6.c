#include <stdio.h>

#define B 5
#define A 7

typedef struct {
    int x[A][B];
    long y;
} str1;

typedef struct {
    char array[B];
    int t;
    short s[A];
    long u;
} str2;

int main(){
    printf("%ld\n", sizeof(str2));
    printf("%ld\n", sizeof(str1));
    return 0;
}