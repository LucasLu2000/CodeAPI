#ifndef HAMMINGCODE_H
#define HAMMINGCODE_H
#include "codeBasic.h"

class HammingCode: public Code {
    public:
        HammingCode();
        HammingCode(int the_n, int the_k, int the_d, int the_q, int the_r);
        void parityCheck();
        void HammingEncode(Row<int> the_word);
        Row<int> HammingDecode(Row<int> the_receivedWord); // this function finds the original word

    private:
        int r;
        Row<int> word;
        Mat<int> genMatrix;
        Mat<int> parityCheckMatrix;
        Row<int> codeWord;
        Row<int> receivedWord;

};

#endif
