/* ID: 2018116323
* NAME: DaeHeon Yoon
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/

#include <stdio.h>
#include <stdlib.h>

void update_knapsack_matrix_elements(int* p_knapsack_matrix_elements, int* p_knapsack_matrix, int value){
    
}

int main(int argc, char *argv[]){
    FILE *fp;

    int num1, num2;
    int items_weight[100], items_benefit[100];
    int items_count = 0;
    int max_weight;

    int knapsack_matrix[100][100];
    int knapsack_matrix_elements[100][100][100];

    int* p_knapsack_matrix = *knapsack_matrix;
    int* p_knapsack_matrix_elements = *knapsack_matrix_elements;


    fp = fopen(argv[1], "r");

    while (1){
        fscanf(fp, "%d %d", &num1, &num2);

        if (num2 == -1){
            max_weight = num1;
            break;
        }
        items_weight[items_count] = num1;
        items_benefit[items_count] = num2;
        items_count++;
    }

    for (int current_items_count = 0; current_items_count <= items_count; current_items_count++){
        for (int current_max_weight = 0; current_max_weight <= max_weight; current_max_weight++){
            if (current_items_count == 0 || current_max_weight == 0){
                knapsack_matrix[current_items_count][current_max_weight] = 0;
                continue;
            }
            
            if (items_weight[current_items_count] <= current_max_weight){
                if (items_benefit[current_items_count] + knapsack_matrix[current_items_count-1][current_max_weight-items_weight[current_items_count]] > knapsack_matrix[current_items_count-1][current_max_weight]){
                    knapsack_matrix[current_items_count][current_max_weight] = items_benefit[current_items_count] + knapsack_matrix[current_items_count-1][current_max_weight-items_weight[current_items_count]];
                    update_knapsack_matrix_elements(p_knapsack_matrix_elements, p_knapsack_matrix, 0);
                }
                // else{
                //     knapsack_matrix[current_items_count][current_max_weight] = knapsack_matrix[current_items_count-1][current_max_weight];
                // }
            }
            else{
                knapsack_matrix[current_items_count][current_max_weight] = knapsack_matrix[current_items_count-1][current_max_weight];
            }
        }
    }

    for (int current_max_weight = 0; current_max_weight <= max_weight; current_max_weight++){
        for (int current_items_count = 0; current_items_count <= items_count; current_items_count++){
            printf("%d ", knapsack_matrix[current_items_count][current_max_weight]);
        }
        printf("\n");
    }

    return 0;
}