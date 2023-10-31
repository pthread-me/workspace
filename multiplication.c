//
// Created by anasn on 2023-10-29.
//


/**
 * to perform multithreading i must firt change the functions to take a void pointer, problem for future anas
 */
#include "multiplication.h"



/**
 * creates a matrix from scartch or from an existing int**
 * @param i_0 staring index of the matrix's rows
 * @param i_1 ending index of the matrix's rows
 * @param j_0 starting index of the matrix's columns
 * @param j_1 ending index of the matrix's columns
 * @param pointer a pointer to an int** to set the matrix to, else NULL to create an int** with the dimensions
 *          specified above
 * @return a pointer to a Matrix object
 */
Matrix* create_matrix(int rows, int columns, int** pointer){
    Matrix* matrix = calloc(1, sizeof (Matrix));
    matrix->rows = rows;
    matrix->columns = columns;

    if(pointer == NULL) {
        int** m = calloc(matrix->rows, sizeof(int *));
        for (int i = 0; i < matrix->rows; i++) {
            m[i] = calloc(matrix->columns, sizeof(int));
        }

        matrix->pointer = m;
    } else{
        matrix->pointer = pointer;
    }

    return matrix;
}

/**
 * function prints a nxm matrix
 * @param rows number of rows
 * @param columns number of columns
 * @param x the matrix
 */
void print_matrix(Matrix* matrix){
    if(matrix==NULL){
        printf("matrix is not initialized", stderr);
        return;
    }

    for(int i=0; i<matrix->rows; i++){
        for(int j=0; j<matrix->columns; j++){
            printf("%d\t", matrix->pointer[i][j]);
        }
        printf("\n");
    }
}


/**
 * unoptimized iterative multiplication on a nxm by a mxp matrix
 * @param A the nxm matrix
 * @param B the mxp matrix
 * @param C the resultant nxp matrix to save the values in
 * @return a void pointer for further multithreading
 */
Matrix* unoptimized(Matrix* A, Matrix* B ){

    Matrix* C = create_matrix( A->rows,  B->columns, NULL);
    if(A==NULL || B==NULL || A->pointer==NULL || B->pointer==NULL){
        printf("matrices cant be null\n", stderr);
        exit(-1);
    }

    int n = A->rows;
    int p = B->columns;
    int m = A->columns;

    time_t start, end;
    time(&start);

    for(int i=0; i < n; i++){
        for (int j=0; j < p; j++){
            int sum =0;
            for(int k=0; k < m; k++){
               sum += (A->pointer[i][k] * B->pointer[k][j]);
            }
            C->pointer[i][j] = sum;
        }
    }

    time(&end);

    printf("%f\n", difftime(end, start));
    return C;
}

Matrix* Iterative_cache_optimized( Matrix* A, Matrix* B){

    Matrix* C = create_matrix(A->rows, B->columns, NULL);
    int** C_array = C->pointer;
    int T = 565;
    int n = A->rows;
    int p = B->columns;
    int m = A->columns;

    time_t start, end;
    time(&start);

    for(int I=0; I<n; I+=T){
        for(int J=0; J < p; J+=T){
            for(int K=0; K < m; K+=T){

                //now we multiply in bursts of 8. which is our T in my PC (I think)
                int min_I = I+T<n ? I+T : n;
                int min_J = J+T < p ? J + T : p;
                int min_K = K+T < m ? K + T : m;

                for(int i=I; i<min_I; i++){
                    for(int j=J; j<min_J; j++){
                        int sum =0;
                        for(int k=K; k<min_K; k++){
                            sum += A->pointer[i][k] * B->pointer[k][j];
                        }
                        C_array[i][j] += sum;
                    }
                }
            }
        }
    }


    time(&end);
    printf("%f\n", difftime(end, start));
    return C;
}


