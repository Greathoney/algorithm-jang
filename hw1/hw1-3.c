/* ID: 2018116323
* NAME: DaeHeon Yoon
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    int ndata, *A;

    fp = fopen(argv[1], "r");


    fscanf(fp, "%d", &ndata);

    A = (int*)malloc(sizeof(int)*ndata);

    for (int i = 0; i < ndata; i++){
        fscanf(fp, "%d", A+i);
    }

    int min = A[0], max = A[0];
    float mean = A[0], variance = 0;

    for (int i = 1; i < ndata; i++){
        if (min > A[i]){
            min = A[i];
        }
        else if (max < A[i]){
            max = A[i];
        }
        mean += A[i];
    }
    mean /= ndata;

    for (int i = 0; i < ndata; i++){
        variance += (A[i]-mean)*(A[i]-mean);
    }
    variance /= ndata;


    printf("%-8s%-6s%-6s%-6s%-10s\n", "#data", "min", "max", "mean", "variance");
    printf("%-8d%-6d%-6d%-6.1f%-10.1f\n", ndata, min, max, mean, variance);
    return 0;
}