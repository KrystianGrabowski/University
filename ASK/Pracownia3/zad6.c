#include<stdio.h>
#include <stdint.h>
#define Array_Size 10

typedef struct {
  uint32_t n;
  uint8_t digits[Array_Size];
} bignum_t;


int64_t insert_sort(long *first, long *last);


int main(){
    long arr[5] = {3, 4, 2, 1, 4};
    for (int i=0; i<5; i++){
      printf(" %ld ", arr[i]);
    }
    insert_sort(arr, &arr[4]);

    printf("\n");
    for (int i=0; i<5; i++){
      printf(" %ld ", arr[i]);
    }
    return 0;
}