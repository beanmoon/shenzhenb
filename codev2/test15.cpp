#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
  string word;
  // while(cin >> word)
  //   cout << word << "," << word.size() << endl;
  // while(getline(cin, word))
  //   cout << word << "," << word.size() << endl;
  vector<int> nines(10,9);
  int count;
  for(vector<int>::iterator it = nines.begin(); it != nines.end(); ++it)
    count++;
  cout << nines.size() << count << endl;
  return 0;
}


