#ifndef GOLAYCODE_H
#define GOLAYCODE_H
#include "codeBasic.h"

class GolayCode {
    public:
        GolayCode();
        Row<int> GolayEncode(Row<int> the_word);
        Row<int> GolayDecode(Row<int> the_receivedWord); // this function finds the original word

    private:
        Row<int> word;
        Mat<int> genMatrix;
        Row<int> codeWord;
        Row<int> receivedWord;

};

#endif
