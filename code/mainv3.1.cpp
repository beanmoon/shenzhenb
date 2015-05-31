#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sparsehash/sparse_hash_map>

using google::sparse_hash_map;      // namespace where class lives by default
using std::hash; 
using namespace std;


const int LEN = 101;

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

int main() {
  char *data = (char *)malloc(LEN);

  FILE *pfile = NULL;
  const char *file = "../data";


  sparse_hash_map<const char*, char *, MyHash<const char*>, eqstr> genes;
  MyHash<const char *> myHash;
  
  if(!(pfile = fopen(file, "r"))){
    printf("open file failed\n");
    exit(1);
  }

  while(fgets(data, LEN, pfile)){
    char *key = (char *) malloc(LEN);
    fgets(key, LEN, pfile);
    key[LEN-1] = '\0';
    genes[key] = data;
    data = (char *)malloc(LEN);
  }
  fclose(pfile);




  cout << myHash("GTATATTCTCGGTATAACGCAACAGCGACCATTCTATTTGGTAGGTTAGTCGCGGCTGGTATCTGTAGTGGCGAAAATTTCAAAGTGTTCAAGGGTGAGA") << endl;
  cout << myHash("TTTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATGTGTTGAATCTCCAACCCTCGGAACATAGTCGTTGCTCTTGCGGACTGAGA") << endl;


  printf("%s\n", genes["GTATATTCTCGGTATAACGCAACAGCGACCATTCTATTTGGTAGGTTAGTCGCGGCTGGTATCTGTAGTGGCGAAAATTTCAAAGTGTTCAAGGGTGAGA"]);
  printf("%s\n", genes["TTTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATGTGTTGAATCTCCAACCCTCGGAACATAGTCGTTGCTCTTGCGGACTGAGA"]);


  pause();
}
