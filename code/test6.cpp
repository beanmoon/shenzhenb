#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <sparsehash/sparse_hash_map>

int main()
{
std::map<std::string, int> m {{"hello",2}, {"world",1}};
   // std::map<int, int> m;
   // m[1] = 2;
   // m[2] = 1;
   std::ofstream outs("hashmap.txt");
   boost::archive::text_oarchive oarch(outs);
   oarch << m;

   outs.close();

   std::ifstream ins("hashmap.txt");
std::map<std::string, int> new_map;
   boost::archive::text_iarchive iarch(ins);
   iarch >> new_map;
   std::cout << (m == new_map) << std::endl;
}
