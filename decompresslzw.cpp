#include <bits/stdc++.h>
using namespace std;
void decompress(fstream& readfile) {
  // Build the dictionary.
  fstream writefile;
  writefile.open("decompress.txt",ios::out);		
  int t;	
  int dictSize = 256;
  std::map<int,std::string> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[i] = std::string(1, i);
  readfile >> t;
  string w(1,t);
  writefile << w;
  string entry;
  for (int n ; readfile >> n; ) {
    if (dictionary.count(n))
      entry = dictionary[n];
    else if (n == dictSize)
      entry = w + w[0];
    else
      throw "Bad compressed n";
 
    writefile << entry;
 
    // Add w+entry[0] to the dictionary.
    dictionary[dictSize++] = w + entry[0];
 
    w = entry;
  }
 
}
int main()
{
	fstream read;
	read.open("compressed.bin",ios::in| ios::binary);
	decompress(read);
}