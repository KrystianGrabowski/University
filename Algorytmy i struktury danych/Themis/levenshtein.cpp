#include<iostream>
#include <algorithm> 

void arrayinit(int l1, int l2, int **arr){
    for (int i=0; i<l1+1; i++){
        arr[i][0] = i;
    }
    for (int j=0; j<l2+1; j++){
        arr[0][j] = j;
    }
}

int levensthein(int l1, int l2, char *a, char *b){
    int **arr;
    arr = new int*[l1+1];
    for (int i=0; i<l1+1; i++){
        arr[i] = new int[l2+1];
    }
    arrayinit(l1, l2, arr);
    for (int i=1; i<l1+1; i++){
        for (int j=1; j<l2+1; j++){
            int cost = (a[i] == b[j]) ? 0 : 2;
            arr[i][j] = std::min(arr[i][j-1]+1, std::min(arr[i-1][j]+1, arr[i-1][j-1] + cost)); 
        }
    }
    return arr[l1][l2];
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
    return 0;
}