#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>


using namespace std;

#pragma pack(push, 1)
struct Bit
{
  uint8_t _bit0:2;
  uint8_t _bit1:2;
  uint8_t _bit2:2;
  uint8_t _bit3:2;
};
#pragma pack(pop, 1)

typedef Bit bit;

struct B
{
  bit bits[4];
};

int main()
{
  int n = 10000000, i = 0;
  // struct B b = {{1, 2, 3, 3}};
  // for (int i = 0; i < 4; ++i)
  //   cout << (int)b.bits[i]._bit0 <<endl;
  bit bitss[n];
  for(i = 0; i < n; i++){
    bitss[i]._bit0 = 3;
  }
  int sum = 0;
  for(i = 0; i < n; i++){
    sum += bitss[i]._bit0;
  }
  cout << sum << endl;
  // bitss[0]._bit0 = 2;
  // cout<< sizeof(x) << endl;
  cout<< sizeof(B) << endl;

  pause();
  return 0;
}
