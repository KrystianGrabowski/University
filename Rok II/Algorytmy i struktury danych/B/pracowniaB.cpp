#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<map>
#include<utility> 

struct tunnel{
    int a1;
    int b1;

    int a2;
    int b2;
};

bool cmp (tunnel x, tunnel y){
    return (x.a1 + x.b1 < y.a1 + y.b1);
}

int m, n, t;
std::vector<tunnel> tunnels;
std::map<std::pair<int,int>, int> order;
std::vector<std::pair<int,int>> queue;

int paths(){
        for(int i = 0; i< t; i++){
        order[std::make_pair(tunnels[i].a2, tunnels[i].b2)] = 
            ((order[std::make_pair(tunnels[i].a2, tunnels[i].b2)] + 
                order[std::make_pair(tunnels[i].a1, tunnels[i].b1)]) % 999979);
    }



    return order[std::make_pair(m,n)];
}



int main(){

    std::ios::sync_with_stdio(false);
    if (scanf("%d %d %d", &m, &n, &t) != 3){
        printf("Error");
    }

    for(int i=0; i<t; i++){
        tunnel temp;
        if (scanf("%d %d %d %d", &temp.a1, &temp.b1, &temp.a2, &temp.b2 ) != 4){
            printf("Error");          
        }
        order[std::make_pair(temp.a1,temp.b1)] = 0;

        tunnels.push_back(temp);
    }
    order[std::make_pair(0,0)] = 1;
    order[std::make_pair(m,n)] = 0;

    std::sort(tunnels.begin(), tunnels.end(), cmp);
    int result = paths();
    printf("%d\n", result);

    return 0;
}