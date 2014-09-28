#pragma once

#include "Binary.h"

class Or : public Binary{
public:
	int getResult(int l , int r){
		return (r|l);
	}
};