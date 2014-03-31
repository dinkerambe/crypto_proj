#include <iostream>
#include "uberzahl.h"
using namespace std;

class Speck {
  public:
    Speck();
    void setKey(uberzahl);
    uberzahl encrypt(uberzahl);
    uberzahl decrypt(uberzahl);
  private:
    uberzahl key;
    uberzahl * keywords;
    int wordSize = 64;
    int keywords = 4;
    int rounds = 34;
};

int main() {
  uberzahl x = 13;
}