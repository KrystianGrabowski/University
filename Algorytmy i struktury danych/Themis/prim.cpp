#include <iostream>
#include <stdio.h>
#include <algorithm>    // std::sort
#include <math.h>

struct Point{
    int x0;
    int y0;
};

struct Pair{
    Point p1;
    Point p2;
};


bool comparePointX(Point p1, Point p2) 
{ 
    return p1.x0 < p2.x0;
}

bool comparePointY(Point p1, Point p2) 
{ 
    return p1.y0 < p2.y0;
}

float distance(Point p1, Point p2){
    return sqrt ( pow((p1.x0 - p2.x0), 2) + pow((p1.y0 - p2.y0), 2) ); 
}

Pair dac(Point *array, int n){
    Pair p;
    double min = INT32_MAX;
    double dist;
    for (int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            dist = distance(array[i], array[j]);
            printf("%d %d %d %d %lf\n", array[i].x0, array[i].y0, array[j].x0, array[j].y0, dist);
            if (dist < min){
                min = dist;
                p.p1 = array[i];
                p.p2 = array[j];
            }
        }
    }
    return p;
    
}

int main(){
    int n;
    scanf("%d", &n);
    Point arr[n];
    for (int i=0; i<n; i++){
        Point p;
        scanf("%d %d", &p.x0, &p.y0);
        arr[i] = p;
    }
    int n1 = sizeof(arr)/sizeof(arr[0]);
    //std::sort(arr, arr+n1, comparePointX); 
    Pair pair = dac(arr, n);
    float d = distance(pair.p1, pair.p2);
    printf("%.5f", d);
    return 0;
}

