#ifndef XNOR_H
#define XNOR_H

#include "Binary.h"
#include "Xor.h"

class Xnor:public Binary{
private:
public:
	int getResult(int l , int r){
                Not n ;
                Xor x ;
                return (n.getResult(x.getResult(l,r)));
	}
};


#endif
