#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  char *p = "TTTCCTTTTTTTGAACAGATGATTTTAGTGAGCACTGCGCTAGGAGTATGTGTTGAATCTCCAACCCTCGGAACATAGTCGTTGCTCTTGCGGACTGAGA";
  char *str = (char *)malloc(51);
  strncpy(str, p+15, 50);
  printf("%s, %d\n", str, strlen(str));
}
