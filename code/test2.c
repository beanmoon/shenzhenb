#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
char *tmp = malloc(4);
int start = 20, lnum = 998765;
tmp[0] |= start;
tmp[1] |= lnum %  (1 << 8);
tmp[2] |= lnum % (1 << 16) / (1 << 8);
tmp[3] |= lnum / (1 << 16);
for(int i = 0; i < 4; i++)
  printf("%d ",tmp[i]);
printf("\n");
}
