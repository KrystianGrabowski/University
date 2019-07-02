#include <iostream>
#include <stdio.h>

bool change_exists(int *combinations, int *array, int size, int amount){
    if (size > 0){
        combinations[0] = 0;
    }
    else{
        if (amount==0){
            return true;
        }
    }
    for (int i=0; i<size; i++){
        for (int j=1; j<amount+1; j++){
            if (j>=array[i]){
                if (combinations[j] > combinations[j-array[i]]){
                    combinations[j] = 1 + combinations[j-array[i]];
                }
            }
        }
        if (combinations[amount]!=INT32_MAX){
            return true;
        }
    }
    return combinations[amount] != INT32_MAX;
}

int main(){
    int n, amount;
    int *array;
    scanf("%d", &n);
    array = new int[n];
    for (int i=0; i<n; i++){
        scanf("%d", &array[i]); 
    }
    scanf("%d", &amount);
    int *combinations = new int[amount+1];
    for (int i=1; i<amount+1; i++){
        combinations[i] = INT32_MAX;
    }
    if (change_exists(combinations, array, n, amount)){
        printf("TAK\n");
    }
    else{
        printf("NIE\n");
    }
    delete [] combinations;
    delete [] array;
    return 0;
}