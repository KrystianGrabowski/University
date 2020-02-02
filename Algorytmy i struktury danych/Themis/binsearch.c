#include<stdio.h>
#include<stdint.h>
#include<math.h>

int main(){
    int32_t n,m;
    scanf("%d", &n);
    int array[n];
    for (int i=0; i<n; i++){
        scanf("%d", &array[i]);
    }
    scanf("%d", &m);
    int a, b, c;

    for (int i=0; i<m; i++){
        int q;
        scanf("%d", &q);
        a = 0;
        b = n;
        while(a < b){
            c = (a + b)/2;
            if (array[c] == q && (c == 0 | (c > 0 && array[c-1] != q))){
                a = c;
                break;
            }
            if(array[c] >= q){
                b = c;
            }
            else{
                a = c+1;
            }
        }
        printf("%d ", n-a);
    }

    


    return 0;
}

