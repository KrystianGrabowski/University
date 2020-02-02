#include<stdio.h>

struct matrixstruct{
    long long int matrix[2][2];
};


struct matrixstruct matrixmult(struct matrixstruct a, struct matrixstruct b, int m){
    struct matrixstruct c;
    c.matrix[0][0] = (a.matrix[0][0] * b.matrix[0][0] + a.matrix[0][1] * b.matrix[1][0]) % m;
    c.matrix[1][0] = (a.matrix[1][0] * b.matrix[0][0] + a.matrix[1][1] * b.matrix[1][0]) % m;
    c.matrix[0][1] = (a.matrix[0][0] * b.matrix[0][1] + a.matrix[0][1] * b.matrix[1][1]) % m;
    c.matrix[1][1] = (a.matrix[1][0] * b.matrix[0][1] + a.matrix[1][1] * b.matrix[1][1]) % m;
    return c;
}

struct matrixstruct matrixpower(struct matrixstruct a, int n, int m){
    if(n == 0){
        struct matrixstruct id;
        id.matrix[0][0] = 1;
        id.matrix[1][0] = 0;
        id.matrix[0][1] = 0;
        id.matrix[1][1] = 1;
        return id;
    }
    struct matrixstruct m1, m2;
    m1 = matrixpower(a, n/2, m);
    m2 = matrixmult(m1, m1, m);
    if (n % 2 == 1){
        m2 = matrixmult(m2, a, m);
    }
    return m2;
}


long long int matrixfib(int n, int m){
    struct matrixstruct x;

    x.matrix[0][0] = 0;
    x.matrix[1][0] = 1;
    x.matrix[0][1] = 1;
    x.matrix[1][1] = 1;

    struct matrixstruct m1;
    m1 = matrixpower(x, n, m);
    return m1.matrix[1][0];
}


int main(){
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; i++){
        int n,m;
        scanf("%d %d", &n, &m );
        printf("%lld\n", matrixfib(n, m));
    }

    return 0;
}