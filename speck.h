#include <iostream>
#include "uberzahl.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
using namespace std;

#define NUMKEYWORDS 2 	// m
#define NUMROUNDS 32 		// T
#define WORDSIZE 64 		// n
#define BLOCKSIZE 128
#define KEYSIZE 128
#define ALPHA 8
#define BETA 3

class Speck {
  public:
    Speck();
    void genKey();
    void expand(uberzahl &x, uberzahl &y, uberzahl &k);
    void setKeyWords();
    void setKey_all(uberzahl userKey);
    void setKey(uberzahl userKey);
    uberzahl encrypt(uberzahl plaintext);
    uberzahl decrypt(uberzahl ciphertext);
    uberzahl encrypt(uberzahl key, uberzahl plaintext);
    uberzahl decrypt(uberzahl key, uberzahl ciphertext);
  private:
    uberzahl key;
    uberzahl keywords[NUMROUNDS];
};

