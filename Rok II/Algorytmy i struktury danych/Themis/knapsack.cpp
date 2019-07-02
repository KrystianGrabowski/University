#include <iostream>
#include <stdio.h>
#include <algorithm>

struct item{
    int weight;
    int value;
};

bool compareItems(item i1, item i2)
{
  return i1.weight < i2.weight;
}

int pick(item *array, int size, int available_weight){
    int *combinations1 = new int[available_weight+1];
    int *combinations2 = new int[available_weight+1];
    for (int i=1; i<available_weight+1; i++){
        combinations1[i] = 0;
        combinations2[i] = 0;
    }    

    if (size > 0){
        combinations1[0] = 0;
        combinations2[0] = 0;
    }
    else{
        if (available_weight==0){
            return 0;
        }
    }
    int *ptr1 = combinations1;
    int *ptr2 = combinations2;
    for (int j=1; j<available_weight+1; j++){
        if (j>=array[0].weight){
            ptr1[j] = array[0].value; 
        }
    }
    for (int i=1; i<size; i++){
        for (int j=1; j<available_weight+1; j++){
            if (j>=array[i].weight){
                if (ptr1[j] < ptr1[j-array[i].weight] + array[i].value){
                    ptr2[j] = ptr1[j-array[i].weight] + array[i].value;
                }
                else {
                    ptr2[j] = ptr1[j];
                }
            }
            else{
                ptr2[j] = ptr1[j];
            }
        }
        std::swap(ptr1, ptr2);
    }
    int a = combinations1[available_weight]; 
    delete [] combinations1;
    delete [] combinations2;
    return a;
}

int main(){
    int n, available_weight;
    item *array;
    scanf("%d", &n);
    array = new item[n];
    for (int i=0; i<n; i++){
        scanf("%d %d", &array[i].weight, &array[i].value); 
    }
    std::sort(array, array + n, compareItems); 
    scanf("%d", &available_weight);
    printf("%d\n", pick(array, n, available_weight));

    delete [] array;
    return 0;
}