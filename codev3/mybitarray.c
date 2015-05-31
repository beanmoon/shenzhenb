#include "mybitarray.h"
#include <stdlib.h>


int bitindex(int b) { return b / WORD_SIZE; }
int bitoffset(int b) { return b % WORD_SIZE; }

char *create_bit_array(int len){
  char num = len % 8 == 0 ? len / 8 : len / 8 + 1;
  /* printf("%d\n", num); */
  /* char *p = (char *)aligned_alloc(1, num); */
  char *p = (char *)malloc(num);

  return p;
}


void set_bit(char * arr,int b) { 
    arr[bitindex(b)] |= 1 << (bitoffset(b)); 
}
void clear_bit(char *arr, int b) { 
    arr[bitindex(b)] &= ~(1 << (bitoffset(b)));
}

int get_bit(char *arr, int b) { 
  return arr[bitindex(b)] >> bitoffset(b)  &  0x1;
}

/* void clear_all(char * arr) { /\* set all elements of data to zero *\/  */
/*   for(int i = 0; i < arr->nwords; i++) */
/*     arr[i] = 0x0; */
/* } */

/* void set_all(char *arr) { /\* set all elements of data to one *\/  */
/*   for(int i = 0; i < arr->nwords; i++) */
/*     arr[i] = 0xff; */
/* } */

void char_free(char *p) {
    free(p);
}

/* void bit_array_print(char *arr){ */
/*   for(int i = 0; i < arr * WORD_SIZE; i++){ */
/*     printf("%c", get_bit(arr, i) ? '1' : '0'); */
/*   } */
/*   printf("\n"); */
/* } */



/* int main() { */
  
/*   char *arr = create_bit_array(20); */
/*   set_bit(arr, 15); */
/*   set_bit(arr,14); */
/*   set_bit(arr,16); */
/*   clear_bit(arr, 15); */
/*   bit_array_print(arr); */
/* } */

