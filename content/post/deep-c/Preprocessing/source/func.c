#include <stdio.h>

#define SUM(a,b) a + b

int main(int argc, char **argv)
{
  int s = SUM(2,3);
  printf("s= %d",s); // s= 5
  return 0;
}
