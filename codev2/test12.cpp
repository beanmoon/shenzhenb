#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/format.hpp> 
using namespace std;
using boost::format;
#define n 100000

int main(){

  string str[n];

  for(int i = 0; i < n; i++)
    str[i] = boost::str(format("%2% %1%") % "hellooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" % i );
    // str[i] = "hello,world";
  cout << str[0] << endl;
  cout << str[99] << endl;
  cout << sizeof(str) << endl;
pause();
}
