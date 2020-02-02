#include<stdio.h>

int main(){
    int t;
    scanf("%d", &t);
    int binary[32];
    int iter;
    long long int val, res;
    int a, b, m;
    for (int i=0; i<t; i++){
        scanf("%d %d %d",&a, &b, &m);
        iter = 0;
        while (b>0){
            binary[iter++] = b % 2;
            b = b / 2;
        }
        int ii = 0;
        val = a % m;
        res = 1;
        while (ii < iter){
            if (binary[ii++] == 1){
                res = (res * val) % m;
            }
            val = (val * val) % m;
        }
        printf("%lld\n", res);
    }
    return 0;
}