#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <iostream>

class BitOutputStream {
  private:
    char buf;
    int nbits;
    std::ostream & out;

    /**
     * Set the value of the nth bit from the right of a byte arg
     */
    unsigned char setBit( unsigned char b, int bit, int n );


  public:
    
    /** Initialize a BitOutputStream that will use the given ostream
     * for output
     */
    BitOutputStream( std::ostream & os ) : out(os), buf(0), nbits(0){}

    /** Send the buffer to the output, and clear it
     */
    void flush();

    /** Write the least significant bit of the argument to the bit buffer,
     * and increment the bit buffer index. But flush the buffer first, if it
     * is full
     */
    void writeBit( int i );
};

#endif 
