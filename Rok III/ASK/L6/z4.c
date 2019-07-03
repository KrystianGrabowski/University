#include <stdio.h>

union elem {
    struct {
        long *p;
        long y;
    } e1;
    struct {
        long x;
        union elem *next;
    } e2;
};

void fun(union elem *a){
    a->e2.x = *(a->e2.next->e1.p) - a->e2.next->e1.y;
}

int main(){
    union elem e;
    long a = 3;
    e.e1.p = &a;
    e.e2.next = &e;
    fun(&e);
    printf("%ld\n", e.e1.y);
    return 0;
}