#include "speck.h"

void Speck::genKey() {
	for(int i = 0; i < KEYSIZE; ++i) {
		key << 1;
		//get random bit
		//or with key	
	}
}

void Speck::rotate(uberzahl x, uberzahl y, uberzahl k){
	x = x.rotateRight(ALPHA,0,WORDSIZE-1);
	x = x + y;
	x = x ^ k;
	y = y.rotateLeft(BETA,0, WORDSIZE-1);
	y = y ^ x;	
}

void Speck::setKey(uberzahl theKey) {
  this->key = theKey;
}

void Speck::setKeyWords(){
	for(int i =0; i < NUMKEYWORDS; i++){
		keywords[i] = key;
		keywords[i] = (keywords[i] >> (WORDSIZE*i));	
	}
}

void Speck::setKey_All(uberzahl key){
	this->key = key;
	this->setKeyWords();
}

uberzahl Speck::encrypt(uberzahl plaintext) {
  uberzahl left = plaintext >> WORDSIZE/2;
  uberzahl right = plaintext & ((uberzahl("1")<<WORDSIZE/2)-1);
  
  for (int i=0; i<NUMROUNDS; i++) {
    left = (left.rotateRight(ALPHA, 0, WORDSIZE/2) + right) ^ keywords[i];
    right = right.rotateLeft(BETA, 0, WORDSIZE/2) ^ left;
  }
  return (left << WORDSIZE/2) + right;
}

int main() {
  uberzahl x; // = 13;
}
