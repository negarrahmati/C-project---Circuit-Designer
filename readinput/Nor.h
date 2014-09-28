#ifndef NOR_H
#define NOR_H

#include "Binary.h"
#include "Not.h"

class Nor:public Binary{
private:
public:
	int getResult(int l , int r){
                Not n;
                return n.getResult(l | r);
	}
};


#endif
