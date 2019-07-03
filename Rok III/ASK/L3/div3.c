#include<stdio.h>
#include<math.h>
#include <stdint.h>
#include <inttypes.h>


int32_t three(int32_t n){
    int64_t magic = 0x55555556;
    int32_t q = magic * n >> 32;
    q = ((q >> 31 & 1) + q);
    return q;
}

int main(){
    printf("%d\n", three(-16));
}
