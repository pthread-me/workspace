//
// Created by anasn on 2023-10-29.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "math.h"

#ifndef MATRIX_MUL_MULTIPLICATION_H
#define MATRIX_MUL_MULTIPLICATION_H

typedef struct My_Matrix{
    double** array;
    int rows;
    int columns;
}Matrix;

Matrix* create_matrix(int rows, int columns);
void print_matrix(Matrix* matrix);
Matrix* transpose_matrix(Matrix*);
bool free_matrix(Matrix*);
Matrix* unoptimized(Matrix* A, Matrix* B);
Matrix* Iterative_cache_optimized(Matrix* A, Matrix* B);
bool freivalds_check(Matrix* A, Matrix* B, Matrix* C);

#endif //MATRIX_MUL_MULTIPLICATION_H
