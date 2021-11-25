/* ID: 2018116323
* NAME: DaeHeon Yoon
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    FILE *fp;

    int tmp1, tmp2;

    int* items_weight, *items_benefit;
    int** knapsack_matrix;
    int*** knapsack_matrix_elements;
    int items_count = 0;
    int max_weight;

    int* result;
    int** result_elements;

    // find N ---------------------------------------------

    fp = fopen(argv[1], "r");
    while (1){
        fscanf(fp, "%d %d", &tmp1, &tmp2);
        if (tmp2 == -1){
            break;
        }
        items_count++;
    }
    fclose(fp);

    // read weight and benefit ----------------------------

    fp = fopen(argv[1], "r");

    items_weight = (int*)malloc(sizeof(int)*items_count);
    items_benefit = (int*)malloc(sizeof(int)*items_count);

    for (int i = 0; i < items_count; i++){
        fscanf(fp, "%d %d", items_weight+i, items_benefit+i);
    }

    fscanf(fp, "%d", &max_weight);
    fclose(fp);


    // knapsack matrix -------------------------------------
    knapsack_matrix = (int**)malloc(sizeof(int*)*(items_count+1));
    for (int i = 0; i < items_count+1; i++){
        knapsack_matrix[i] = (int*)malloc(sizeof(int)*(max_weight+1));
    }

    // knapsack matrix elements -----------------------------
    knapsack_matrix_elements = (int***)malloc(sizeof(int**)*(items_count+1));
    for (int i = 0; i < items_count+1; i++){
        knapsack_matrix_elements[i] = (int**)malloc(sizeof(int*)*(max_weight+1));
        for (int j = 0; j < max_weight+1; j++){
            knapsack_matrix_elements[i][j] = (int*)malloc(sizeof(int)*items_count);
        }
    }

    // result -----------------------------------------------
    result = (int*)malloc(sizeof(int)*(items_count+1));
    
    // result elements --------------------------------------
    result_elements = (int**)malloc(sizeof(int*)*(items_count+1));
    for (int i = 0; i < items_count+1; i++){
        result_elements[i] = (int*)malloc(sizeof(int)*items_count);
    }


    for (int n = 0; n < items_count+1; n++){
        // knapsack matrix elements init -----------------------------
        for (int i = 0; i < items_count+1; i++){
            for (int j = 0; j < max_weight+1; j++){
                memset(knapsack_matrix_elements[i][j], -1, sizeof(int)*items_count);
            }
        }
        
        for (int i = 0; i < items_count; i++){
            if (i == n){
                items_benefit[i] *= 2;
                items_weight[i] *= 2;
            }
        }

        for (int current_items_count = 0; current_items_count < items_count+1; current_items_count++){
            for (int current_max_weight = 0; current_max_weight < max_weight+1; current_max_weight++){
                if (current_items_count == 0 || current_max_weight == 0){
                    knapsack_matrix[current_items_count][current_max_weight] = 0;
                    continue;
                }
                
                if (items_weight[current_items_count-1] <= current_max_weight
                    && items_benefit[current_items_count-1]
                    + knapsack_matrix[current_items_count-1][current_max_weight-items_weight[current_items_count-1]]
                    > knapsack_matrix[current_items_count-1][current_max_weight]){
                        knapsack_matrix[current_items_count][current_max_weight]
                        = items_benefit[current_items_count-1]
                        + knapsack_matrix[current_items_count-1][current_max_weight-items_weight[current_items_count-1]];
                    
                    for (int k = 0; k < items_count; k++){
                        if (knapsack_matrix_elements[current_items_count-1][current_max_weight-items_weight[current_items_count-1]][k] == -1){
                            knapsack_matrix_elements[current_items_count][current_max_weight][k] = current_items_count-1;
                            break;
                        }
                        knapsack_matrix_elements[current_items_count][current_max_weight][k] = knapsack_matrix_elements[current_items_count-1][current_max_weight-items_weight[current_items_count-1]][k];
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

        for (int i = 0; i < items_count; i++){
            if (i == n){
                items_benefit[i] /= 2;
                items_weight[i] /= 2;
            }
        }

        result[n] = knapsack_matrix[items_count][max_weight];
        for (int k = 0; k < items_count; k++){
            result_elements[n][k] = knapsack_matrix_elements[items_count][max_weight][k];
        }
    }
    

    int max_index = -1;
    int max_value = -1;

    for (int i = 0; i < items_count+1; i++){
        if (max_value < result[i]){
            max_index = i;
            max_value = result[i];
        }
    }

    for (int i = 0; i < items_count; i++){
        if (result_elements[max_index][i] == -1){
            break;
        }
        if (result_elements[max_index][i] == max_index){
            printf("%dx2 ", result_elements[max_index][i]+1);
        }
        else{
            printf("%d ", result_elements[max_index][i]+1);
        }
    }
    printf("%d\n", max_value);


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

    free(result);
    for (int i = 0; i < items_count+1; i++)
    {
        free(result_elements[i]);
    }
    free(result_elements);
    
    return 0;
}