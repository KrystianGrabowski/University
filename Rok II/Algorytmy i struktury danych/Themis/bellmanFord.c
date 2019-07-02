#include<stdio.h>

struct edge {
    int a;
    int b;
    int c;
};

struct distance {
    int d;
    int checked;
};

static int edge_cmp(const void *s1, const void *s2)
{
  const struct edge *str1 = s1, *str2 = s2;

  return str1->a < str2->a ? -1 : str1->a > str2->a;
}

static int dist_cmp(const void *s1, const void *s2)
{
  const struct distance *str1 = s1, *str2 = s2;

  return str1->d < str2->d ? -1 : str1->d > str2->d;
}

int main(){
    int s, n, m;
    scanf("%d %d %d", &n, &m, &s);
    struct edge edges[m];
    struct distance distances[n];
    
    for ( int p=0; p<n; p++){
        distances[p].checked = 0;
    }

    for ( int i=0; i<m; i++ ){
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c );
    }
    distances[s].d = 0;
    distances[s].checked = 1;
    //qsort(edges, sizeof edges / sizeof *edges, sizeof *edges, edge_cmp);

    for ( int k=0; k<n-1; k++ ){
        for ( int j=0; j<m; j++ ){
            if ( distances[edges[j].a].checked == 1 ){
                if ( distances[edges[j].b].checked == 0 ){
                    distances[edges[j].b].d = distances[edges[j].a].d + edges[j].c;
                }
                else if (  distances[edges[j].b].d >  distances[edges[j].a].d + edges[j].c ){
                    distances[edges[j].b].d = distances[edges[j].a].d + edges[j].c;
                }
                distances[edges[j].b].checked = 1;}
        }
    }
    
    int c = 0;
    for ( int j=0; j<m; j++ ){
        if ( distances[edges[j].a].checked ){
            if ( distances[edges[j].b].d >  distances[edges[j].a].d + edges[j].c ){
                printf("NIE");
                c = 1;
                break;
            }
        }
    }

    if (!c){
        for (int h=0; h<n; h++){
            if ( h!=s && distances[h].checked ){
                printf("%d %d\n", h, distances[h].d );
            }
        }
    }

    return 0;
}