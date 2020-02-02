#include<stdio.h>
#include <stdint.h>
#define Array_Size 10

typedef struct {
  uint32_t n;
  uint8_t digits[Array_Size];
} bignum_t;


int64_t add_bignum(bignum_t *a, bignum_t *b, bignum_t *r);


int main(){
    bignum_t b;
    b.n = 9;
    b.digits[0] = 0xde;
    b.digits[1] = 0xc0;
    b.digits[2] = 0xad;
    b.digits[3] = 0x0b;
    bignum_t a;
    a.n = 8;
    a.digits[0] = 0x00;
    a.digits[1] = 0x00;
    a.digits[2] = 0x00;
    a.digits[3] = 0xd3;
    bignum_t r;
    r.n = 10;

    /*bignum_t b;
    b.n = 10;
    b.digits[0] = 0xff;
    b.digits[1] = 0xff;
    b.digits[2] = 0xff;
    b.digits[3] = 0xff;
    b.digits[4] = 0xff;
    b.digits[5] = 0xff;
    b.digits[6] = 0xff;
    b.digits[7] = 0xff;
    b.digits[8] = 0xff;
    b.digits[9] = 0xff;
    bignum_t a;
    a.n = 10;
    a.digits[0] = 0xff;
    a.digits[1] = 0xff;
    a.digits[2] = 0xff;
    a.digits[3] = 0xff;
    a.digits[4] = 0xff;
    a.digits[5] = 0xff;
    a.digits[6] = 0xff;
    a.digits[7] = 0xff;
    a.digits[8] = 0xff;
    a.digits[9] = 0xff;
    bignum_t r;
    r.n = 12; */

    /* bignum_t b;
    b.n = 10;
    b.digits[0] = 0xff;
    b.digits[1] = 0xff;
    b.digits[2] = 0xff;
    b.digits[3] = 0xff;
    b.digits[4] = 0xff;
    b.digits[5] = 0xff;
    b.digits[6] = 0xff;
    b.digits[7] = 0xff;
    b.digits[8] = 0xff;
    b.digits[9] = 0xff;
    bignum_t a;
    a.n = 1;
    a.digits[0] = 0x01;
    bignum_t r;
    r.n = 12; */

    /*bignum_t a;
    a.n = 8;
    a.digits[0] = 0x10;
    a.digits[1] = 0x10;
    bignum_t b;
    b.n = 8;
    b.digits[0] = 0xf0;
    b.digits[1] = 0xf0;
    bignum_t r;
    r.n = 10;*/
    printf("%lx", add_bignum(&a, &b, &r));
    return 0;
}