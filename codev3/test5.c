#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  int i = 23, j = 54;
  int tmp = 0;
  tmp |= 23;

  tmp |= 54 << 8;
  printf("%d\n", tmp);
}
