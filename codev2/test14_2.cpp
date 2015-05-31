#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <sparsehash/sparse_hash_map>

using google::sparse_hash_map;      // namespace where class lives by default
// map::begin/end
#include <iostream>
#include <map>

int main ()
{
  sparse_hash_map<char *,int> mymap;
  char *p1, *p2, *p3;
  p1 = "ab"; p2 = "bc"; p3 = "cd";
  mymap["ab"] = 100;
  mymap["bc"] = 200;
  mymap["cd"] = 300;

  // show content:
  for (sparse_hash_map<char*,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}
