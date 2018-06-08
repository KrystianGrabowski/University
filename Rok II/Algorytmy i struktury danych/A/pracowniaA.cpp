#include<iostream>
#include<stdio.h>
#include<vector>
#include <algorithm>

struct dfsstruct{
    int timein;
    int timeout;
};
struct relations{
    int id;
    int parent;
};

int n = 0;
int q = 0 ;
int iotime;

std::vector<int> order;
std::vector<dfsstruct> dfs;
std::vector<int> stack;
std::vector<relations> descendants;

int iter_visit(int u){
    stack.push_back(u);
    while(!stack.empty()){

        iotime++;
        int curr = stack.back();
        if (dfs[curr].timein == -1){
            dfs[curr].timein = iotime;
        }
        bool finished = true;
        int i = order[curr];
        int bar = descendants.size(); 
        if (i != -2){
            while(descendants[i].parent == curr + 1 and i < bar){

                if (dfs[descendants[i].id - 1].timein == -1 ){
                    finished = false;
                    
                    stack.push_back(descendants[i].id - 1);
                                  
                }
                i++;
            }
        }

        if (finished and (!stack.empty())){
            curr = stack.back();
            stack.pop_back();
            if (dfs[curr].timeout == -1){
                dfs[curr].timeout = iotime;

            }

        } 
    }
    return 0;
}

bool check_path(int v, int u){
    if(dfs[u].timein >= dfs[v].timein){  
        if(dfs[u].timein <= dfs[v].timeout){
            return true;
        }
    }
    return false;

}

bool rel_compare(relations a, relations b){
    return (a.parent < b.parent);
}

int main(){
    std::ios::sync_with_stdio(false);
    if(scanf("%d %d", &n, &q) != 2){
        printf("ERROR");
    }

    for (int i=1; i<n; i++){
        relations r1;
        r1.id = i+1;
        if(scanf("%d", &r1.parent) != 1){
             printf("ERROR");
        }
        descendants.push_back(r1);
    }

    std::sort(descendants.begin(), descendants.end(), rel_compare);

    relations r0;
    r0.id = 1;
    r0.parent = 1;
    descendants.insert(descendants.begin(),r0);


    order.resize(n, -2);
    int z = 0;
    while (z<n){
        int temp = descendants[z].parent;
        order[temp-1] = z;
        z++;
        while(descendants[z].parent == temp){
            z++;
        }
    }

    
    std::vector<dfsstruct> que(q);

    for (int j=0; j<q; j++){
        if(scanf("%d %d", &que[j].timein, &que[j].timeout) != 2){
             printf("ERROR");
        }
    }

    
    iotime = -1;
    for (int j=0; j<n; j++){
        dfsstruct dfs1;
        dfs1.timein = -1;
        dfs1.timeout = -1;
        dfs.push_back(dfs1);
    }
    
    iter_visit(0);
    
    for (int i=0; i<q; i++){
        if(check_path(que[i].timein - 1, que[i].timeout - 1)){
            printf("TAK\n");
        }
        else{
            printf("NIE\n");
        }
    }
    
    
    return 0;

}