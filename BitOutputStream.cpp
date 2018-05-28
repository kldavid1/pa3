#include "BitOutputStream.h"
#define MAX_BITS 8

/** Initialize a BitOutputStream that will use the given ostream
  * for output
  */
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = 0;
  nbits = 0;
}

/** Write the least significant bit of the argument to the bit buffer,
  * and increment the bit buffer index. But flush the buffer first, if it
  * is full
  */
void BitOutputStream::writeBit( int i ) {
  if( this->nbits == MAX_BITS ) {
    this->flush();
  }

  this->buf = setBit( this->buf, i, this->nbits );

  this->nbits++;
}

/**
 *  Set the value of the nth bit from the right of a byte arg
 */
unsigned char BitOutputStream::setBit( unsigned char b, int bit, int n ) {
  b = b & (~( 1 << n ));
  return b | ( bit << n ) ;
}
