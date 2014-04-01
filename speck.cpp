#include "speck.h"

Speck::Speck() {
	genKey();
}

void Speck::genKey() {
	
	srand(time(NULL));
	key.setBit(0);
	for(int i = 1; i < KEYSIZE; ++i) {
		key = (key << 1) | (rand() % 2);
	}
	//cout << key << endl;
}

void Speck::keyExpansion(){
	for(int i =0; i < NUMROUNDS - 2; i++){
	}
}

void Speck::setKey(uberzahl userKey) {
  this->key = userKey;
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
  Speck speck;	//single instance of speck class
	uberzahl x; // = 13;
	//speck.genKey();
}
