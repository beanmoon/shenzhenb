#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <sparsehash/sparse_hash_map>

using google::sparse_hash_map;      // namespace where class lives by default

int main(){


// sparse_hash_map<int, int> * mp = new std::map<int, int>;
// std::map<int, int> mp;
sparse_hash_map<int, int>  *mp = new sparse_hash_map<int,int>;
// sparse_hash_map<int, int>  mp;
for(int i = 0; i < 999999; i++){
mp->insert(std::pair<int, int>(i, 999999-i )); 
// mp[i] = 999999-i;
}

//mp->clear();     -     doesn't help either
// std::map<int, int> *map  = &mp;
// free(mp);
delete mp;
 pause();

}
