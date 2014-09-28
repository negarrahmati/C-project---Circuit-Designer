#ifndef AND_H
#define AND_H

#include "Binary.h"

class And : public Binary{
public:
	int getResult(int l , int r){
		return r*l;
	}
};

#endif