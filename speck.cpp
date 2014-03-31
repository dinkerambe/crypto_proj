#include <iostream>
#include "uberzahl.h"
using namespace std;

#define WORDSIZE 64
#define NUMKEYWORDS 4
#define ROUNDS 34

class Speck {
  public:
    Speck();
    void setKey(uberzahl);
    uberzahl encrypt(uberzahl);
    uberzahl decrypt(uberzahl);
  private:
    uberzahl key;
    uberzahl * keywords;
};

int main() {
  uberzahl x = 13;
}
