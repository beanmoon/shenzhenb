#include <stdio.h>
#include <stdlib.h>
#include "mybitarray.h"


int main() {

  for(int i = 0; i < 10000000; i++){
    char *pstr = (char *)malloc(7);
    strcpy(pstr, "hello");
    /* bitarray *arr = create_bit_array(100); */
    /* arr->nwords = 10; */
  } 

    /* pstr = (char*)malloc(10); */

  pause();
}
