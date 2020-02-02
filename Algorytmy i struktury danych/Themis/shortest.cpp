#include <iostream>
#include <stdio.h>
#include <algorithm>    // std::sort
#include <math.h>

struct Point{
    double x0;
    double y0;
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

double distance(Point p1, Point p2){
    return sqrt ( pow((p1.x0 - p2.x0), 2) + pow((p1.y0 - p2.y0), 2) ); 
}

Pair shortest(Point *arr, int size){
    double min = MAXFLOAT;
    double dist;

    Pair p;
    for (int i=0; i<size; i++){
        for (int j=i+1; j<size; j++){
            dist = distance(arr[i], arr[j]);
            if (dist < min){
                min = dist;
                p.p1 = arr[i];
                p.p2 = arr[j];
            }
        }
    }
    return p;
}

Pair divline_shortest(Point *arr, int size){
    double min = MAXFLOAT;
    double dist;
    int b;
    Pair p;
    for (int i=0; i<size; i++){
        if (i+8>size){
            b = size;
        }
        else{
            b = i+8;
        }
        for (int j=i+1; j<b; j++){
            dist = distance(arr[i], arr[j]);
            if (dist < min){
                min = dist;
                p.p1 = arr[i];
                p.p2 = arr[j];
            }
        }
    }
    return p;
}

Pair dac(Point *array, int a, int b){
    int size = (b-a);
    if (size == 1){
        Pair p;
        p.p1.x0 = MAXFLOAT;
        p.p1.y0 = MAXFLOAT;
        p.p2.x0 = MAXFLOAT;
        p.p2.y0 = MAXFLOAT;
        return p;
    }
    if(size > 4){
        int middle = a + ((b - a) /2);
        Pair p1 = dac(array, a, middle);
        Pair p2 = dac(array, middle, b);
        Pair pf = (distance(p1.p1, p1.p2) > distance(p2.p1, p2.p2) ? p2 : p1);
        double dist = distance(pf.p1, pf.p2);
        
        int i = 0;
        int iter = middle;
        Point points[b-a+1];
        while( (iter >= a) && ((array[middle].x0 - array[iter].x0) < dist)){
            points[i] = array[iter];
            i++;
            iter--;
        }
        iter = middle + 1;
        while( (iter < b) && ((array[iter].x0 - array[middle].x0) < dist)){
            points[i] = array[iter];
            i++;
            iter++;
        }
        
        std::sort(points, points+i, comparePointY); 
        bool i_ne0 = false;
        Pair pf1;
        if (i>1){
            i_ne0 = true;
            pf1 = divline_shortest(points, i);
        }
        if(i_ne0){
            Pair p_final = (distance(pf.p1, pf.p2) > distance(pf1.p1, pf1.p2) ? pf1 : pf);
            return p_final;
        }
        return pf;
       
    }
    else{
        Point points[b-a+1];
        for (int i=a; i<=b; i++){
            points[i-a] = array[i];
        }
        return shortest(points, b-a+1);
    }

    
}

int main(){
    int n;
    scanf("%d", &n);
    Point arr[n];
    for (int i=0; i<n; i++){
        Point p;
        scanf("%lf %lf", &p.x0, &p.y0);
        arr[i] = p;
    }
    int n1 = sizeof(arr)/sizeof(arr[0]);
    std::sort(arr, arr+n1, comparePointX); 
    Pair pair = dac(arr, 0, n);
    double d = distance(pair.p1, pair.p2);
    printf("%.5f", d);
    return 0;
}

