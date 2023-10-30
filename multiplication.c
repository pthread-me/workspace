//
// Created by anasn on 2023-10-29.
//

#include "multiplication.h"

void print_matrix(int rows, int columns, int x[rows][columns]){
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

void* Iterative_cache_optimized(int x_row, int x_col, int y_row, int y_col, int** A, int** B, int** C){

    time_t start, end;
    time(&start);

    for(int I=0; I<x_row; I+=8){
        for(int J=0; J<y_col; J+=8){
            for(int K=0; K<x_col; K+=8){
                //now we multiply in bursts of 8. which is our T in my PC (i think)
                int min_I = I+8<x_row ? I+8 : x_row;
                int min_J = J+8<y_col ? J+8 : y_col;
                int min_K = K+8<x_col ? K+8 : x_col;
                for(int i=I; i<min_I; i++){
                    for(int j=J; j<min_J; j++){
                        int sum =0;
                        for(int k=K; k<min_K; k++){
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }


    time(&end);

    printf("%f", difftime(end, start));
    return NULL;
}
