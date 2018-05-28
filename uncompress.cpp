#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include <fstream>
#include <vector>

int main( int argc, char * argv[] ) {
  HCTree myTree;
  char c;
  int result = 0;
  vector<int> freq(256,0);

  ifstream in;
  BitInputStream bitIn(in);
  in.open(argv[1], ios::binary);

  for( int i = 0; i < freq.size(); i++ ) {
    int curr;
    in >> curr;
    freq[i] = curr;
  }

  myTree.build(freq);
  
  ofstream out;
  out.open(argv[2], ios::binary);
  
  in.get(c);
  while( 1 ){

    result = myTree.decode( bitIn );
  
    if( in.eof() || result == -1 ) {
      break;
    }

    out << (char)result;

  }

  out.close();
  in.close();
}
