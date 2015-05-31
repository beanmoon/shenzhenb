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


int main()
{
  sparse_hash_map<const char*, int> m;
   // std::map<int, int> m;
   // m[1] = 2;
   // m[2] = 1;
   std::ofstream outs("hashmap.txt");
   boost::archive::text_oarchive oarch(outs);
   oarch << m;

   outs.close();

   std::ifstream ins("hashmap.txt");
   sparse_hash_map<const char*, int> new_map;
   boost::archive::text_iarchive iarch(ins);
   iarch >> new_map;
   std::cout << (m == new_map) << std::endl;
}
