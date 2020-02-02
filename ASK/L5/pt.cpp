#include<iostream>

uint32_t my_puzzle3(uint32_t n, uint32_t d){
    uint64_t a = n;
    uint64_t b = d;
    b <<= 32;
    uint32_t mask = 0x80000000;
    uint32_t result = 0;
    for(int i = 32; i != 0; i--){
        a += a;
        uint64_t c = a;
        bool test = 0;
        if (c < b) test = 1;
        c -= b;
        if (!test){
            result |= mask;
            a = c;
        }
        mask >>= 1;
    }
    return result;
}

int main(){
    /*char a[] = "bdaaaaacaaa";
    char b[] = "aab";
    printf("%ld", puzzle2(a,b));*/
    printf("%d\n", my_puzzle3(250,1));
    return 0;
}