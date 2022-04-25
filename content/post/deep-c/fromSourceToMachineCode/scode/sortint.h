#ifndef EXAMPLE_SORT
#define EXAMPLE_SORT
#include <stdlib.h>

typedef enum {
  ASCENDING,
  DECREASE
} type_compare;

// Function declaration
void swapInt(int *a, int *b);
void sortInt(int*, type_compare);

#endif