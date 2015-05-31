#include "mybitarray.h"

int bitindex(int b) { return b / WORD_SIZE; }
int bitoffset(int b) { return b % WORD_SIZE; }

bitarray *create_bit_array(int len){
  bitarray *arr = (bitarray *)malloc(sizeof(bitarray));
  /* char numofwords = len % 8 == 0 ? len / 8 : len / 8 + 1; */
  /* word_t *data = (word_t *)malloc(numofwords); */
  /* arr->words = data; */
  /* arr->nwords = numofwords; */
  /* printf("nwords = %d\n", arr->nwords); */
  return arr;
}



void set_bit(bitarray * arr,int b) { 
    arr->words[bitindex(b)] |= 1 << (bitoffset(b)); 
}

void clear_bit(bitarray *arr, int b) { 
    arr->words[bitindex(b)] &= ~(1 << (bitoffset(b)));
}

int get_bit(bitarray *arr, int b) { 
  return arr->words[bitindex(b)] >> bitoffset(b)  &  0x1;
}

void clear_all(bitarray * arr) { /* set all elements of data to zero */ 
  for(int i = 0; i < arr->nwords; i++)
    arr->words[i] = 0x0;
}

void set_all(bitarray *arr) { /* set all elements of data to one */ 
  for(int i = 0; i < arr->nwords; i++)
    arr->words[i] = 0xff;
}

void bitarray_free(bitarray *bitarray) {
    free(bitarray->words);
    free(bitarray);
}

void bit_array_print(bitarray *arr){
  for(int i = 0; i < arr->nwords * WORD_SIZE; i++){
    printf("%c", get_bit(arr, i) ? '1' : '0');
  }
  printf("\n");
}



/* int main() { */
  
/*   bitarray *arr = create_bit_array(20); */
/*   set_bit(arr, 15); */
/*   set_bit(arr,14); */
/*   set_bit(arr,16); */
/*   clear_bit(arr, 15); */
/*   bit_array_print(arr); */
/* } */

