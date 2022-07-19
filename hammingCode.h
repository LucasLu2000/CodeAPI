#ifndef HAMMINGCODE_H
#define HAMMINGCODE_H
#include "codeBasic.h"

class HammingCode {
    public:
        HammingCode(Row<int>);



    private:
        Mat<int> parityCheck (int n, int r, int q);

};

#endif
