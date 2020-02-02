#include<stdio.h>
#include <math.h>


void show_heap(int *heap, int heapsize){
    printf("[ ");
    for (int i=0; i<heapsize; i++){
        printf("%d ", heap[i]);
    }
    printf("]\n");
}

int left_child(int i){
    return i * 2;
}

int right_child(int i){
    return (i * 2) + 1;
}

int parent(int i){
    return floor(i / 2);
}

int heap_get(int *heap, int i){
    return heap[i-1];
}

int heap_set(int *heap, int i, int value){
    heap[i-1] = value;
    return 0;
}

int max_heapify(int *heap, int i, int size){
    int l = left_child(i);
    int r = right_child(i);
    int largest;
    if (l <= size && heap_get(heap, l) > heap_get(heap, i)){
        largest = l;
    }
    else{
        largest = i;
    }
    if (r <= size && heap_get(heap, r) > heap_get(heap, largest)){
        largest = r;
    }
    if (largest != i){
        int temp = heap_get(heap, largest);
        heap_set(heap, largest, heap_get(heap, i));
        heap_set(heap, i, temp);
        max_heapify(heap, largest, size); 
    }
    return 0;
}

int build_max_heap(int *heap, int size){
    for (int i=floor(size/2); i>0; i--){
        max_heapify(heap, i, size);
    }
    return 0;
}

int heap_sort(int *heap, int size){
    build_max_heap(heap, size);
    for (int i=size; i>1; i--){
        int temp = heap_get(heap, 1);
        heap_set(heap, 1, heap_get(heap, i));
        heap_set(heap, i, temp);
        max_heapify(heap, 1, i-1);
    }
}

int get_down(int *heap, int i, int size){
    int l = left_child(i);
    int r = right_child(i);
    if (l > size && r > size){
        return i;
    }
    if (l <= size && r <= size){
        if (heap_get(heap, l) > heap_get(heap, r)){
            heap_set(heap, i, heap_get(heap, l));
            return get_down(heap, l, size );   
        }
        else{
            heap_set(heap, i, heap_get(heap, r));
            return get_down(heap, r, size );
        }
    }
    else{
        if (l <= size){
            heap_set(heap, i, heap_get(heap, l));
            return l;
        }
        if (r <= size){
            heap_set(heap, i, heap_get(heap, r));
            return r;
        }
        
    }
    return 0;
}

int get_up(int *heap, int i, int size){
    int p = parent(i);
    int largest;
    if (heap_get(heap, i) > heap_get(heap, p)){
        int temp = heap_get(heap, i);
        heap_set(heap, i, heap_get(heap, p));
        heap_set(heap, p, temp);
        get_up(heap, p, size);
    }
    return 0;
}

int heap_sort_hole(int *heap, int size){
    build_max_heap(heap, size);
    for (int i=size; i>1; i--){
        int temp = heap_get(heap, 1);
        int position = get_down(heap, 1, i);
        heap_set(heap, position, heap_get(heap, i));
        get_up(heap, position, i);
        heap_set(heap, i, temp);     
    }
}

int main(){
    int heap[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    show_heap(heap, 10);
    build_max_heap(heap, 10);
    show_heap(heap, 10);
    printf("\n");
    int heap2[99] = {76,45,29,4,86,54,72,65,12,42,25,33,96,23,90,82,62,8,93,68,36,92,81,49,80,57,88,56,75,7,69,71,28,47,32,51,13,16,73,11,48,14,3,27,2,97,94,59,84,10,9,43,87,64,38,39,30,58,44,67,61,15,34,70,53,22,99,60,20,19,24,55,21,6,85,91,74,83,52,31,37,98,77,50,66,89,26,40,18,46,41,63,35,17,79,78,95,5,1};
    //show_heap(heap2, 99);
    heap_sort(heap2, 99);
    //show_heap(heap2, 99);
    printf("Hole version\n");
    int heap3[99] = {76,45,29,4,86,54,72,65,12,42,25,33,96,23,90,82,62,8,93,68,36,92,81,49,80,57,88,56,75,7,69,71,28,47,32,51,13,16,73,11,48,14,3,27,2,97,94,59,84,10,9,43,87,64,38,39,30,58,44,67,61,15,34,70,53,22,99,60,20,19,24,55,21,6,85,91,74,83,52,31,37,98,77,50,66,89,26,40,18,46,41,63,35,17,79,78,95,5,1};
    show_heap(heap3, 99);
    heap_sort_hole(heap3, 99);
    show_heap(heap3, 99);
}
