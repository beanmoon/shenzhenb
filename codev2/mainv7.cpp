#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sparsehash/sparse_hash_map>
#include "mybitarray.h"
#include <iostream>
#include <math.h>


using google::sparse_hash_map;      // namespace where class lives by default
using namespace std;

const int LARGELEN = 102;
const int LEN = 100;
const int K = 50;
#define SIZE (int)ceil(K / 4.0)

int dup_num = 0;

uint64_t MyHashFunction(const void * key);
char* create_bitarray(const char *key);
int valueStored(int lnum, char start);
void explainResult(int value);
void storeGene(char *key, int lnum, int start);
void retrieveGene(char *seq);

template<typename T> 
struct MyHash {
    size_t operator()(const T t) const {
      return MyHashFunction(t);
    }    
};

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
  }
};

sparse_hash_map<const char*, int, MyHash<const char*>, eqstr> genes;

int main() {
  FILE *pfile = NULL;
  const char *file = "../data";
  // const char *file = "../yaa"; // small amount of test data

  MyHash<const char *> myHash;
  
  if(!(pfile = fopen(file, "r"))){
    printf("open file failed\n");
    exit(1);
  }

  int count = 0, lnum = 0;
  char start;
  char *key = (char *)malloc(LARGELEN);
  char *data = (char *)malloc(LARGELEN);

  while(fgets(data, LARGELEN, pfile)){
    fgets(key, LARGELEN, pfile);
    key[LEN] = '\0';
    start = 0;
    lnum++;

    while(key[start+K-1] != '\0'){
      char *bitarr = create_bitarray(key+start);

      // char *str = (char *)malloc(51);
      // strncpy(str, key+start, 50);
      // storeGene(str, bitarr, lnum, start);

      storeGene(bitarr, lnum, start);
      // genes[bitarr] = valueStored(lnum, start);
      // genes[bitarr] = NULL;
      start++;
      count++;
    }
  }
  fclose(pfile);

  // return 0;
  cout << count << endl;
  cout << dup_num << endl;
  // 0-0
  char *subgene1 = "TTTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATG";
  // 0-1
  char *subgene2 = "TTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATGT";
  char *subgene2_1 = "AGATGATTTTAGTGAGCACTGCGCTAGGAGTATGTGTTGAATCTCCAACC";
  char *subgene2_2 = "CAGATGATTTTAGTGAGCACTGCGCTAGGAGTATGTGTTGAATCTCCAAC";
  // 49995-0
  char *subgene3 = "ATTAGAGCGGCAAGGTGCCTGTACTTTCCGAGCAAGCACTGCGGAAATCG";
  // 49995-50
  char *subgene4 = "CCTATATTGAAACCTACCGGAGAGCAAGGGCCGCCGCCCAGAATACCTAC";
  char *subgene5 = "ACGAAGGTTACAGGGATGGCTAAGTTTCATATGGGTAACCGGATATTGGC";

  explainResult(genes[(create_bitarray(subgene1))]);
  explainResult(genes[(create_bitarray(subgene2))]);
  explainResult(genes[(create_bitarray(subgene2_1))]);
  explainResult(genes[(create_bitarray(subgene2_2))]);
  explainResult(genes[(create_bitarray(subgene5))]);
  // cout << "-----------" << endl;
  retrieveGene(subgene1);
  retrieveGene(subgene2);
  retrieveGene(subgene2_1);
  retrieveGene(subgene2_2);
  retrieveGene(subgene5);

  // pause();
}

// hash function
uint64_t MyHashFunction(const void * key)
{
  const uint64_t m = 0xc6a4a7935bd1e995;
  const int r = 47;
  const char * data = (const char *)key;
  char c;
  uint64_t seed = 0; 

  int i = 0;
  while(i < (SIZE+1))
    seed += (*(data+i))*(++i);
  uint64_t h = seed ^ m;

  data = (char *)key;
  i = 0;
  while(i < (SIZE+1))  {
    char k = *(data+(i++));
    k *= m; 
    k ^= k >> r; 
    k *= m; 

    h ^= k;
    h *= m; 
    // data++;
  }
  return h;
}  


// create bit array based on primary key
char* create_bitarray(const char *key){
  char *bitarr = (char *)malloc(SIZE+1);
  int i = 0;  //bit数组中的索引值

  while(i < K * 2){
    char chr = key[i / 2];
    switch(chr){
    case 'A':
      clear_bit(bitarr, i); 
      clear_bit(bitarr, i+1); 
      break;
    case 'C':
      set_bit(bitarr,i);
      clear_bit(bitarr, i+1); 
      break;
    case 'G':
      clear_bit(bitarr, i); 
      set_bit(bitarr,i+1);
      break;
    case 'T':
      set_bit(bitarr,i);	  
      set_bit(bitarr,i+1);
      break;
    default:
      cout << "gene charactor error!" << endl;
      exit(1);
    }
    i += 2;
  }
  // bitarr[13] = 0;
  // bitarr[14] = 0;
  // bitarr[15] = 0;
  return bitarr;
}


void storeGene(char *key, int lnum, int start){
  unsigned int i = 0;
  // if(lnum == 1 && start == 0){
  //   for(int i = 0; i < 16; i++)
  //     cout << (int)(unsigned char)key[i] << " ";
  //   cout << endl;
  // }

  while(genes[key] && i < 256){
    // for(int i = 0; i < SIZE+1; i++)
    //   cout << (int)(unsigned char)key[i] << " ";
    // cout << endl;
    key[SIZE] = (char)++i;
    // cout << "i = " << i << endl;
    dup_num++;
  }
  if(i == 256){
    cout << "Error: too many duplicates of gene!" << endl;
    printf("This sequence is from gene %d starting from position %d.\n", lnum, start);
    exit(1);
  }
  if(valueStored(lnum, start) == 0){
    printf("Error! This sequence is from gene %d starting from position %d.\n", 
	   lnum, start);
    exit(1);
  }
  genes[key] = valueStored(lnum, start);
}

void retrieveGene(char *seq){
  char *key = create_bitarray(seq);
  // for(int i = 0; i < 16; i++)
  //   cout << (int)(unsigned char)key[i] << " ";
  // cout << endl;

  char i = 0;
  int value;
  while(value = genes[key]){
    explainResult(value);
    key[SIZE] = ++i;
  }
}
// create bit array for value stored
int valueStored(int lnum, char start){
  int tmp = 0;
  tmp |= start;
  tmp |= (lnum << 8);
  return tmp;  
}

// reverse to valueStored
void explainResult(int value){
  int start = value & 0xff;
  int lnum = (value & 0xffffff00) >> 8;
  printf("This sequence is from gene %d starting from position %d.\n", lnum, start);

}
