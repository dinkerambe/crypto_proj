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
	setKey_all(key);
	//cout << key << endl;
}

void Speck::expand(uberzahl &x, uberzahl &y, uberzahl k){
	x = x.rotateRight(ALPHA,0,WORDSIZE-1);
	x = x + y;
	x = x ^ k;
	y = y.rotateLeft(BETA,0, WORDSIZE-1);
	y = y ^ x;	
}

void Speck::contract(uberzahl &x, uberzahl &y, uberzahl k){
	y = y ^ x;
	y = y.rotateRight(BETA,0, WORDSIZE-1);
	x = x ^ k;
	x = x - y;
	x = x.rotateLeft(ALPHA,0,WORDSIZE-1);
}

void Speck::setKey(uberzahl userKey) {
  this->key = userKey;
}

void Speck::setKeyWords(){
	for(int i =0; i < NUMKEYWORDS; i++){
		keywords[i] = key;
		keywords[i] = (keywords[i] >> (WORDSIZE*i));	
	}
}

void Speck::setKey_all(uberzahl key){
	this->key = key;
	this->setKeyWords();
	cout << "KEY:\t\t" << key<<endl;
	cout << "Keywords:\t"<<keywords[1] << " " << keywords[0]<<endl;
}

uberzahl Speck::encrypt(uberzahl plaintext) {
  uberzahl left = plaintext >> WORDSIZE;
  uberzahl right = plaintext & ((uberzahl("1")<<WORDSIZE)-1);
  cout << "PLAINTEXT " << plaintext << endl;
  cout << "left and right " << left << " " << right << endl;
  uberzahl leftKeyWord = keywords[1];
  uberzahl rightKeyWord = keywords[0];
  //This is not correct 
  /*for (int i=0; i<NUMROUNDS; i++) {
    left = (left.rotateRight(ALPHA, 0, WORDSIZE) + right) ^ keywords[i];
    right = right.rotateLeft(BETA, 0, WORDSIZE) ^ left;
  }*/
  for(int i =0; i < NUMROUNDS; i++){
    expand(left,right, rightKeyWord);//encrypt
    expand(leftKeyWord, rightKeyWord,uberzahl(i));
  }
  return (left << WORDSIZE) + right;
}

uberzahl Speck::decrypt(uberzahl ciphertext) {
  uberzahl left = ciphertext >> WORDSIZE;
  uberzahl right = ciphertext & ((uberzahl("1")<<WORDSIZE)-1);
  uberzahl leftKeyWord = keywords[1];
  uberzahl rightKeyWord = keywords[0];
  //This is not correct 
  /*for (int i=0; i<NUMROUNDS; i++) {
    left = (left.rotateRight(ALPHA, 0, WORDSIZE) + right) ^ keywords[i];
    right = right.rotateLeft(BETA, 0, WORDSIZE) ^ left;
  }*/
  for (int i=NUMROUNDS-1; i>=0; i--) {
    contract(leftKeyWord, rightKeyWord,uberzahl(i));
    contract(left,right, rightKeyWord);//encrypt
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
	
  uberzahl omg = (uberzahl("1")<<64)-1;
  cout << "FISRST " << omg <<endl;
  omg = omg.rotateLeft(1, 0, 63);
  cout << "WTF OM G " << omg <<endl;
	//speck.genKey();
  uberzahl key = "20011376718272490338853433276725592320";
  uberzahl cipher = "147139012391338450886016132908936943925";
  uberzahl plain = "144062678019685919772856771483193666848";
  cout << "plain is "<< (uberzahl("1")<<64)+uberzahl("1") <<endl;
  
  uberzahl testcipher = speck.encrypt(69696969);//plain);
  cout << "expected: " << cipher << endl << "result:   " << testcipher << endl;
  uberzahl testplain = speck.decrypt(testcipher);
  cout << "expected: " << plain << endl << "result:   " << testplain << endl;
}
