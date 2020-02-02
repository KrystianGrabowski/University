#include <stdio.h>
#include <stdint.h>

void bin(unsigned n) 
{ 
    /* step 1 */
    if (n > 1) 
        bin(n/2); 
  
    /* step 2 */
    printf("%d", n % 2); 
}  


int zad1(uint32_t x, uint32_t i, uint32_t k){
    bin(x);
    printf("\n");
    uint32_t c = (x & (1<<i)) >> i;
    x = (x & ~(1<<k)) | (c << k);
    bin(x);
    return 0;
}

int zad2(uint32_t x){

}

struct A {
    int8_t a;
    void *b;
    int8_t c;
    int16_t d;
};

struct A1 {
    int8_t a;
    int8_t c;
    int16_t d;
    void *b;
};

struct B {
    uint16_t a;
    double b;
    void *c;
};

struct B1 {
    void *c;
    uint16_t a;
    double b;
};

int fun1() 
{ 
    static int zmienna = 1;
    zmienna = zmienna + 3;
    return zmienna;
} 

void arrayTos(int *arr){
    printf("\n[");
    for(int j=0; j<5; j++){
        printf("%d, ", arr[j]);
    }
    printf("]\n");
}

int arrayincdec(){
    int a[5] = { 5, 1, 15, 20, 25 } ;
    int i = 2;
    a[i++] -= 66;
    arrayTos(a);
    printf("%d\n", i);
    return 0;
}


int count_one(unsigned x) { 
    x = (x & 0x55555555) + (x>>1 & 0x55555555);
    x = (x & 0x33333333) + (x>>2 & 0x33333333);
    x = (x & 0x0f0f0f0f) + (x>>4 & 0x0f0f0f0f);
    x = (x & 0x00ff00ff) + (x>>8 & 0x00ff00ff);
    x = (x & 0x0000ffff) + (x>>16 & 0x0000ffff);
    return x;
}

int countSetBits(unsigned int n)
{
  n = n - ((n >> 1) & 0x55555555);
  n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
  n = (n + (n >> 4)) & 0x0F0F0F0F;
  n = n + (n >> 8);
  n = n + (n >> 16);
  return n & 0x0000003F;
}

void secret(uint8_t *to, uint8_t *from, size_t count) {
    size_t n = (count + 7) / 8;
    switch (count % 8) {
        case 0: do { *to++ = *from++;
        case 7: *to++ = *from++;
        case 6: *to++ = *from++;
        case 5: *to++ = *from++;
        case 4: *to++ = *from++;
        case 3: *to++ = *from++;
        case 2: *to++ = *from++;
        case 1: *to++ = *from++;
    } while (--n > 0);
    }
}

void secret1(uint8_t *to, uint8_t *from, size_t count) {
    static void *array[] = { &&s0, &&s1, &&s2, &&s3, &&s4, &&s5, &&s6, &&s7 };
    size_t n = (count + 7) / 8;
    goto *array[count%8];
    s0:
        *to++ = *from++;
    s7:
        *to++ = *from++;
    s6:
        *to++ = *from++;
    s5:
        *to++ = *from++;
    s4:
        *to++ = *from++;
    s3:
        *to++ = *from++;
    s2:
        *to++ = *from++;  
    s1:
        *to++ = *from++;
    if (--n > 0) goto *array[0]; 
}

int main()
{
    struct A a0;
    struct A1 a1;
    struct B b0;
    struct B1 b1;

    zad1(18, 0, 1);
    printf("\n%u", sizeof(a0));
    printf("\n%p", (&(a0.a)));
    printf("\n%p", (&(a0.b)));
    printf("\n%p", (&(a0.c)));
    printf("\n%p", (&(a0.d)));
    printf("\n");
    printf("\n%u", sizeof(a1));
    printf("\n%p", (&(a1.a)));
    printf("\n%p", (&(a1.b)));
    printf("\n%p", (&(a1.c)));
    printf("\n%p", (&(a1.d)));

    printf("\n\nB");
    printf("\n%u", sizeof(b0));
    printf("\n%p", (&(b0.a)));
    printf("\n%p", (&(b0.b)));
    printf("\n%p", (&(b0.c)));
    printf("\n");
    printf("\n%u", sizeof(b1));
    printf("\n%p", (&(b1.a)));
    printf("\n%p", (&(b1.b)));
    printf("\n%p", (&(b1.c)));

    printf("\n%d", fun1());
    printf("\n%d", fun1());

    printf("\n\n");
    printf("%d\n", arrayincdec());

    printf("\n\nCOUNT\n");
    printf("%d\n", count_one(123456789));
     printf("%d", countSetBits(1023));

    uint8_t array1[6] = {1,2,3,4,5,6};
    uint8_t array2[6] = {61,66,67,68,69,70};
    int d = 0;
        printf("\narray\n");
    while (array1[d] != '\0') {
        printf("%d ", array1[d]);
        d++;
    }
    secret1(array1, array2, 6);
    int c = 0;
    printf("\narray\n");
    while (array1[c] != '\0') {
        printf("%d ", array1[c]);
        c++;
    }
    return 0;
}