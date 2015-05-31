#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  int a;
  int b;
  int c;
} tmp;

int main() {
  tmp h[20];
  printf("%d\n", sizeof(h));
}
