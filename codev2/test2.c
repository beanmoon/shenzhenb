#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

  char * const p1 = "hello";
  /* p1 = "world"; */
  strcpy(p1, "world");
  printf("%s\n", p1);
}
