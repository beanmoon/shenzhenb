/**
   本程序采用了bit field技术，本来想突破对字符串用malloc函数进行内存分配时的限制
   后来发现对bit field构成的结构体进行分配内存是，仍然需要动态分配内存，
   即只要牵涉到动态分配内存的问题，都要进行alignment。
   解决办法是key的内存保持不变，把value的长度从alignmeng时的16byte转成int的4byte
   详情见codev2/mainv6.cpp
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sparsehash/sparse_hash_map>
#include <iostream>
#include <math.h>


using google::sparse_hash_map;      // namespace where class lives by default
using namespace std;

const int LARGELEN = 102;
const int LEN = 100;
const int K = 50;

#define SIZE (int)ceil(K / 4.0)

#pragma pack(push, 1)
typedef struct Bit
{
  uint8_t _bit0:2;
  uint8_t _bit1:2;
  uint8_t _bit2:2;
  uint8_t _bit3:2;
} bit;
#pragma pack(pop, 1)

uint64_t MyHashFunction(const void * key);
bit *create_bitarray(const char *key, int K);
bit *valueStored(int lnum, char start);
void explainResult(char *rst);
// void explainResult(bit *rst);


int bit2int(bit b){
  return (b._bit3 << 6) + (b._bit2 << 4) + (b._bit1 << 2) + b._bit0;
}

void int2bit(bit *b, int i){
  b->_bit3 = (i & 0xc0) >> 6;
  b->_bit2 = (i & 0x30) >> 4;
  b->_bit1 = (i & 0x0c) >> 2;
  b->_bit0 = (i & 0x03);
}


template<typename T> 
struct MyHash {
    size_t operator()(const T t) const {
      return MyHashFunction(t);
    }    
};

// struct eqstr
// {
//   bool operator()(const char* s1, const char* s2) const
//   {
//     return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
//   }
// };
struct eqstr
{
  bool operator()(const bit* b1, const bit* b2) const
  {
    int i = 0;
    bool eq = true;
    while(i < SIZE){
      if(bit2int(b1[i]) != bit2int(b2[i]))
	eq = false;
      break;
    }

    return eq;
  }
};


int main() {
  FILE *pfile = NULL;
  // const char *file = "../data";
  const char *file = "../yaa"; // small amount of test data

  sparse_hash_map<const bit*, bit *, MyHash<const bit*>, eqstr> genes;
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

    while(key[start+K-1] != '\0'){
      bit *bits = create_bitarray(key+start, K);
      genes[bits] = valueStored(lnum, start);
      // genes[bits] = NULL;

      count++;
      start++;
    }

    lnum++;
  }
  fclose(pfile);

  cout << count << endl;
  // 0-0
  char *subgene1 = "TTTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATG";
  // 0-1
  char *subgene2 = "TTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATGT";
  // 49995-0
  char *subgene3 = "ATTAGAGCGGCAAGGTGCCTGTACTTTCCGAGCAAGCACTGCGGAAATCG";
  // 49995-50
  char *subgene4 = "CCTATATTGAAACCTACCGGAGAGCAAGGGCCGCCGCCCAGAATACCTAC";
  // count << myHash(subgene1) << endl;
  // count << myHash(subgene2) << endl;
  // count << myHash(subgene3) << endl;
  // count << myHash(subgene4) << endl;

  // bit_array_print(create_bitarray(subgene1,K));

  // explainResult(genes[(create_bitarray(subgene1,K))]);
  explainResult(genes[(create_bitarray(subgene2,K))]);

  // explainResult(genes[(create_bitarray(subgene3,K))->words]);
  // explainResult(genes[(create_bitarray(subgene4,K))->words]);

  // FILE* fp = fopen("hashtable.data", "w");
  // genes.serialize(StringToIntSerializer(), fp);
  // fclose(fp);
  pause();
}

// hash function
uint64_t MyHashFunction(const void * key)
{
  const uint64_t m = 0xc6a4a7935bd1e995;
  const int r = 47;
  bit *bits = (bit *)key;
  uint64_t seed = 0; 
  int pos = 0;

  while(pos < SIZE){
    seed *= bit2int(bits[pos]);
    pos++;
  }

  uint64_t h = seed ^ m;

  pos = 0;
  while(pos < SIZE)  {
    char k = bit2int(bits[pos]);
    k *= m; 
    k ^= k >> r; 
    k *= m; 

    h ^= k;
    h *= m; 
    pos++;
  }
  return h;
}  


// create bit array based on primary key
bit* create_bitarray(const char *key, int K){
  bit *bits = new bit[SIZE];
  int i = 0, pos = 0, value = 0;

  while(i < K){
    value = 0;
    pos = i / 4;

    switch(key[i]){
    case 'A':
      value = 0;      break;
    case 'C':
      value = 1;      break;
    case 'G':
      value = 2;      break;
    case 'T':
      value = 3;      break;
    default:
      cout << "gene charactor error!" << endl;
      exit(1);
    }

    switch(i % 4){
    case 0:
      bits[pos]._bit0 = value; break;
    case 1:
      bits[pos]._bit1 = value; break;
    case 2:
      bits[pos]._bit2 = value; break;
    case 3:
      bits[pos]._bit3 = value; break;
    }

    i++;
  }
  return bits;
}


// create bit array for value stored
bit *valueStored(int lnum, char start){
  bit *bits = new bit[4];

  int2bit(&bits[0], start);
  int2bit(&bits[1], lnum %  (1 << 8));
  int2bit(&bits[2], lnum % (1 << 16) / (1 << 8));
  int2bit(&bits[3], lnum / (1 << 16));
  return bits;  
}


// reverse to valueStored
void explainResult(char *rst){
  int start = rst[0];
  int lnum = (unsigned char)rst[1] 
    + (unsigned char)(rst[2])*256 + (unsigned char)(rst[3])*65536;
  printf("This sequence is from gene %d starting from position %d.\n", lnum, start);
}

