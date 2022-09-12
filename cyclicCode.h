#ifndef CYCLICCODE_H
#define CYCLICCODE_H
#include "codeBasic.h"

class CyclicCode: public Code { // for now only works in binary

    public:
        CyclicCode();
        CyclicCode(int the_n, int the_k, int the_d, int the_q);
        void setCyclicParityCheck();
        void setCyclicGenMatrix();

};

#endif
