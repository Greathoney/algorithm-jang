#include <stdio.h>

void function(int test[2][2], int change){
    test[0][0] = change;
}

int main(void){
    int test[2][2] = {{1,2},{3,4}};
    function(test, 10);
    printf("%d", test[0][0]);

    return 0;
}