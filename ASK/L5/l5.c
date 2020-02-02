#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t maxofthree(int64_t, int64_t, int64_t);

int lsr(int x, int n)
{
  return (int)((unsigned int)x >> n);
}


int puzzle4(long *a, long v, uint64_t s, uint64_t e){
    long rax = e;
    uint64_t rdx = s;
    uint64_t rcx = e;
    rax = rax - rdx;
    rax = rax >> 1;
    rax += rdx;
    if (rdx <= rcx){
        long r8 = *(a + (rax * 8));
        if (r8 == v){
            return rax;
        }
        else{
            if (r8 > v){
                rcx = *(&rax - 1);
                return puzzle4(a, v, rdx, rcx);
                
            }
            else{
                rdx = *(&rax + 1);
                return puzzle4(a, v, rdx, e);
            }
        }
    }
    else{
        rax = -1;
        return rax;
    }
}

uint32_t puzzle3(uint32_t n, uint32_t d){
    uint64_t rdi = n;
    uint64_t rsi = d;
    rsi = rsi << 32;
    uint32_t edx = 32;
    uint32_t ecx = 0x80000000;
    uint32_t eax = 0;
    long r8;

    while (edx != 0){
        rdi += rdi;
        r8 = rdi - rsi;
        if (r8 < 0){
            ecx = ecx >> 1;
            edx --;
        }
        else{
            eax = eax | ecx;
            rdi = r8; 
            ecx = ecx >> 1;
            edx --;
        }
    }
    return eax;
}

long puzzle2(char *s, char *d){
    char *ptr1 = s;
    char *ptr2 = d; 
    while(*ptr2 != 0){
        if (*ptr1 == *ptr2){
            ptr1++;
            ptr2 = d;
        }
        else{
            ptr2++;
        }
    }
    return ptr1 - s;
}


int main(){
    /*char a[] = "bdaaaaacaaa";
    char b[] = "aab";
    printf("%ld", puzzle2(a,b));
    printf("%d\n", puzzle3(250,1));
        printf("%ld\n", maxofthree(1, -4, -7));
    printf("%ld\n", maxofthree(2, -6, 1));
    printf("%ld\n", maxofthree(2, 3, 1));
    printf("%ld\n", maxofthree(-2, 4, 3));
    printf("%ld\n", maxofthree(2, -6, 5));
    printf("%ld\n", maxofthree(2, 4, 6));*/
    long a[5] = {2, 1, 4, 6, 9};
    printf("%d\n", puzzle4(a, 1, 0 , 4));
    return 0;
}
