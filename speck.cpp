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
  uberzahl left = plaintext >> WORDSIZE;
  uberzahl right = plaintext & ((uberzahl("1")<<WORDSIZE)-1);
  
  for (int i=0; i<NUMROUNDS; i++) {
    left = (left.rotateRight(ALPHA, 0, WORDSIZE) + right) ^ keywords[i];
    right = right.rotateLeft(BETA, 0, WORDSIZE) ^ left;
  }
  return (left << WORDSIZE) + right;
}

int main() {
  Speck speck;	//single instance of speck class
	uberzahl x; // = 13;
	//speck.genKey();
  uberzahl key = "20011376718272490338853433276725592320";
  uberzahl cipher = "147139012391338450886016132908936943925";
  uberzahl plain = "144062678019685919772856771483193666848";
}
