#include<stdio.h>
#include<limits.h>
#include <stdint.h>
#include<math.h>

void swap()
{
    int32_t a = INT_MAX;
    int32_t b = 5;
	a = a+b;
	b = a-b;
	a = a-b;
    printf("%d <a, %d <b",a, b);
}

/*int32_t overunderflow(int32_t x, int32_t y){
    int N = 32 ;
    return ((((x + y) ^ x) & ((x + y) ^ y)) >> (N - 1)) & 1;
}*/

int32_t overunderflow(int32_t x, int32_t y){
    int N = 32 ;
    return ((~(x^y) & ((x+y)^x) & (1<<(N-1)) >> (N-1))) & 1;
}

int32_t quickadd(int32_t x, int32_t y){
    int s = (x & 0x7F7F7F7F) + (y &0x7F7F7F7F);
    s = ((x+y) & 0x80808080) + s;
    return s;
}

int32_t quicksub(int32_t x, int32_t y){
    int s = (x | 0x80808080) - (y & 0x7F7F7F7F);
    s = ((x-y) | 0x7F7F7F7F);
    return s;
}

int32_t threefourths(int32_t x){
    return (x>>2) + (x>>1) + ((x&3 == 3));
}

uint32_t comparison(int32_t x, int32_t y){
    return (((x-y) ^ ((x^y) & ((x-y) ^ x))) >> 31) & 1;
}

int32_t comparisonU(uint32_t x, uint32_t y){
    return (((~x & y) | ((~x | y) & (x - y))) >> 31);
}

int32_t comp(int32_t x, int32_t y){
    return ((x>>1) - (y>>1) - (~x & y & 1)) >> 31 & 1;
}

uint32_t compu(uint32_t x, uint32_t y){
    return ((x>>1) - (y>>1) - (~x & y & 1)) >> 31 & 1;
}

/*
int32_t absT(int32_t x){
    int y = x >> 31;
    //return (x^y) - y;
    //return (x + y) ^ y;
    return x - ((x<<1) & y);
}*/

int32_t absT(int32_t x){
    return ((x >> 31) & (-x)) + (~(x >> 31) & x);
}

int32_t odd_ones(int32_t x){
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

/*
int32_t signum(int32_t x){
    int32_t h =((~x +1)>>31);
    int32_t y = h >> 31;
    return ((x>>31) | (h^y) - y );
}

int32_t signum(int32_t x){
    int32_t h =((~x +1)>>31);
    return ((x>>31) | (~h + 1) );
}*/

int32_t signum(int32_t x){
    return (x>>31) | ((-x >> 31) & 1);
}



int main(){
    int32_t x, y;
    x = INT_MIN;
    //printf("%d\n", x);
    //printf("%d\n", x - 1);
    printf("EX1 %d\n",(x > 0) || (x - 1 < 0));

    x = 7;
    //printf("%d\n", (x<<29));
    int32_t i = 0;
    /*while(i >= INT_MIN){
        if(!((i & 7) != 7 || (i << 29 < 0))){
            printf("%d ", i);
            scanf("%d", &y);
        }
        i++;
    }*/
    printf("EX2 %d\n", (x & 7) != 7 || (x << 29 < 0));

    i = 0;
    /*while(i <= INT_MAX){
        if((i*i) < 0){
            printf("%d ", i);
            scanf("%d", &y);
        }
        i++;
    }*/
    x = 46341;
    //printf("%d\n", x*x);
    printf("EX3 %d\n", ((x * x) >= 0));

    i=0;
    /*while(i <= INT_MAX){
        if(!(i < 0 || -i <= 0)){
            printf("%d ", i);
            scanf("%d", &y);
        }
        i++;
    }*/
    printf("EX4 %d\n", (x < 0 || -x <= 0));


    i=0;
    /*while(i <= INT_MAX){
        if(!(i < 0 || -i <= 0)){
            printf("%d ", i);
            scanf("%d", &y);
        }
        i++;
    }*/
    x = INT_MIN;
    printf("EX4 %d\n", (x > 0 || -x >= 0));

    i=0;
    /*while(i <= INT_MAX){
        if(!((x | -x) >> 31 == -1)){
            printf("%d ", i);
            scanf("%d", &y);
        }
        i++;
    }*/
    x = 0;
    printf("EX5 %d\n", (x | -x) >> 31 == -1);

    i=0;
    /*while(i <= INT_MAX){
        if(!((x | -x) >> 31 == -1)){
            printf("%d ", i);
            scanf("%d", &y);
        }
        i++;
    }
    x = 0;
    printf("EX5 %d\n", (x | -x) >> 31 == -1);*/

    x = -100;
    y = 132312;
    printf("%u %u", (uint32_t)y + (uint32_t)x, (uint32_t)(x + y));
    x + y == (uint32_t)y + (uint32_t)x;
    printf("EX6 %d\n", x + y == (uint32_t)y + (uint32_t)x);

    x = INT_MAX;
    y = INT_MAX;
    printf("EX7 %d\n", x * ~y + (uint32_t)y * (uint32_t)x == -x);

    swap();
    printf("\nFLOW%d\n", overunderflow(INT_MIN, 0));
    printf("%d\n", quickadd(554, 212));
    printf("%d\n", quicksub(554, 212));
    printf("%d\n", threefourths(14));
    printf("%d \n", (1<<31)>>1);
    printf("%d\n", comparison(INT_MIN, 2));
    printf("%d\n", comparisonU(0,5));
    printf("ABS %d\n", absT(-112));
    printf("signum %d %d %d (mniejsze, równe, wieksze 0)\n", signum(-33), signum(0), signum(421));

    printf("zadanie9 %d\n", odd_ones(7));

    printf("COmp s %d\n", comp(1,2));
    printf("CompU u %u\n", compu(1, 222));
    return 0;
}