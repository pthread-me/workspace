#include <stdio.h>
#include "stdlib.h"
#include "multiplication.h"

int main() {


    int n = 3;
    int m = 3;
    int p = 3;



    Matrix* A = create_matrix(n, m, NULL);
    Matrix* B = create_matrix(m, p, NULL);

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            A->pointer[i][j] = 1;
            B->pointer[i][j] = 3;
        }
    }

    //Matrix* C = unoptimized(A, B);
    Matrix* C = Iterative_cache_optimized(A, B);
    print_matrix(C);
}
