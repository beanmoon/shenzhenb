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

struct StringToIntSerializer {
  bool operator()(FILE* fp, const std::pair<const int, std::string>& value) const {
    // Write the key.  We ignore endianness for this example.
    if (fwrite(&value.first, sizeof(value.first), 1, fp) != 1)
      return false;
    // Write the value.
    assert(value.second.length() <= 255);   // we only support writing small strings
    const unsigned char size = value.second.length();
    if (fwrite(&size, 1, 1, fp) != 1)
      return false;
    if (fwrite(value.second.data(), size, 1, fp) != 1)
      return false;
    return true;
  }
  bool operator()(FILE* fp, std::pair<const int, std::string>* value) const {
    // Read the key.  Note the need for const_cast to get around
    // the fact hash_map keys are always const.
    if (fread(const_cast<int*>(&value->first), sizeof(value->first), 1, fp) != 1)
      return false;
    // Read the value.
    unsigned char size;    // all strings are <= 255 chars long
    if (fread(&size, 1, 1, fp) != 1)
      return false;
    char* buf = new char[size];
    if (fread(buf, size, 1, fp) != 1) {
      delete[] buf;
      return false;
    }
    new(&value->second) string(buf, size);
    delete[] buf;
    return true;
  }
};


int main(){
  sparse_hash_map<int, string> mymap;
  mymap[1] = "foo";
  mymap[2] = "boo";
  FILE* fp = fopen("hashtable.data", "w");
  mymap.serialize(StringToIntSerializer(), fp);
  fclose(fp);

  sparse_hash_map<int, string> mymap2;
  FILE* fp_in = fopen("hashtable.data", "r");
  mymap2.unserialize(StringToIntSerializer(), fp_in);
  fclose(fp_in);
  assert(mymap == mymap2);
  cout << mymap2[1] << endl;
}


