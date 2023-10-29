//
// Created by anasn on 2023-10-29.
//

#include "multiplication.h"

void print_matrix(int rows, int columns, int x[rows][columns] ){
    if(x==NULL){
        printf("matrix is not initialized", stderr);
        return;
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            printf("%d\t", x[i][j]);
        }
        printf("\n");
    }
}



void* unoptimized(int x_row, int x_col, int y_row, int y_col, int** x, int** y, int** result){
    if(x==NULL || y==NULL){
        printf("matrices cant be null\n", stderr);
        exit(-1);
    }

    if(x_col != y_row){
        printf("incompatible matrices\n", stderr);
        exit(-1);
    }

    time_t start, end;
    time(&start);

    for(int i=0; i<x_row; i++){
        for (int j=0; j<y_col; j++){
            for(int k=0; k<x_col; k++){
               result[i][j] = (x[i][k] * y[k][j]);
            }
        }
    }

    time(&end);

    printf("%f", difftime(end, start));
    return NULL;
}
