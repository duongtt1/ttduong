#include <stdio.h>
#include "sortint.h"

#define N_ARRAY 5

int main(){
    int *arr = (int *)malloc( N_ARRAY * sizeof(int));
    arr[0]=12;
    arr[1]=5;
    arr[2]=20;
    arr[3]=16;
    arr[4]=30;

    sortInt(arr,N_ARRAY, DECREASE);

    for (int i = 0; i < N_ARRAY; i++)
    {
        printf("%d", arr[i]);
    }

    free(arr);

    return 0;
}
