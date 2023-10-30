//
// Created by anasn on 2023-10-29.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef MATRIX_MUL_MULTIPLICATION_H
#define MATRIX_MUL_MULTIPLICATION_H

void print_matrix(int x, int y, int [x][y]);
void* unoptimized(int x_row, int x_col, int y_row, int y_col, int** , int** , int**);
void* Iterative_cache_optimized(int x_row, int x_col, int y_row, int y_col, int** , int** , int**);

#endif //MATRIX_MUL_MULTIPLICATION_H
