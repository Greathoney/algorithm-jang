#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int numbers[5];
    for (int i = 0; i < 5; i++){
        numbers[i] = atoi(argv[i+1]);
    }

    int max_number = numbers[0];
    for (int i = 1; i < 5; i++)
    {
        if (max_number < numbers[i]){
            max_number = numbers[i];
        }
    }
    
    return 0;
}