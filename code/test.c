#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *str = "ATTAGAGCGGCAAGGTGCCTGTACTTTCCGAGCAAGCACTGCGGAAATCGCCTATATTGAAACCTACCGGAGAGCAAGGGCCGCCGCCCAGAATACCTAC";
  char *substr = malloc(51);
  strncpy(substr, str+50, 50);
  substr[50] = '\0';
  printf("%s\n", substr);
 char *subgene3 = "GTATATTCTCGGTATAACGCAACAGCGACCATTCTATTTGGTAGGTTAGT";
 int i = 0;
 char c;
 while(c = *subgene3++)
   i++;
 printf("%d\n", i);
}
