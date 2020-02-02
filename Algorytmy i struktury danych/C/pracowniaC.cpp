#include<iostream>
#include<stdio.h>
#include<vector>


struct station{
    int d;
    int c;
};


int main(){
    int n, l, b;
    if(scanf("%d %d %d", &n, &l, &b) != 3){
        printf("Error");
    }
    std::vector<station> stations(n+2);
    std::vector<long long int> costs(n+2,-1);
    costs[0] = 0;
    station s;
    station e;
    s.d = 0;
    s.c = 0;

    e.d = l;
    e.c = 0;
    stations[0] = s;
    stations[n+1] = e;

    for(int i=1; i<n+1; i++){
        if(scanf("%d %d", &stations[i].d, &stations[i].c) != 2){
            printf("Error");
        }
        if((stations[i].d - stations[i-1].d) > b){
            printf("NIE\n");
            return 0;
        }
    }

    if((l - stations[n].d) > b){
        printf("NIE\n");
        return 0;
    }
    int available_fuel = b;
    int min = 0;
    int distance = 0;
    int temp = 0;
    int current = 0;
    int iterator = 0;

    bool way = true;
    while(way){
        temp = current + 1;
        min = temp;
        way = false;
        iterator++;
        while(available_fuel >= (stations[temp].d - distance) && temp < n + 2){
            iterator++;
            way = true;
            if(costs[temp] == -1){
                costs[temp] = costs[current] + stations[temp].c;
            }
            else{
                if(costs[temp] > costs[current] + stations[temp].c){

                    costs[temp] = costs[current] + stations[temp].c;
                }
            }
            if(costs[min] >= costs[temp]){
                min = temp;
            }
            temp++;
        }
        
        current = min;
        distance = stations[current].d;
    }
    int min_cost = costs[n+1];
    if (min_cost == -1){
        printf("NIE\n");
    }
    else{
        printf("%lld\n", costs[n+1]);
    }
    


return 0;
}