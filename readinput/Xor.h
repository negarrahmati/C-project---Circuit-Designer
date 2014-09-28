#ifndef XOR_H
#define XOR_H

#include "Binary.h"
#include "Not.h"

using namespace std;

class Xor:public Binary{
private:
public:
        int getResult(int l , int r);
};
#endif
