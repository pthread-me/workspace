#include <stdio.h>
#include "stdlib.h"
#include "multiplication.h"

int main() {

    int x_row = 3000;
    int x_col = 3000;
    int y_row = 3000;
    int y_col = 3000;

    int** x = calloc(x_row, sizeof (int *));
    int** y = calloc(y_row,  sizeof (int* ));
    int** result = calloc(x_row, sizeof (int *));

    for(int i=0; i<x_row; i++){
        x[i] = calloc(x_col, sizeof (int ));
        result[i] = calloc(y_col, sizeof (int ));
    }

    for(int i=0; i<y_row; i++){
        y[i] = calloc(y_col, sizeof (int ));
    }

    unoptimized(x_row,x_col, y_row,y_col, x,y, result);

}
