#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sparsehash/sparse_hash_map>

using google::sparse_hash_map;      // namespace where class lives by default
using std::hash; 

const int LARGELEN = 110;
const int LEN = 100;

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
  }
};
g
int main() {
  char *data = (char *)malloc(LARGELEN);
  char *pre = (char *)malloc(LARGELEN);
  FILE *pfile = NULL;
  const char *file1 = "../b1";
  const char *file2 = "../b2";

  sparse_hash_map<const char*, char *, hash<const char*>, eqstr> genes;

  
  if(!(pfile = fopen(file1, "r"))){
    printf("open file b1 failed\n");
    exit(1);
  }

  while(fgets(data, LARGELEN, pfile)){
    char *key = (char *) malloc(LEN);
    strncpy(key,data,LEN);
    //    key[100] = '\0';
    if(key[0] == '>')
      strcpy(pre,key);
    else
      genes[key] = pre;
  }
  fclose(pfile);


  if(!(pfile = fopen(file2, "r"))){
    printf("open file b2 failed\n");
    exit(1);
  }

  char *tmp;
  while(fgets(data, LARGELEN, pfile)){
    char *key = (char *) malloc(LEN);
    strncpy(key,data,LEN);
    //    key[100] = '\0';
    if(key[0] == '>')
      strcpy(pre,key);
    else
      genes[key] = pre;
    tmp = key;
  }
  fclose(pfile);
  printf("%s, %d\n", data, strlen(data));
  char *key = (char*)malloc(LEN);
  strcpy(key,tmp);
  //  strcpy(key, "TTTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATGTGTTGAATCTCCAACCCTCGGAACATAGTCGTTGCTCTTGCGGACTGAGA");
  strcpy(key,"GTATATTCTCGGTATAACGCAACAGCGACCATTCTATTTGGTAGGTTAGTCGCGGCTGGTATCTGTAGTGGCGAAAATTTCAAAGTGTTCAAGGGTGAGA");
  printf("%s, %d\n", key, strlen(key));
  printf("%s, %d\n", tmp, strlen(tmp));
  printf("%s\n",genes[data]);
  printf("%s\n",genes[tmp]);
  printf("%s\n", genes[key]);
  printf("%s\n", genes["GTATATTCTCGGTATAACGCAACAGCGACCATTCTATTTGGTAGGTTAGTCGCGGCTGGTATCTGTAGTGGCGAAAATTTCAAAGTGTTCAAGGGTGAGA"]);
  printf("%d\n", sizeof genes);

}
