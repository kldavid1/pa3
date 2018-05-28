#include "HCNode.h"
#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include <vector>
#include <queue>
#include <fstream>

using namespace std;
int main( int argc, char * argv[] ) {
  HCTree myTree;
  ifstream in;
  BitInputStream bitIn(in);
  vector<int> freq(256,0);
  char c = 0;
  //std::queue<HCNode*> theTree;
 
  in.open(argv[1], ios::binary);

  while( 1 ){
    in.get(c);

    if( in.eof() ) {
      break;
    }

    freq[(int)c]++;
  }

  in.close();

  myTree.build(freq);

  ofstream out;
  BitOutputStream bitOut(out);
  out.open(argv[2], ios::binary);

  for( int i = 0; i < freq.size(); i++ ) {
    out << freq[i] << endl;
  }

  in.open(argv[1]);

  while( 1 ) {
    in.get(c);

    if( in.eof() ) {
      break;
    }

    myTree.encode(c, bitOut);
  }

  in.close();
  out.close();

}
