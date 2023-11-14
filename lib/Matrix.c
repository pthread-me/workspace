//
// Created by anasn on 2023-10-29.
//

/**
 * to perform multithreading i must firt change the functions to take a void pointer, problem for future anas
 */

#include "Matrix.h"

#define checks 100

/**
 *  creates a nxm matrix filled with 0
 * @param rows number of rows
 * @param columns number of columns
 * @param array
 * @return
 */
Matrix* create_matrix(int rows, int columns){
    if(rows<1 || columns <1){
        printf("cant create matrices with non-positive dimensions", stderr);
    }

    Matrix* matrix = calloc(1, sizeof (Matrix));
    matrix->rows = rows;
    matrix->columns = columns;


    double** m = calloc(matrix->rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
        m[i] = calloc(columns, sizeof(double ));
    }
    matrix->array = m;

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
            printf("%f\t", matrix->array[i][j]);
        }
        printf("\n");
    }
}

bool free_matrix(Matrix* matrix){
    if(matrix==NULL || matrix->array == NULL){
        printf("matrix is already empty");
        return true;
    }

    if(matrix->rows<1 || matrix->columns<1){
        printf("cant free an empty matrix", stderr);
        exit(-1);
    }

    for(int i=0; i<matrix->rows; i++){
        free(matrix->array[i]);
    }

    free(matrix->array);
    free(matrix);

    return true;
}


Matrix* transpose_matrix(Matrix* matrix){
    if(matrix==NULL || matrix->array==NULL){
        printf("cant transpose a null matrix", stderr);
        exit(-1);
    }

    if(matrix->rows<1 || matrix->columns<1){
        printf("cant transpose an empty matrix");
        exit(-1);
    }

    Matrix* t_matrix = create_matrix(matrix->columns, matrix->rows);

    for(int i=0; i<matrix->rows; i++){
        for(int j=0; j<matrix->columns; j++){
            matrix->array[i][j] = t_matrix->array[j][i];
        }
    }

    return t_matrix;
}
/**
 * unoptimized iterative multiplication on a nxm by a mxp matrix
 * @param A the nxm matrix
 * @param B the mxp matrix
 * @param C the resultant nxp matrix to save the values in
 * @return a void pointer for further multithreading
 */
Matrix* unoptimized(Matrix* A, Matrix* B){

    Matrix* C = create_matrix( A->rows,  B->columns);
    if(A==NULL || B==NULL || A->array==NULL || B->array==NULL){
        printf( "matrices cant be null\n", stderr);
        exit(-1);
    }

    int n = A->rows;
    int p = B->columns;
    int m = A->columns;

    time_t start, end;
    time(&start);

    for(int i=0; i < n; i++){
        for (int j=0; j < p; j++){
            double sum =0;
            for(int k=0; k < m; k++){
               sum += (A->array[i][k] * B->array[k][j]);
            }
            C->array[i][j] = sum;
        }
    }
    time(&end);

    //printf("%f\n", difftime(end, start));
    return C;
}

/**
 * optimal matrix step multiplication that takes into account my laptops hardware
 * @param A The matrix on the right
 * @param B the matrix on the left
 * @return a matrix with the resultant multiplication, nxp
 */
Matrix* Iterative_cache_optimized( Matrix* A, Matrix* B){

    Matrix* C = create_matrix(A->rows, B->columns);
    double** C_array = C->array;
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
                        double sum =0;
                        for(int k=K; k<min_K; k++){
                            sum += A->array[i][k] * B->array[k][j];
                        }
                        C_array[i][j] += sum;
                    }
                }
            }
        }
    }
    time(&end);
    //printf("%f\n", difftime(end, start));
    return C;
}

/**
 * performs Freivalds algorithm to the check the multiplication given 3 nxn matrices
 * @param A left matrix
 * @param B right matrix
 * @param C result matrix
 * @return true if A x B = C
 */
bool freivalds_check(Matrix* A, Matrix* B, Matrix* C){

    if(!A || !B || !C || !A->array || !B->array || !C->array){
        printf("matrices must not be null", stderr);
        exit(-1);
    }

    if(A->rows != B->rows || A->rows!=B->columns || A->rows!=C->rows || A->columns!=C->columns){
        printf("algorithm only works when matrices all have the same dimensions", stderr);
        exit(-1);
    }


    Matrix* r = create_matrix(A->rows, 1);

    FILE* file = fopen("/dev/random", "r");
    int input=0;

    for(int runs=0; runs<checks; runs++) {
        for (int i = 0; i < A->rows; i++) {
            (int) fread(&input, sizeof(int), 1, file);
            r->array[i][0] = abs(input % 2);
        }

        Matrix *ABr = unoptimized(A, unoptimized(B, r));
        Matrix *Cr = unoptimized(C, r);

        for (int i = 0; i < A->rows; i++) {
            if (ABr->array[i][0] - Cr->array[i][0] != 0) {
                fclose(file);
                return false;
            }

        }

        free_matrix(Cr);
        free_matrix(ABr);
    }
    fclose(file);
    return true;
}
