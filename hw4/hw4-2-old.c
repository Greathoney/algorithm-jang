/* ID: 2018116323
* NAME: DaeHeon Yoon
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_avail(float **knapsack_matrix, float ***knapsack_matrix_elements, int current_items_count, int items_count, int current_max_weight){
    if (current_items_count <= (items_count-1)/2)
        return 1;
    
    for (int i = 0; i < 2*items_count; i++){
        knapsack_matrix_elements[current_items_count][]
    }

    return 1;
}


int main(int argc, char *argv[]){
    FILE *fp;

    float tmp1, tmp2;

    float* items_weight, *items_benefit;
    float** knapsack_matrix;
    int*** knapsack_matrix_elements;
    int items_count = 0;
    int max_weight;

    // find N ---------------------------------------------

    fp = fopen(argv[1], "r");
    while (1){
        fscanf(fp, "%f %f", &tmp1, &tmp2);
        if (tmp2 == -1){
            break;
        }
        items_count++;
    }
    fclose(fp);

    // read weight and benefit ----------------------------

    fp = fopen(argv[1], "r");

    items_weight = (float*)malloc(sizeof(float)*items_count*2);
    items_benefit = (float*)malloc(sizeof(float)*items_count*2);

    for (int i = 0; i < items_count; i++){
        fscanf(fp, "%f %f", tmp1, tmp2);

        items_weight[i] = tmp1;
        items_benefit[i] = tmp2;
        items_weight[items_count+i] = tmp1/2;
        items_benefit[items_count+i] = tmp2/2;
    }

    fscanf(fp, "%d", &max_weight);
    fclose(fp);


    // knapsack matrix -------------------------------------
    knapsack_matrix = (float**)malloc(sizeof(float*)*(2*items_count+1));
    for (int i = 0; i < 2*items_count+1; i++){
        knapsack_matrix[i] = (float*)malloc(sizeof(float)*(max_weight+1));
    }

    // knapsack matrix elements -----------------------------
    knapsack_matrix_elements = (float***)malloc(sizeof(float**)*(2*items_count+1));
    for (int i = 0; i < 2*items_count+1; i++){
        knapsack_matrix_elements[i] = (float**)malloc(sizeof(float*)*(max_weight+1));
        for (int j = 0; j < max_weight+1; j++){
            knapsack_matrix_elements[i][j] = (float*)malloc(sizeof(float)*(2*items_count));
            memset(knapsack_matrix_elements[i][j], -1, sizeof(float)*(2*items_count));
        }
    }

    for (int current_items_count = 0; current_items_count < 2*items_count+1; current_items_count++){
        for (int current_max_weight = 0; current_max_weight < max_weight+1; current_max_weight++){
            if (current_items_count == 0 || current_max_weight == 0){
                knapsack_matrix[current_items_count][current_max_weight] = 0;
                continue;
            }

            if (is_avail(knapsack_matrix, knapsack_matrix_elements, current_items_count, items_count, current_max_weight)) { // logic
                if (items_weight[current_items_count-1] <= current_max_weight
                    && items_benefit[current_items_count-1]
                    + knapsack_matrix[current_items_count-1][current_max_weight-(int)items_weight[current_items_count-1]]
                    > knapsack_matrix[current_items_count-1][current_max_weight]){
                        knapsack_matrix[current_items_count][current_max_weight]
                        = items_benefit[current_items_count-1]
                        + knapsack_matrix[current_items_count-1][current_max_weight-(int)items_weight[current_items_count-1]];

                    for (int k = 0; k < items_count; k++){
                        if (knapsack_matrix_elements[current_items_count-1][current_max_weight-(int)items_weight[current_items_count-1]][k] == -1){
                            knapsack_matrix_elements[current_items_count][current_max_weight][k] = current_items_count-1;
                            break;
                        }
                        knapsack_matrix_elements[current_items_count][current_max_weight][k] = knapsack_matrix_elements[current_items_count-1][current_max_weight-(int)items_weight[current_items_count-1]][k];
                    }
                }
                else{
                    knapsack_matrix[current_items_count][current_max_weight]
                    = knapsack_matrix[current_items_count-1][current_max_weight];
                    for (int k = 0; k < items_count; k++){
                        if (knapsack_matrix_elements[current_items_count-1][current_max_weight][k] == -1){
                            break;
                        }
                        knapsack_matrix_elements[current_items_count][current_max_weight][k] = knapsack_matrix_elements[current_items_count-1][current_max_weight][k];
                    }                
                }
            }
        }
    }


    for (int k = 0; k < items_count; k++){
        if (knapsack_matrix_elements[items_count][max_weight][k] == -1)
            break;
        printf("%d ", knapsack_matrix_elements[items_count][max_weight][k]+1);
    }
    printf("%d\n", knapsack_matrix[items_count][max_weight]);


    

    // free memory ---------------------------------------
    free(items_weight);
    free(items_benefit);
    for (int i = 0; i < items_count; i++){
        free(knapsack_matrix[i]);
    }
    free(knapsack_matrix);

    for (int i = 0; i < items_count+1; i++){
        for (int j = 0; j < max_weight+1; j++){
            free(knapsack_matrix_elements[i][j]);
        }
        free(knapsack_matrix_elements[i]);
    }
    free(knapsack_matrix_elements);

    return 0;
}