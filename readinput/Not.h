#ifndef NOT_H
#define NOT_H

#include "Unary.h"

class Not:public Unary{
private:
public:
    int getResult(int l , int r = 0){
            return (l ? 0 : 1) ;
	}
};

#endif
