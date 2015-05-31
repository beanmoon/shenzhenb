#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <sparsehash/sparse_hash_map>
using google::sparse_hash_map;      // namespace where class lives by default

using namespace std;
int main(){
  sparse_hash_map<char*, int> mymap;
  mymap["foo"] = 1;
  mymap["boo"] = 2;
  if(mymap["hah"])
    cout << "true" << endl;
  else
    cout << "false" << endl;
}


