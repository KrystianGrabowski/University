#include<iostream>
#include<stdio.h>
int row;
int column;
int** array;
int** result;
bool** changed;

int path(){
    for (int i=0; i<row; i++){
        result[i][0] = array[i][0];
    }
    for(int n=0; n<column-1; n++){
        for(int m=0; m<row; m++){
            for(int k=0; k<3; k++){
                int index = m+k-1;
                if((index >= 0) && (index < row)){                    
                    if(result[m][n] + array[index][n+1] < result[index][n+1] || !changed[index][n+1]){
                        result[index][n+1] = result[m][n] + array[index][n+1];
                        changed[index][n+1] = true;
                    }
                }
            }
        }
    }
    int min = result[0][column-1];
    for(int i=1; i<row; i++){
        min = min < result[i][column-1] ? min : result[i][column-1];
    }
    return min;
}

int main(){
    int c;
    scanf("%d", &c);
    for (int i=0; i<c; i++){
        scanf("%d %d", &row, &column);
        array = new int*[row];
        result = new int*[row];
        changed = new bool*[row];

        for(int i = 0; i < row; ++i){
            array[i] = new int[column];
            result[i] = new int[column];
            changed[i] = new bool[column];
        }
        for (int i=0; i<row; i++){
            for (int j=0; j<column; j++){
                scanf("%d", &array[i][j]);
                changed[i][j] = false;
            }
        }
        printf("%d\n", path());
        for (int i = 0; i < row; ++i){
            delete [] array[i];
            delete [] result[i];
            delete [] changed[i];
        }
        delete [] array;
        delete [] result;
        delete [] changed;
    }

    return 0;
}