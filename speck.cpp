#include <iostream>
#include "uberzahl.h"
using namespace std;

#define WORDSIZE 64
#define NUMKEYWORDS 4
#define ROUNDS 34


class Speck {
  public:
    Speck();
    void setKey(uberzahl userKey);
		void genKye();
    uberzahl encrypt(uberzahl);
    uberzahl decrypt(uberzahl);
  private:
    uberzahl key;
    uberzahl * keywords;
};

void Speck::genKey() {
	for(int i = 0; i < KEYSIZE; ++i) {
		key << 1;
		//get random bit
		//or with key	
	}
}
int main() {
  uberzahl x; // = 13;
}
