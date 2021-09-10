#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int score = atoi(argv[1]);

    if (score >= 70){
        printf("Pass\n");
    }
    else{
        printf("No pass\n");
    }
    
    return 0;
}