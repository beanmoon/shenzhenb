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
  char nwords; 
} bitarray;

int bitindex(int b);
int bitoffset(int b);

char *create_bit_array(int len);

void clear_bit(char * arr,int b) ;

void set_bit(char * arr,int b) ;

int get_bit(char *arr, int b) ;

void clear_all(char * arr) ;

void set_all(char *arr) ;

void char_free(char *p);

void bit_array_print(char *arr);


#endif /* _MYCHAR_H */

