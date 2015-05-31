#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sparsehash/sparse_hash_map>
#include "bit_array.h"

using google::sparse_hash_map;      // namespace where class lives by default
using std::hash; 
using namespace std;

const int LARGELEN = 102;
const int LEN = 100;
const int K = 50;



uint64_t MyHashFunction(const void * key);
BIT_ARRAY* create_bitarray(const char *key, int K);


template<typename T> 
struct MyHash {
    size_t operator()(const T t) const {
      return bit_array_hash(t,0);
    }    
};


struct eqstr
{
  bool operator()(const BIT_ARRAY* s1, const BIT_ARRAY* s2) const
  {
    // return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
    return (s1 == s2);
  }
};


int main() {
  char *data = (char *)malloc(LARGELEN);

  FILE *pfile = NULL;
  const char *file = "../data";

  sparse_hash_map<const BIT_ARRAY*, char *, MyHash<const BIT_ARRAY*>, eqstr> genes;
  // MyHash<const char *> myHash;
  
  if(!(pfile = fopen(file, "r"))){
    printf("open file failed\n");
    exit(1);
  }

  int count = 0;
  int start;
  char *key = (char *) malloc(LARGELEN);
  while(fgets(data, LARGELEN, pfile)){
    // char *key = (char *) malloc(LEN + 1);
    fgets(key, LARGELEN, pfile);
    key[LEN] = '\0';
    start = 0;

    while(key[start+K-1] != '\0'){
      BIT_ARRAY *bitarr = create_bitarray(key+start, K);

      // genes[bitarr] = data;
      count++;
      start++;
    }

    // cout << "count = " << count << endl;
    // data = (char *)malloc(LARGELEN);
  }
  fclose(pfile);

  // cout << myHash("GTATATTCTCGGTATAACGCAACAGCGACCATTCTATTTGGTAGGTTAGTCGCGGCTGGTATCTGTAGTGGCGAAAATTTCAAAGTGTTCAAGGGTGAGA") << endl;
  // cout << myHash("TTTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATGTGTTGAATCTCCAACCCTCGGAACATAGTCGTTGCTCTTGCGGACTGAGA") << endl;


  // printf("%s\n", genes["GTATATTCTCGGTATAACGCAACAGCGACCATTCTATTTGGTAGGTTAGTCGCGGCTGGTATCTGTAGTGGCGAAAATTTCAAAGTGTTCAAGGGTGAGA"]);
  // printf("%s\n", genes["TTTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATGTGTTGAATCTCCAACCCTCGGAACATAGTCGTTGCTCTTGCGGACTGAGA"]);


  pause();
}


uint64_t MyHashFunction(const void * key)
{
  const uint64_t m = 0xc6a4a7935bd1e995;
  const int r = 47;
  const char * data = (const char *)key;
  char c;
  uint64_t seed = 0; 

  while((c = *data++) != '\0')
    seed *= c;
  uint64_t h = seed ^ m;

  data = (const char *)key;
 
  while(*data != '\0')
  {
    char k = *data;
    //    printf("c = %c, ", k);
    k *= m; 
    k ^= k >> r; 
    k *= m; 

    h ^= k;
    h *= m; 
    data++;
  }
  return h;
}  


BIT_ARRAY* create_bitarray(const char *key, int K){
  BIT_ARRAY *bitarr = bit_array_create(K*2);
  int i = 0;  //bit数组中的索引值

  while(i < K * 2){
    char chr = key[i / 2];
    switch(chr){
    case 'A':
      bit_array_clear_bit(bitarr, i); 
      bit_array_clear_bit(bitarr, i+1); 
      break;
    case 'C':
      bit_array_clear_bit(bitarr, i); 
      bit_array_set_bit(bitarr,i+1);
      break;
    case 'G':
      bit_array_set_bit(bitarr,i);
      bit_array_clear_bit(bitarr, i+1); 
      break;
    case 'T':
      bit_array_set_bit(bitarr,i);	  
      bit_array_set_bit(bitarr,i+1);
      break;
    default:
      cout << "gene charactor error!" << endl;
      exit(1);
    }
    i += 2;
  }
  return bitarr;
}
