#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <iostream>

class BitInputStream {
  private:
    char buf;               // One byte buffer of bits
    int nbits;              // How many bits have been read from buf
    std::istream & in;      // The input stream to use
    
    /**
     * Return the value of the nth bit from the right of a byte argument
     */
    unsigned char bitVal( unsigned char b, int n );

  public:
    
    /** Initialize a BitInputStream that will use the given istream
     * for input
     */
    BitInputStream( std::istream & is ) : in(is), buf(0), nbits(8){}

    /** Fill the buffer from the input
     */
    void fill();

    /** Read the next bit from the bit buffer.
     *  Fill the buffer from the inpout stream first if needed.
     *
     *  Return value:
     *   - 1 if the bit read is 1
     *   - 0 if the bit read is 0
     */
    int readBit();

    bool isEOF();
};

#endif 
