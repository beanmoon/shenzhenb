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
  bool operator()(FILE* fp, const std::pair<const std::string,int>& value) const {
    // Write the key.
    assert(value.first.length() <= 255);   // we only support writing small strings
    const unsigned char size = value.first.length();
    if (fwrite(&size, 1, 1, fp) != 1)
      return false;
    if (fwrite(value.first.data(), size, 1, fp) != 1)
      return false;

    // Write the value.  We ignore endianness for this example.
    if (fwrite(&value.second, sizeof(value.second), 1, fp) != 1)
      return false;

    return true;
  }
  bool operator()(FILE* fp, std::pair<const std::string, int>* value) const {
    // Read the key.
    unsigned char size;    // all strings are <= 255 chars long
    if (fread(&size, 1, 1, fp) != 1)
      return false;
    char* buf = new char[size];
    if (fread(buf, size, 1, fp) != 1) {
      delete[] buf;
      return false;
    }
    new(const_cast<std::string*>(&value->first)) string(buf, size);
    delete[] buf;

    // Read the value.  Note the need for const_cast to get around
    // the fact hash_map keys are always const.
    if (fread(const_cast<int*>(&value->second), sizeof(value->second), 1, fp) != 1)
      return false;

    return true;
  }
};



int main(){
  sparse_hash_map<string,int> mymap, mymap2;
  mymap["foo"] = 1;
  mymap["boo"] = 5;
  FILE* fp = fopen("hashtable.data", "w");
  mymap.serialize(StringToIntSerializer(), fp);
  printf("%d\n", sizeof(mymap));
  fclose(fp);

  FILE* fp_in = fopen("hashtable.data", "r");
  mymap2.unserialize(StringToIntSerializer(), fp_in);
  fclose(fp_in);
  assert(mymap == mymap2);
  cout << mymap2["boo"] << endl;
  delete mymap2;
  printf("%d\n", sizeof(mymap2));
}


