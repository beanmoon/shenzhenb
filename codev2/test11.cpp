#include <iostream>
#include <sparsehash/sparse_hash_map>
using google::sparse_hash_map;      // namespace where class lives by default

using namespace std;

#define SIZE 13

struct CharPointerToIntSerializer {
  bool operator()(FILE* fp, std::pair<char * const, int>* value) const {
    // this can't be done, since value->first is of type 'char *const'
    // value->first = realloc(value->first, SIZE);
    if (fread(const_cast<char *>(value->first), 1, SIZE, fp) != 1) {
      return false;
    }

    if (fread(&(value->second), sizeof(value->second), 1, fp) != 1)
      return false;
    return true;
  }

  bool operator()(FILE* fp, const std::pair<char * const, int>& value) const {
    if (fwrite(value.first, 1, SIZE, fp) != 1)
      return false;

    if (fwrite(&value.second, sizeof(value.second), 1, fp) != 1)
      return false;
    return true;
  }
};

int main(){
  sparse_hash_map<char*, int> old_map,new_map;
  char *p1, *p2;
  p1 = (char *) malloc(SIZE);
  p2 = (char *) malloc(SIZE);
  strcpy(p1, "hello");
  strcpy(p2, "world");
  old_map[p1] = 1;
  old_map[p2] = 2;

  FILE* fp = fopen("hashtable.txt", "w");
  old_map.serialize(CharPointerToIntSerializer(), fp);
  // cout << old_map[p1] << endl;
  // cout << old_map[p2] << endl;
  fclose(fp);

  FILE* fp_in = fopen("hashtable.txt", "r");
  new_map.unserialize(CharPointerToIntSerializer(), fp_in);
  fclose(fp_in);
  assert(old_map == new_map);
  cout << new_map[p2] << endl;
}
