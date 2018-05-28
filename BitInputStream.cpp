#include "BitInputStream.h"
#define MAX_BITS 8

/** 
 * Fill the buffer from the input
 */
void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
}

/** Read the next bit from the bit buffer.
 *  Fill the buffer from the input stream first if needed.
 *
 *  Return value:
 *   - 1 if the bit read is 1
 *   - 0 if the bit read is 0
 */
int BitInputStream::readBit() {
  unsigned char bit;

  if( this->nbits == MAX_BITS ) {
    fill();
  }
  
  bit = bitVal( this->buf, this->nbits ); 

  this->nbits++;

  return (int)bit;
}

/**
 * Return the value of the nth bit from the right of a byte argument
 */
unsigned char BitInputStream::bitVal( unsigned char b, int n ) {
  return (b >> n) & 1;
}

bool BitInputStream::isEOF() {
  if( in.eof() ) return true;
  return false;
}
