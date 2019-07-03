#include <stdio.h>

//wyzeruj k-ty bit zmiennej x
int zad3a (int x, int k)
{
    return x & ~(1<<k);
}

//ustaw k-ty bit zmiennej x
int zad3b (int x, int k)
{
    return x | (1<<k);
}

//zaneguj k-ty bit zmiennej x
int zad3c (int x, int k)
{
    return x ^ (1<<k);
}


//x * 2^y
int zad4a (int x, int k)
{
    return x<<k;
}

//podłoga z x / 2^y
float zad4b (int x, int k)
{
    return x>>k;
}

//x mod 2^y
int zad4c (int x, int k)
{
    return x & ~(1<<k);
}

//sufit x / 2^y
float zad4d (int x, int k)
{
    return x>>k;
}

int zad5 (int x)
{
    return x & (x-1);
}


int main()
{
    printf("%d\n", zad3a(10,3));
    printf("%d\n", zad3b(2,3));
    printf("%d\n", zad3c(2,3));

    printf("4a %d\n", zad4a(5,10));
    printf("4b %f\n", zad4b(63, 4));
    printf("4c %d\n", zad4c(33, 5));
    printf("4d %f\n", zad4d(63, 4));

    printf("%d\n", zad5(32));
    printf("%d\n", zad5(31));
    printf("%d\n", zad5(33));



    return 0;
}