#include "Binary.h"
#include "Xor.h"


int Xor::getResult(int l , int r){
            Not n;
            return ((l*n.getResult(r,0)) | (r*n.getResult(l , 0)));
}
