#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main() {
  int i = 0, n = 1000000;
  // char p[10000000][] = new char[10000000][];
  char *p[n];
  while(i < n){
    p[i] = new char[17];
    strcpy(p[i], "hello,world");
    // p[i] = "hello,world";
    i++;
  }
  // printf("%s\n", p[0]);
  pause();
}
