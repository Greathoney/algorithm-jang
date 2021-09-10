#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int numbers[2];
    for (int i = 0; i < 2; i++){
        numbers[i] = atoi(argv[i+1]);
    }

    float average_number = (float)(numbers[0] + numbers[1]) / 2;

    printf("average_number: %f\n", average_number);
    
    
    return 0;
}