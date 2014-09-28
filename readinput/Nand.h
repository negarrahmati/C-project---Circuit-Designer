#ifndef NAND_H
#define NAND_H

#include "Binary.h"
#include "Not.h"

class Nand:public Binary{
private:
public:
	int getResult(int l , int r){
                Not n;
                return n.getResult(l*r , 0);
	}
};


#endif
