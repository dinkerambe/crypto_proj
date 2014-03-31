#include "speck.h"

void Speck::genKey() {
	for(int i = 0; i < KEYSIZE; ++i) {
		key << 1;
		//get random bit
		//or with key	
	}
}

void Speck::keyExpansion(){
	for(int i =0; i < NUMROUNDS - 2; i++){
	}
		

}

void Speck::setKey(uberzahl theKey) {
  this->key = theKey;
}

uberzahl Speck::encrypt(uberzahl plaintext) {
  uberzahl left = plaintext >> WORDSIZE/2;
  uberzahl right = plaintext & ((1<<WORDSIZE/2)-1);
  
  for (int i=0; i<NUMROUNDS; i++) {
    left = (left.rotateRight(ALPHA, 0, WORDSIZE/2) + right) ^ keywords[i];
    right = right.rotateLeft(BETA, 0, WORDSIZE/2) ^ left;
  }
}

int main() {
  uberzahl x; // = 13;
}
