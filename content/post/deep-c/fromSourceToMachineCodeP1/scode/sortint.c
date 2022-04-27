#include "sortint.h"

void swapInt(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortInt(int* a, int n, type_compare type){
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (type == ASCENDING ? a[i] > a[j] : a[i] < a[j])
            {
                swapInt(&a[i], &a[j]);
            }

        }
    }
}
