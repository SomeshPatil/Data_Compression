#include <bits/stdc++.h>
using namespace std;
 void compress(fstream& readfile) {
 fstream writefile;
 writefile.open("compressed.bin", ios::out | ios::binary);
  int dictSize = 256;
  map<string,int> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[string(1, i)] = i;
  readfile >> noskipws;
  char c;
  string w;
  while(readfile >> c) {

    string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else {
    	writefile<<dictionary[w]<<' ';
      // Add wc to the dictionary.
      dictionary[wc] = dictSize++;
      w = string(1, c);
    }
      }
 cerr<<dictionary.size();

  // Output the code for w.
  if (!w.empty())
    writefile << dictionary[w];
}
int main()
{
	fstream readfile;
	readfile.open("tocompress.txt", ios::in);
	readfile>>noskipws;
	compress(readfile);

}