#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sparsehash/sparse_hash_map>
#include "mybitarray.h"
#include <iostream>

using google::sparse_hash_map;      // namespace where class lives by default
using namespace std;

const int LARGELEN = 102;
const int LEN = 100;
const int K = 50;

uint64_t MyHashFunction(const void * key);
bitarray* create_bitarray(const char *key, int K);
char *valueStored(int lnum, char start);
void explainResult(char *rst);

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

// for serialization, needed to be implemented later
struct StringToIntSerializer {
  bool operator()(FILE* fp, const std::pair<const int, std::string>& value) const {
    // Write the key.  We ignore endianness for this example.
    if (fwrite(&value.first, sizeof(value.first), 1, fp) != 1)
      return false;
    // Write the value.
    assert(value.second.length() <= 255);   // we only support writing small strings
    const unsigned char size = value.second.length();
    if (fwrite(&size, 1, 1, fp) != 1)
      return false;
    if (fwrite(value.second.data(), size, 1, fp) != 1)
      return false;
    return true;
  }
  bool operator()(FILE* fp, std::pair<const int, std::string>* value) const {
    // Read the key.  Note the need for const_cast to get around
    // the fact hash_map keys are always const.
    if (fread(const_cast<int*>(&value->first), sizeof(value->first), 1, fp) != 1)
      return false;
    // Read the value.
    unsigned char size;    // all strings are <= 255 chars long
    if (fread(&size, 1, 1, fp) != 1)
      return false;
    char* buf = new char[size];
    if (fread(buf, size, 1, fp) != 1) {
      delete[] buf;
      return false;
    }
    new(&value->second) string(buf, size);
    delete[] buf;
    return true;
  }
};


int main() {
  FILE *pfile = NULL;
  const char *file = "../data";
  // const char *file = "../yaa"; // small amount of test data

  sparse_hash_map<const char*, char *, MyHash<const char*>, eqstr> genes;
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
      bitarray *bitarr = create_bitarray(key+start, K);
      // genes[bitarr->words] = valueStored(lnum, start);

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

  // explainResult(genes[(create_bitarray(subgene1,K))->words]);
  // explainResult(genes[(create_bitarray(subgene2,K))->words]);
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
  const char * data = (const char *)key;
  char c;
  uint64_t seed = 0; 

  while((c = *data++) != '\0')
    seed *= c;
  uint64_t h = seed ^ m;

  data = (const char *)key;
 
  while(*data != '\0')  {
    char k = *data;
    k *= m; 
    k ^= k >> r; 
    k *= m; 

    h ^= k;
    h *= m; 
    data++;
  }
  return h;
}  


// create bit array based on primary key
bitarray* create_bitarray(const char *key, int K){
  bitarray *bitarr = create_bit_array(K*2);
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
  return bitarr;
}


// create bit array for value stored
char *valueStored(int lnum, char start){
  char *tmp = (char *)malloc(4);

  tmp[0] |= start;
  tmp[1] |= lnum %  (1 << 8);
  tmp[2] |= lnum % (1 << 16) / (1 << 8);
  tmp[3] |= lnum / (1 << 16);
  return tmp;  
}


// reverse to valueStored
void explainResult(char *rst){
  int start = rst[0];
  int lnum = (unsigned char)rst[1] 
    + (unsigned char)(rst[2])*256 + (unsigned char)(rst[3])*65536;
  printf("This sequence is from gene %d starting from position %d.\n", lnum, start);
}

