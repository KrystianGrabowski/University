#include<iostream>
#include <algorithm> 

void arrayinit(int l2, int *arr){
    for (int j=0; j<l2+1; j++){
        arr[j] = 0;
    }
}

int lcs_length(int l1, int l2, char *seq1, char *seq2){
    int *arr1 = new int[l2+1];
    int *arr2 = new int[l2+1];
    arrayinit(l2, arr1);
    for (int i=1; i<l1+1; i++){
        arr2[0] = 0;
        for (int j=1; j<l2+1; j++){
            if (seq1[i] == seq2[j]){
                arr2[j] = arr1[j-1] + 1;
            }
            else{
                arr2[j] = std::max(arr1[j], arr2[j-1]);
            }
        }
        std::swap(arr1, arr2);
    }
    int res = arr1[l2];
    delete[] arr1;
    delete[] arr2;
    return res;
}

void read_string_with_firstempty(int len, char *arr){
    arr[0] = ' ';
    int k = 1;
    while (k < len+1){
        char c;
        scanf("%c", &c);
        if (c != ' ' && c != '\n'){
            arr[k] = c;
            k++;
        }
    }
}

int main(){
    int l1, l2, n;
    char *seq1, *seq2;
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        scanf("%d", &l1);
        seq1 = new char[l1+1];
        read_string_with_firstempty(l1, seq1);
        scanf("%d", &l2);
        seq2 = new char[l2+1];
        read_string_with_firstempty(l2, seq2);
        printf("%d\n", lcs_length(l1, l2, seq1, seq2));
        delete[] seq1;
        delete[] seq2;
    }
    return 0;
}