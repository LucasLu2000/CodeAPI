#ifndef HAMMINGCODE_H
#define HAMMINGCODE_H
#include "codeBasic.h"

class HammingCode: public Code {
    public:
        HammingCode();
        HammingCode(int the_n, int the_k, int the_d, int the_q, int the_r);
        void setHammingParityCheck();
        void setHammingGenMatrix();
        Row<int> HammingEncode(Row<int> the_word);
        Row<int> HammingDecode(Row<int> the_receivedWord); // this function finds the original word

    private:
        int r;

};

#endif
