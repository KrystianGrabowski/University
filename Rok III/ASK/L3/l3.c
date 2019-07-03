#include<stdio.h>
#include<stdint.h>
#include<limits.h>
void looptest(){
    /*for (int i=INT_MAX; i>INT_MAX-1000; i--){
        for (int j=INT_MAX; j>INT_MAX-1000; j--){
            for (int k=INT_MAX; k>INT_MAX-1000; k--){
                double di = (double)i;
                double dj = (double)j;
                double dk = (double)k;
                if ((di * dj) * dk != di * (dj * dk)){
                    printf("%d %d %d\n", i, j, k);
                    
        }

            }
        }

        

    }*/
}


int main(){
    int32_t x, y, z;
    double dx, dy, dz;
    while (x!=666){
        scanf("%d %d %d", &x, &y, &z);
        dx = (double)x;
        dy = (double)y;
        dz = (double)z;
        printf("%d <- (float)x == (float)dx\n", (float)x == (float)dx);
        printf("%d %lf %lf <- dx - dy == (double)(x - y)\n", dx - dy == (double)(x - y), dx - dy, (double)(x - y));
        printf("%d %lf %lf <- (dx + dy) + dz == dx + (dy + dz)\n", (dx + dy) + dz == dx + (dy + dz), (dx + dy) + dz, dx + (dy + dz) );
        printf("%d %lf %lf <- (dx * dy) * dz == dx * (dy * dz)\n", (dx * dy) * dz == dx * (dy * dz), (dx * dy) * dz, dx * (dy * dz));
        printf("%d %lf %lf <- dx / dx == dz / dz\n", dx / dx == dz / dz, dx / dx, dz / dz);
    }
    //looptest();

    return 0;
}

//2 - intmax