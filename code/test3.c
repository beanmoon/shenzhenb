#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  FILE *pfile = NULL;
  pfile = fopen("../xaa", "r");
  char *data = (char *)malloc(150);

  while(fgets(data, 150, pfile))
    {}
  pause();

}
