#include <iostream>
#include <stdio.h>
#include <algorithm>


int generate_answer(int **combinations, int *array, int n, int m){
    int iter_m = m;
    int iter_n = n;
    while(iter_m != 0){
        if (iter_n<0){
            printf("klops...");
            break;
        }
        if (iter_n != 0 && array[iter_n]>=iter_m && (combinations[iter_n][iter_m] != 1 + combinations[iter_n][iter_m-array[iter_n]])){
            iter_n -= 1;
        }
        else if (iter_m >= array[iter_n] ){
            printf("%d ", array[iter_n]);
            iter_m -= array[iter_n];
            }
            else {
                iter_n -= 1;
            }
    }
    return 0;
}

int change_exists(int *array, int size, int amount){
    int **combinations = new int*[size];
    for (int i=0; i<size; i++){
        combinations[i] = new int[amount+1];
        combinations[i][0] = 0;
        for (int j=1; j<amount+1; j++){
            combinations[i][j] = INT32_MAX;
        }
    }
    int end = -1;
    for (int i=0; i<size; i++){
        if (array[i] > amount){
            break;
        }
        end++;
        for (int j=1; j<amount+1; j++){
            if (j>=array[i]){
                if (i!=0 && (1 + combinations[i][j-array[i]] > combinations[i-1][j])){
                    combinations[i][j] = combinations[i-1][j];
                }
                else{
                    combinations[i][j] = 1 + combinations[i][j-array[i]];
                }
            }
            else if (i!=0) {
                combinations[i][j] = combinations[i-1][j];
            }
        }
    }
    generate_answer(combinations, array, end, amount);
    for (int i=0; i<size; i++){
        delete [] combinations[i];
    }
    delete [] combinations;
    return 0;
}

int main(){
    int n, amount;
    int *array;
    scanf("%d", &n);
    array = new int[n];
    for (int i=n-1; i>=0; i--){
        scanf("%d", &array[i]); 
    }
    scanf("%d", &amount);
    change_exists(array, n, amount);
    delete [] array;
    return 0;
}
/*
100 100 99 98 97 96 95 94 93 92 91 90 89 88 87 86 85 84 83 82 81 80 79 78 77 76 75 74 73 72 71 70 69 68 67 66 65 64 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
*/