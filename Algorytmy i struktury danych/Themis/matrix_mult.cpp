#include<iostream>
#include<algorithm>

int arr[200];
int result[200][200];
/*
int optimal_matrix_mult(int i, int j){
    if(j == i){
        return 0;
    }
    int opt = INT32_MAX;
    for(int k=i; k<j; k++){
        opt = std::min(opt, (arr[i] * arr[k+1] * arr[j+1]) + optimal_matrix_mult(i, k) + optimal_matrix_mult(k+1, j));
    }
    return opt;
}*/

int optimal_matrix_mult_dynamic(int n){
    for(int i=0; i<n+1; i++){
        result[i][i] = 0;
    }
    for(int i=1; i<=n; i++){
        for(int j=0; j+i<=n; j++){
            int opt = INT32_MAX;
            for(int k=j; k<j+i; k++){
                opt = std::min(opt, (arr[j] * arr[k+1] * arr[j+i+1]) + result[j][k] + result[k+1][j+i]);
            }
            result[j][j+i] = opt;
        }
    }
    return result[0][n];
}

int main(){
    int t, n;
    scanf("%d", &t);
    for (int i=0; i<t; i++){
        scanf("%d", &n);
        for(int i=0; i<n+1; i++){
            scanf("%d", &arr[i]);
        }
        printf("%d\n", optimal_matrix_mult_dynamic(n-1));
    }
    return 0;
}