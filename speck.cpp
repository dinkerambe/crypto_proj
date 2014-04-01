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

void Speck::expand(uberzahl x, uberzahl y, uberzahl k){
	x = x.rotateRight(ALPHA,0,WORDSIZE-1);
	x = x + y;
	x = x ^ k;
	y = y.rotateLeft(BETA,0, WORDSIZE-1);
	y = y ^ x;	
}

void Speck::setKey(uberzahl userKey) {
  this->key = userKey;
  // For testing:
  for (int i=0; i<NUMROUNDS; i++) {
    keywords[i] = i;
  }
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
  uberzahl left = plaintext >> WORDSIZE;
  uberzahl right = plaintext & ((uberzahl("1")<<WORDSIZE)-1);
  uberzahl leftKeyWord = keywords[1];
  uberzahl rightKeyWord = keywords[0];
  //This is not correct 
  /*for (int i=0; i<NUMROUNDS; i++) {
    left = (left.rotateRight(ALPHA, 0, WORDSIZE) + right) ^ keywords[i];
    right = right.rotateLeft(BETA, 0, WORDSIZE) ^ left;
  }*/
  for(int i =0; i < NUMROUNDS-2; i++){
    expand(left,right, keywords[0]);//encrypt
    expand(leftKeyWord, rightKeyWord, i);
  }
  return (left << WORDSIZE) + right;
}

uberzahl Speck::decrypt(uberzahl ciphertext) {
  uberzahl left = ciphertext >> WORDSIZE;
  uberzahl right = ciphertext & ((uberzahl("1")<<WORDSIZE)-1);
  
  for (int i=NUMROUNDS-1; i>=0; i--) {
    right = right ^ left;
    right = right.rotateRight(BETA, 0, WORDSIZE);
    left = left ^ keywords[i];
    left = left - right;
    left = left.rotateLeft(ALPHA, 0, WORDSIZE);
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
  uberzahl testcipher = speck.encrypt(plain);
  cout << "expected: " << cipher << endl << "result:   " << testcipher << endl;
  uberzahl testplain = speck.decrypt(testcipher);
  cout << "expected: " << plain << endl << "result:   " << testplain << endl;
}
