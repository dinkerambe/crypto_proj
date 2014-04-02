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
	//setKey_all(key);
	//cout << key << endl;
}

void Speck::setKey(uberzahl userKey) {
  this->key = userKey;
}

void Speck::setKeyWords(){
	for(int i = 0; i < NUMKEYWORDS; ++i){
		keywords[i] = key;
		keywords[i] = (keywords[i] >> (WORDSIZE*(i)));//NUMKEYWORDS - 1 - i 	
		for(int j = WORDSIZE; j < KEYSIZE; ++j) {
			keywords[i].clearBit(j);
		}
	}
}

void Speck::setKey_all(uberzahl userKey){
	setKey(userKey);
	setKeyWords();

  uberzahl leftKeyWord = keywords[1];
  uberzahl rightKeyWord = keywords[0];
  
  // Shift keywords and store for later
  for(int i = 0; i < NUMROUNDS; i++){
    rounds[i] = rightKeyWord;
    expand(leftKeyWord, rightKeyWord, uberzahl(i));
  }
  
	///cout<< "KEY:\t\t" << key << endl;
	///cout<< "Keywords:\t" << keywords[1] << " " << keywords[0] << endl;
}

void Speck::expand(uberzahl &x, uberzahl &y, uberzahl k){
	x = x.rotateRight(ALPHA, 0, WORDSIZE - 1);	
	x = x + y;
	x = x & ( (uberzahl("1") << WORDSIZE) - 1);
	x = x ^ k;
	x = x & ( (uberzahl("1") << WORDSIZE) - 1);
	y = y.rotateLeft(BETA, 0, WORDSIZE - 1);
	y = y ^ x;	
	y = y & ( (uberzahl("1") << WORDSIZE) - 1);
}

void Speck::contract(uberzahl &x, uberzahl &y, uberzahl k){
	y = y ^ x;	
	y = y & ( (uberzahl("1") << WORDSIZE) - 1);
	y = y.rotateRight(BETA, 0, WORDSIZE - 1);
	x = x ^ k;
	x = x & ( (uberzahl("1") << WORDSIZE) - 1);
	if (x<y) {
	  x = (uberzahl("1") << WORDSIZE) - (y-x);
	} else {
  	x = x - y;
  }
	x = x & ( (uberzahl("1") << WORDSIZE) - 1);
	x = x.rotateLeft(ALPHA, 0, WORDSIZE - 1);
}

uberzahl Speck::encrypt(uberzahl plaintext) {
  uberzahl left = plaintext >> WORDSIZE;
  uberzahl right = plaintext & ( (uberzahl("1") << WORDSIZE) - 1);


  for(int i = 0; i < NUMROUNDS; i++){
    expand(left, right, rounds[i]);				//encrypt
  }
  cout <<"Separated Result " << left << " " << right << endl;
  return (left << WORDSIZE) | right;
}

uberzahl Speck::decrypt(uberzahl ciphertext) {
  uberzahl left = ciphertext >> WORDSIZE;
  uberzahl right = ciphertext & ((uberzahl("1")<<WORDSIZE)-1);
  
  for (int i=NUMROUNDS-1; i>=0; i--) {
    contract(left, right, rounds[i]);
  }
  return (left << WORDSIZE) + right;
}

uberzahl Speck::encrypt(uberzahl key, uberzahl plaintext) {
  setKey_all(key);
  return encrypt(plaintext);
}

uberzahl Speck::decrypt(uberzahl key, uberzahl ciphertext) {
  setKey_all(key);
  return decrypt(ciphertext);
}

int main() {
  Speck speck;	//single instance of speck class
	uberzahl x; // = 13;
	//speck.genKey();
 // uberzahl key = "20011376718272490338853433276725592320";
 // uberzahl cipher = "147139012391338450886016132908936943925";
 // uberzahl plain = "144062678019685919772856771483193666848";
  
	
  uberzahl key = "20011376718272490338853433276725592320";
  uberzahl cipher = "221137820289473687857657110085594713368";
  uberzahl plain = "144062678019685919772856771483193666848";
  
  uberzahl testcipher = speck.encrypt(key, plain);
  cout << "Expected ciphertext:\t" << cipher << endl 
				<< "Resulting ciphertext:\t" << testcipher << endl;

  uberzahl testplain = speck.decrypt(key, testcipher);
  cout << "Expected plaintext:\t" << plain << endl 
			 << "Result plaintext:\t" << testplain << endl;

	return 0;
}
