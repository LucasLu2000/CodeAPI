#ifndef GOLAYCODE_H
#define GOLAYCODE_H
#include "codeBasic.h"

class GolayCode: public Code { // for now only works in binary
    public:
        GolayCode();
        GolayCode(int the_n, int the_k, int the_d, int the_q);
        void checkGolay();
        void setGolayParityCheck();
        void setGolayGenMatrix();
        Row<int> GolayEncode(const Row<int> the_word);
        Row<int> GolayDecode(const Row<int> the_receivedWord); // this function finds the original word

};

#endif
