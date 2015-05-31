#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <math.h>

using namespace std;
#define SIZE ceil(50 / 4.0)

#pragma pack(push, 1)
typedef struct Bit
{
  uint8_t _bit0:2;
  uint8_t _bit1:2;
  uint8_t _bit2:2;
  uint8_t _bit3:2;
} bit;
#pragma pack(pop, 1)


// int bit2int(bit *b){
//   return b->_bit3 * 64 + b->_bit2 * 16 + b->_bit1 * 4 + b->_bit0;
// }

int bit2int(bit b){
  return (b._bit3 << 6) + (b._bit2 << 4) + (b._bit1 << 2) + b._bit0;
}

void int2bit(bit *b, int i){
  b->_bit3 = (i & 0xc0) >> 6;
  cout << (int)b->_bit3 << endl;
  b->_bit2 = (i & 0x30) >> 4;
  cout << (int)b->_bit2 << endl;
  b->_bit1 = (i & 0x0c) >> 2;
  cout << (int)b->_bit1 << endl;
  b->_bit0 = (i & 0x03);
  cout << (int)b->_bit0 << endl;
}


struct B
{
  bit bits[4];
};

int main()
{
  int n = 10000000, i = 0;
  bit *b = new bit[n];
  b[0]._bit0 = 1;

  int2bit(&b[1], 23);
  cout << SIZE << endl;
  cout<< bit2int(b[1]) << endl;


  pause();
  return 0;
}
