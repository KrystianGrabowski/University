#include<iostream>
#include <algorithm> 

void arrayinit(int l2, int *arr){
    for (int j=0; j<l2+1; j++){
        arr[j] = j;
    }
}

int levensthein(int l1, int l2, char *a, char *b){
    int *arr1 = new int[l2+1];
    int *arr2 = new int[l2+1];
    arrayinit(l2, arr1);
    for (int i=1; i<l1+1; i++){
        arr2[0] = i;
        for (int j=1; j<l2+1; j++){
            int cost = (a[i] == b[j]) ? 0 : 2;
            arr2[j] = std::min(arr2[j-1]+1, std::min(arr1[j]+1, arr1[j-1] + cost)); 
        }
        std::swap(arr1, arr2);
    }
    int res = arr1[l2];
    delete[] arr1;
    delete[] arr2;
    return res;
}


int main(){
    int l1, l2;
    char *a, *b;
    scanf("%d", &l1);
    a = new char[l1+1];
    for (int i=0; i<l1+1; i++){
        char c;
        scanf("%c", &a[i]);
    }
    scanf("%d", &l2);
    b = new char[l2+1];
    for (int i=0; i<l2+1; i++){
        char c;
        scanf("%c", &b[i]);
    }
    printf("%d\n", levensthein(l1, l2, a, b));
    delete[] a;
    delete[] b;
    return 0;
}