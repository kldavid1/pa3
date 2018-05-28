#include "HCTree.h"
#include <queue>
#include <stack>
#include <vector>
#include <fstream>

HCTree::~HCTree() {
  deleteAll( this->root );
}

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int> & freqs){
  std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> forest;
  HCNode * t1;
  HCNode * t2;
  HCNode * tempRoot;

  for(int i = 0; i < freqs.size(); i++) {
    if( freqs[i] != 0 ) {
      HCNode * curr = new HCNode(freqs[i],i);
      this->leaves[i] = curr;
      forest.push(curr);
    }
  }

  while( forest.size() > 1 ){
    t1 = forest.top();
    forest.pop();
    t2 = forest.top();
    forest.pop();

    int freq = t1->count + t2->count;
    tempRoot = new HCNode(freq, 0);
    tempRoot->c1 = t1;
    tempRoot->c0 = t2;

    t1->p = tempRoot;
    t2->p = tempRoot;

    forest.push(tempRoot);
  }

  this->root = tempRoot;
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream & out) const {
  std::stack<char> code;
  HCNode * prev;

  HCNode * curr = this->leaves[(int)symbol];

  while( curr ) {
    prev = curr;
    if( !curr->p ) {
      break;
    }

    curr = curr->p;
    
    if( curr->c1 == prev ) {
      code.push('1');
    } else {
        code.push('0');
    }
  }

  while( !code.empty() ) {
    out << code.top();
    code.pop();
  }

}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode( byte symbol, BitOutputStream & out ) const {
  std::stack<int> code;
  HCNode * prev;

  HCNode * curr = this->leaves[(int)symbol];

  while( curr ) {
    prev = curr;

    if( !curr->p ) {
      break;
    }

    curr = curr->p;
    
    if( curr->c1 == prev ) {
      code.push(1);
    } else {
        code.push(0);
    }
  }

  while( !code.empty() ) {
    out.writeBit( code.top() );
    code.pop();
  }

}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream & in) const {
  HCNode * curr = this->root;
  char c;
  
  while( curr->c1 || curr->c0 ) {
    in.get(c);

    if( in.eof() ) {
      return -1;
    }

    if( c == '1' ) {
      curr = curr->c1;
    } else {
        curr = curr->c0;
    }
  }

  return (int)curr->symbol;
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode( BitInputStream& in ) const {
  HCNode * curr = this->root;
  int c;

  while( curr->c1 || curr->c0 ) {
    c = in.readBit();

    if( in.isEOF() ) {
      return -1;
    }

    if( c == 1 ) {
      curr = curr->c1;
    } else {
        curr = curr->c0;
    }
  }

  return (int)curr->symbol;

}


/**
 * Method that will recursively free all blocks of memory
 */
void HCTree::deleteAll( HCNode * n ) {
  if( !n ) {
    return;
  }

  deleteAll( n->c0 );
  deleteAll( n->c1 );
  delete n;
}
