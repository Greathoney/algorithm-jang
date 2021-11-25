#include <stdio.h>
#include <math.h>

int num_cities = 100;
int cities[100][2];

double cities_weight[100][100] = {0, };
int visited_cities[100-1] = {0, };

int num_fuels = 4;
int fuels[4] = {250, 500, 950, 1350};

double fuel_left;

double distance(int x1, int y1, int x2, int y2){
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

int is_reach(int current_city, int target_city, int move, int max_move, double fuel){
    visited_cities[move] = current_city;
    int answer = 0;
    int is_skip;

    if (move == max_move){
        if (current_city == target_city){
            fuel_left = fuel;
            return 1;
        }
        else{
            return 0;
        }
    }
    if (current_city == target_city){
        return 0;
    }


    if (fuel < cities_weight[current_city][target_city]){
        return 0;
    }
    for (int next_city = 1; next_city < num_cities; next_city++){
        if (next_city == current_city){
            continue;
        }
        is_skip = 0;
        for (int i = 0; i < move; i++){
            if (next_city == visited_cities[i]){
                is_skip = 1;
            }
        }
        if (is_skip){
            continue;
        }
        if (fuel-cities_weight[current_city][next_city] >= 0){
            if (is_reach(next_city, target_city, move+1, max_move, fuel-cities_weight[current_city][next_city])){
                return 1;
            }
        }
    }
    return 0;
}



int main(int argc, char *argv[]){
    int max_move;
    double distance_tmp;

    FILE *fp;
    fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &num_cities);
    for (int i = 0; i < num_cities; i++){
        fscanf(fp, "%d %d", &cities[i][0], &cities[i][1]);
    }
    fclose(fp);


    for (int i = 0; i < num_cities; i++){
        for (int j = i+1; j < num_cities; j++){
            distance_tmp = distance(cities[i][0], cities[i][1], cities[j][0], cities[j][1]);
            cities_weight[i][j] = distance_tmp;
            cities_weight[j][i] = distance_tmp;
        }
    }


    for (int f = 0; f < num_fuels; f++){
        max_move = 1;
        while (1){
            if (is_reach(0, num_cities-1, 0, max_move, (double)fuels[f])){
                max_move++;
            }
            else{
                break;
            }
        }
        printf("%d %f", fuels[f], fuels[f]-fuel_left);
        for (int i = 0; i < max_move; i++){
            printf("%d %d ", cities[visited_cities[i]][0], cities[visited_cities[i]][1]);
        }
    }

    return 0;
}