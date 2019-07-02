#include<stdio.h>

int power2(int x)
{
    return (x & (x - 1)) == 0;
}


int period(int m){
    int a = 0;
    int b = 1;
    int c;
    int iter = 0;
    if (power2(m)){
        return 3 * (m >> 1);
    }
    while(iter<m*m){
        c = (a + b) % m;
        a = b;
        b = c;
        iter++;
        if (a == 0 && b == 1){break;}
    }
    return iter;
}


int main(){
    int n;
    scanf("%d", &n);
    int n_tab[n];
    int m_tab[n];
    for (int i=0; i<n; i++){
        scanf("%d %d", &n_tab[i], &m_tab[i]);
    }

    for (int j=0; j<n; j++){
        int r = n_tab[j] % period(m_tab[j]);
        int x0 = 0;
        int x1 = 1;
        int temp;
        for (int k=0; k<r-1; k++){
            temp = (x0 + x1) % m_tab[j];
            x0 = x1;
            x1 = temp;
        }
        printf("%d\n", x1);
    }


    return 0;
}