/* ID: 2018116323
* NAME: DaeHeon Yoon
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int numbers[3];
    for (int i = 0; i < 3; i++){
        numbers[i] = atoi(argv[i+1]);
    }

    int tmp;
    for (int i = 0; i < 3; i++){
        for (int j = i+1; j < 3; j++){
            if (numbers[i] > numbers[j]){
                tmp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = tmp;
            }
        }
    }

    for (int i = 0; i < 3; i++){
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}