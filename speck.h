#include <iostream>
#include "uberzahl.h"
using namespace std;

#define WORDSIZE 64 		// n
#define NUMKEYWORDS 4 	// m
#define ROUNDS 34 			// T
#define KEYSIZE 128
#define ALPHA = 8
#define BETA = 3


class Speck {
  public:
    Speck();
    void setKey(uberzahl userKey);
		void genKey();
    void keyExpansion()
    uberzahl encrypt(uberzahl);
    uberzahl decrypt(uberzahl);
  private:
    uberzahl key;
    uberzahl * keywords;
};

