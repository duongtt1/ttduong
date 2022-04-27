#include "calc.h"

void swapInt(int *a, int *b){
    int tmp = *a; 
    *a = *b; 
    *b = tmp;
}

void sortInt(int* a, type_compare type){
    for (int i = 0; i < N_ARRAY-1; i++)
    {
        for (int j = i+1; j < N_ARRAY; j++)
        {
            if (type == ASCENDING ? a[i] > a[j] : a[i] < a[j])
            {
                swapInt(&a[i], &a[j]);
            }
            
        }
    }
}