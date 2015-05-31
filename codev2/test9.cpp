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

#define SIZE 13

struct StringToIntSerializer {
  bool operator()(FILE* fp, std::pair<const char *, int>* value) const {
    // value->first = new char[SIZE];
    if (fread(const_cast<char *>(value->first), SIZE, 1, fp) != 1) {
    // if (fread(const_cast<char *>(value->first), SIZE, 1, fp) != 1) {
      return false;
    }
    // value->first = buf;
    // Read the key.  Note the need for const_cast to get around
    // the fact hash_map keys are always const.
    // if (fread(const_cast<int*>(&value->second), sizeof(value->second), 1, fp) != 1)
    if (fread(&(value->second), sizeof(value->second), 1, fp) != 1)
      return false;

    return true;
  }

  bool operator()(FILE* fp, const std::pair<const char *, int>& value) const {
    for(int i = 0; i < SIZE; i++){
      if (fwrite(value.first + i, 1, 1, fp) != 1)
	return false;
    }

    if (fwrite(&value.second, sizeof(value.second), 1, fp) != 1)
      return false;

    return true;
  }
};



int main(){
  // sparse_hash_map<char*, int, MyHash<const char*>, eqstr> mymap, mymap2;
  sparse_hash_map<char*, int> mymap,mymap2;
  char *p1, *p2, *p3, *p4;
  p1 = (char *) malloc(10);
  p2 = (char *) malloc(10);
  p3 = (char *) malloc(10);
  p4 = (char *) malloc(10);
  strcpy(p1, "hello");
  strcpy(p2, "world");
  strcpy(p3, "foo");
  strcpy(p4, "boo");
  mymap[p1] = 1;
  mymap[p2] = 2;
  mymap[p3] = 3;
  mymap[p4] = 4;
  FILE* fp = fopen("hashtable.dat", "w");
  mymap.serialize(StringToIntSerializer(), fp);
  cout << mymap[p1] << endl;
  fclose(fp);


  FILE* fp_in = fopen("hashtable.dat", "r");
  mymap2.unserialize(StringToIntSerializer(), fp_in);
  fclose(fp_in);
  // assert(mymap == mymap2);
  cout << mymap2[p2] << endl;
}


