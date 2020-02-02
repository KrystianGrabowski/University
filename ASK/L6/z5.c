#include <stdio.h>
#include <stdint.h>

typedef struct A {
    long u[2];
    long *v;
} SA;

typedef struct B {
    long p[2];
    long q;
} SB;

SB eval(SA s){
    //SB r;
    // r.p[0] = s.u[1] * s.v[0];
    // r.p[1] = s.u[0] - s.v[0];
    // r.q = s.u[0] - s.u[1];
    return (SB){
        {
            s.u[1] * s.v[0],
            s.u[0] - s.v[0]
        },
        s.u[0] - s.u[1]
    };
} 

int64_t wrap(int64_t x, int64_t y, int64_t z){
    SB sb = eval((SA) { {x, y}, &z});
    return (sb.p[1] + sb.p[0]) * sb.q;
}

int main(){
    return 0;
}