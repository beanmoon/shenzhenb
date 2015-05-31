#include <map>
#include <iostream>
#include <unistd.h>

int main(){
  // std::map<int, int> *mp = new std::map<int, int>;;
  std::map<int, int> mp;
  for(int i = 0; i < 999999; i++){
    // mp->insert(std::pair<int, int>(i, 999999-i )); 
    mp[i] = 999999-i;
  }

  delete &mp;
  // delete mp;
  pause();
}
