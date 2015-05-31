#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bit_array.h"

int main() {
  BIT_ARRAY *p = bit_array_create(2000);
  printf("%d\n", (p)[1]);
}
