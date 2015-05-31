/* @(#)mybitarray.h
 */

#ifndef _MYBITARRAY_H
#define _MYBITARRAY_H 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char word_t;
enum { WORD_SIZE = sizeof(word_t) * 8 };

typedef struct bits { 
  word_t *words; 
  int nwords; 
} bitarray;

int bitindex(int b);
int bitoffset(int b);

bitarray *create_bit_array(int len);

void clear_bit(bitarray * arr,int b) ;

void set_bit(bitarray * arr,int b) ;

int get_bit(bitarray *arr, int b) ;

void clear_all(bitarray * arr) ;

void set_all(bitarray *arr) ;

void bitarray_free(bitarray *bitarray);

void bit_array_print(bitarray *arr);


#endif /* _MYBITARRAY_H */

