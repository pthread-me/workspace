#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "../lib/Matrix.h"

#define num_input 2
#define num_layer1_nodes 2
#define num_outputs 1
#define num_layer1_biases 2
#define num_output_bias 1
#define LR 0.01
#define epochs 10

double get_weight(){
    return ((double )random() / RAND_MAX);
}

double sigmoid(double x){
    return 1.0/1+ exp(-1*x);
}

double derivative_sigmoid(double x){
    return sigmoid(x) * (1- sigmoid(x));
}

void shuffle(int* array, size_t array_size){
    if(array_size>1){
        for(size_t i =0; i<array_size-1; i++){
            size_t j = i+ random()/(RAND_MAX/ (array_size -i-1));
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}
int main() {
    double layer_1[num_layer1_nodes];
    double output[num_outputs];
    double layer1_biases[num_layer1_biases];
    double output_biases[num_output_bias];
    double layer1_weights[num_layer1_nodes][num_input];
    double output_weights[num_outputs][num_layer1_nodes];

    double training_set[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
    double training_label[4] = {0,1,1,0};

    //filling the weight matrices
    for(int i=0; i<num_input; i++){
        for(int j=0; j<num_layer1_nodes; j++){
            layer1_weights[j][i] = get_weight();
        }
    }
    for(int i=0; i<num_layer1_nodes; i++){
        for(int j=0; j<num_outputs; j++){
            output_weights[j][i] = get_weight();
        }
    }




    for(int epoch=0; epoch<epochs; epoch++){
        int training_order[4] = {0,1,2,3};
        shuffle(training_order, 4);

        for(int order=0; order<4; order++){
            int set=training_order[order];

            //layer1 propagation
            for(int layer_1_node=0; layer_1_node<num_layer1_nodes; layer_1_node++){
                double activation = layer1_biases[layer_1_node];

                for(int curr_input=0; curr_input<num_input; curr_input++){
                    activation += training_set[set][curr_input] * layer1_weights[layer_1_node][curr_input];
                }
                layer_1[layer_1_node] = sigmoid(activation);
            }

            //output layer propagation
            for(int output_layer_node=0; output_layer_node<num_outputs; output_layer_node++){
                double activation = output_biases[output_layer_node];

                for(int curr_input=0; curr_input<num_layer1_nodes; curr_input++){
                    activation+= layer_1[curr_input] * output_weights[output_layer_node][curr_input];
                }

                output[output_layer_node] = sigmoid(activation);
            }


            //print summary of the pass
            printf("input: %g %g\toutput: %g\texpected: %g\n", training_set[set][0], training_set[set][1],
                   output[0], training_label[set]);


        }
    }

}
