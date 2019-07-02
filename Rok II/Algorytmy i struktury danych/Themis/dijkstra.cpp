#include<iostream>
#include<stdio.h>
#include<vector>

struct pair{
    int neighbor;
    int cost;
};

struct vertex{
    std::vector<pair> neighbors;
    bool visited = false;
};

int main(){
    int x;
    int n, m;
    scanf("%d %d", &n, &m);
    vertex vertices[n+1];
    int a, b, c;
    std::vector<int> distance(n+1, -1);
    for ( int i=0; i<m; i++ ){
        scanf("%d %d %d",&a, &b, &c);
        pair p1, p2;
        p1.neighbor = a;
        p2.neighbor = b;
        p1.cost = c;
        p2.cost = c; 
        vertices[b].neighbors.push_back(p1);
        vertices[a].neighbors.push_back(p2);
    }
    int current = 1;
    vertex vertex1 = vertices[current];
    distance[1] = 0;
    int min;
    int mincost = -1;
    int f;

    while (true){
        for (int i=0; i<vertex1.neighbors.size(); i++){
            pair p = vertex1.neighbors[i];
            if((distance[p.neighbor] > distance[current] + p.cost) || distance[p.neighbor] == -1){
                distance[p.neighbor] = distance[current] + p.cost;
            }
            if ((mincost == -1 || mincost > distance[p.neighbor]) && !vertices[p.neighbor].visited){
                mincost =  distance[p.neighbor];
                min = p.neighbor;
            }
        }

        vertices[current].visited = true;
        current = min;
        vertex1 = vertices[current];
        if(vertices[min].visited){
            f = -1;
            for(int j=1; j<n+1; j++){
                if (!vertices[j].visited){
                    if (f == -1 && distance[j] != -1){
                        f = j;
                    }
                    else if (distance[j] != -1 && distance[f] != -1 && distance[f] > distance[j] ){
                            f = j;
                    }
                }
            }
            if (f == -1){
                break;
            }
            else{
                current = f;
                vertex1 = vertices[f];
            }
        }
               
    }

    for (int i=2; i<n+1; i++){
        printf("%d ", distance[i]);
    }
    
    return 0;
}

/*
10
17
1 2 3
1 3 4
2 4 3
2 5 4 
3 5 2
3 8 4
5 8 5
4 5 6
5 7 4
4 6 2
6 9 5
9 10 3
10 8 3
8 7 3
7 10 2
7 9 3
6 7 3
3 4 6 6 8 10 8 13 11
*/