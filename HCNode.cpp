#include "HCNode.h"

bool HCNode::operator<(const HCNode& other){
  if( this->count > other.count ) {
    return true; 
  } else if ( other.count > this->count ) {
      return false;
  } else if ( this->symbol < other.symbol ) {
      return true;
  } else {
      return false;
  }
}
