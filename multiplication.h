//
// Created by anasn on 2023-10-29.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef MATRIX_MUL_MULTIPLICATION_H
#define MATRIX_MUL_MULTIPLICATION_H

typedef struct My_Matrix{
    int** pointer;
    int rows;
    int columns;
}Matrix;

Matrix* create_matrix(int, int, int**);
void print_matrix(Matrix* matrix);
Matrix* unoptimized(Matrix* A, Matrix* B);
Matrix* Iterative_cache_optimized(Matrix* A, Matrix* B);

#endif //MATRIX_MUL_MULTIPLICATION_H
