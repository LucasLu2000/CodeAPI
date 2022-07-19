#ifndef HAMMINGCODE_H
#define HAMMINGCODE_H
#include "codeBasic.h"

class HammingCode: public Code {
    public:
        HammingCode();
        Row<int> HammingEncode(Row<int> the_word);
        Row<int> HammingDecode(Row<int> the_receivedWord); // this function finds the original word

    private:
        Mat<int> parityCheck(int n, int r, int q);
        Mat<int> getGenMatrix();
        Row<int> word;
        Mat<int> genMatrix;
        Row<int> codeWord;
        Row<int> receivedWord;

};

#endif
