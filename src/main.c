#include <stdio.h>
#include "stdlib.h"
#include "Matrix.h"

int main() {


    int n = 12;
    int m = 12;
    int p = 12;



    Matrix* A = create_matrix(n, m);
    Matrix* B = create_matrix(m, p);
    Matrix* C = create_matrix(n, m);

    FILE* stream = fopen("/dev/random", "r");

    int a_val, b_val, c_val;
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){

            fread(&a_val, sizeof (int ), 1, stream);
            fread(&b_val, sizeof (int ), 1, stream);
            fread(&c_val, sizeof (int ), 1, stream);


            A->array[i][j] = abs(a_val)%2;
            B->array[i][j] = abs(b_val)%2;
            C->array[i][j] = abs(c_val)%2;
        }
    }

    bool equal = freivalds_check(A, B, C);
    if(equal != true){
        printf("incorrect\n");
    }else {
        printf("correct\n");
    }


}
