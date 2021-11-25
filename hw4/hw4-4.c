/* ID: 2018116323
* NAME: DaeHeon Yoon
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int weight, benefit;
    float efficiency;
} Items;


int main(int argc, char *argv[]){
    FILE *fp;
    int tmp;

    Items* items;
    Items tmp_items;
    int items_count = 0;
    int max_weight[2];
    int current_weight[2] = { 0, };


    // find N ---------------------------------------------

    fp = fopen(argv[1], "r");
    while (1){
        fscanf(fp, "%d", &tmp);
        if (tmp == -1){
            break;
        }
        items_count++;
    }
    items_count = items_count/2 - 1;
    fclose(fp);

    // read weight and benefit ----------------------------
    fp = fopen(argv[1], "r");

    items = (Items*)malloc(sizeof(Items)*items_count);


    for (int i = 0; i < items_count; i++){
        fscanf(fp, "%d %d", &items[i].weight, &items[i].benefit);
        items[i].efficiency = (float)items[i].benefit / items[i].weight;
    }

    fscanf(fp, "%d %d", max_weight, max_weight+1);
    fclose(fp);


    // sort by efficiency -------------------------------
    for (int i = 0; i < items_count; i++){
        for (int j = i+1; j < items_count; j++){
            if (items[i].efficiency < items[j].efficiency){
                tmp_items = items[i];
                items[i] = items[j];
                items[j] = tmp_items;
            }
        }
    }

    // sort by weight -----------------------------------------
    int before_efficiency_index = 0;
    float before_efficiency = items[0].efficiency;
    for (int n = 1; n < items_count; n++){
        if (before_efficiency != items[n].efficiency){
            // sort by weight (in same efficiency) ---------------
            for (int i = before_efficiency_index; i < n; i++){
                for (int j = i+1; j < n; j++){
                    if (items[i].weight < items[j].weight){
                        tmp_items = items[i];
                        items[i] = items[j];
                        items[j] = tmp_items;
                    }
                }
            }
            before_efficiency_index = n;
            before_efficiency = items[n].efficiency;
        }
    }
    for (int i = before_efficiency_index; i < items_count; i++){
        for (int j = i+1; j < items_count; j++){
            if (items[i].weight < items[j].weight){
                tmp_items = items[i];
                items[i] = items[j];
                items[j] = tmp_items;
            }
        }
    }

    // insert to knapsack ----------------------------------------

    int current_put;
    int left_weight;
    int total_benefit = 0;
    
    for (int i = 0; i < items_count; i++){
        if (max_weight[0] - current_weight[0] >= max_weight[1] - current_weight[1]){
            current_put = 0;
        }
        else{
            current_put = 1;
        }
        left_weight = max_weight[current_put] - current_weight[current_put];

        if (left_weight >= items[i].weight){
            current_weight[current_put] += items[i].weight;
            total_benefit += items[i].benefit;
            printf("%d %d ", items[i].weight, current_put+1);
        }
    }
    printf("%d\n", total_benefit);
    
    return 0;
}