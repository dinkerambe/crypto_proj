#include "speck.h"

Speck::Speck() {
	genKey();
}

uberzahl Speck::trimmedNum(uberzahl num, int bits) {
  return num & ( (uberzahl("1") << bits) - 1);
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
	//x = trimmedNum(x, WORDSIZE);
	x = x ^ k;
	x = trimmedNum(x, WORDSIZE);
	y = y.rotateLeft(BETA, 0, WORDSIZE - 1);
	y = y ^ x;	
	y = trimmedNum(y, WORDSIZE);
}

void Speck::contract(uberzahl &x, uberzahl &y, uberzahl k){
	y = y ^ x;	
	y = trimmedNum(y, WORDSIZE);
	y = y.rotateRight(BETA, 0, WORDSIZE - 1);
	x = x ^ k;
	x = trimmedNum(x, WORDSIZE);
	if (x<y) {
	  x = (uberzahl("1") << WORDSIZE) - (y-x);
	} else {
  	x = x - y;
  }
	//x = trimmedNum(x, WORDSIZE);
	x = x.rotateLeft(ALPHA, 0, WORDSIZE - 1);
}

uberzahl Speck::encrypt(uberzahl plaintext) {
  uberzahl left = plaintext >> WORDSIZE;
  uberzahl right = trimmedNum(plaintext, WORDSIZE);


  for(int i = 0; i < NUMROUNDS; i++){
    expand(left, right, rounds[i]);				//encrypt
  }
  cout <<"Separated Result " << left << " " << right << endl;
  return (left << WORDSIZE) | right;
}

uberzahl Speck::decrypt(uberzahl ciphertext) {
  uberzahl left = ciphertext >> WORDSIZE;
  uberzahl right = trimmedNum(ciphertext, WORDSIZE);
  
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
	
  const int testVectorLen = 7;
  uberzahl key[testVectorLen], cipher[testVectorLen], plain[testVectorLen];
	
  key[0] = "20011376718272490338853433276725592320";
  cipher[0] = "221137820289473687857657110085594713368";
  plain[0] = "144062678019685919772856771483193666848";
	
  key[1] = "0";
  cipher[1] = "1000444146172915417172513437297852742";
  plain[1] = "144062678019685919772856771483193666848";
	
  key[2] = "1";
  cipher[2] = "197518563100430107023787069588039329421";
  plain[2] = "152037107215241021449068138290853736037";
	
  key[3] = "1442304682729575737805390361686";
  cipher[3] = "32096542000650209713025123876611961071";
  plain[3] = "111111111111111111111111111111111";
	
  key[4] = "12345678901234567890123456";
  cipher[4] = "215825222094735503735129327493762389553";
  plain[4] = "111111111111111111111111111111111";
	
  key[5] = "5176156079219501789779";
  cipher[5] = "84750170069882828649038465849818186684";
  plain[5] = "1189998819991197253";
	
  key[6] = "1189998819991197253";
  cipher[6] = "132247081460443199909686876827324754061";
  plain[6] = "1189998819991197253";
  
  for (int i=0; i<testVectorLen; i++) {
  
    uberzahl testcipher = speck.encrypt(key[i], plain[i]);
    cout << "Expected ciphertext:\t" << cipher[i] << endl 
          << "Resulting ciphertext:\t" << testcipher << endl;

    uberzahl testplain = speck.decrypt(key[i], testcipher);
    cout << "Expected plaintext:\t" << plain[i] << endl 
         << "Result plaintext:\t" << testplain << endl;
    cout << "-----------------------------------------" << endl;
  }

	return 0;
}
