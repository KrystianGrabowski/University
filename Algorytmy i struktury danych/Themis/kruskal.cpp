#include <iostream>
#include <algorithm>

struct edge{
    int id;
    int a;
    int b;
    int c;
};

void pt(edge *edges, int size){
    for (int i=0; i<size; i++){
        printf("%d %d %d\n", edges[i].a, edges[i].b, edges[i].c);
    }
    printf("\n");
}

bool compareEdges(edge e1, edge e2){
    return e1.c < e2.c || (e1.c == e2.c && e1.id < e2.id);
}

int find_(int *parent, int x){
    int i = x;
    while(parent[i] != -1){
        i = parent[i];
    }
    return i;
}

int union_(int *parent, int a, int b){
    int aroot = find_(parent, a);
    int broot = find_(parent, b);
    if (aroot != broot){
        parent[aroot] = broot;
    }
    return 0;
}

bool disjoint(int *parent, int a, int b){
    int aroot = find_(parent, a);
    int broot = find_(parent, b);
    if (aroot != broot){
        return true;
    }
    return false;
}

int kruskal(edge *edges, int n, int m){
    int *parent;
    parent = new int[n+1];
    for (int i=0; i<n+1; i++){
        parent[i] = -1;
    }
    int edges_in_mst = 0;
    int iter = 0;
    while(edges_in_mst!=n-1){
        if (disjoint(parent, edges[iter].a, edges[iter].b)){
            union_(parent, edges[iter].a, edges[iter].b);
            printf("%d\n", edges[iter].id);
            edges_in_mst++;
        }
        iter++;
    }
    delete [] parent;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    edge *edges;
    edges = new edge[m];
    int iter = 1;
    for (int i=0; i<m; i++){
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c);
        edges[i].id = iter++;
    }
    std::sort(edges, edges+m, compareEdges);
    kruskal(edges, n, m);
    delete [] edges;
    return 0;
}