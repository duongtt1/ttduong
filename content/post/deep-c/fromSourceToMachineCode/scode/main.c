#include <stdio.h>
#include "sortint.h"

int main(){
    int *arr = (int *)malloc( 5 * sizeof(int));
    arr[0]=12;
    arr[1]=5;
    arr[2]=20;
    arr[3]=16;
    arr[4]=30;

    sortInt(arr, DECREASE);

    for (int i = 0; i < 5; i++)
    {
        printf("%d", arr[i]);
    }
    
    free(arr);

    return 0;
}