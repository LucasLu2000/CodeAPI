#ifndef GOLAYCODE_H
#define GOLAYCODE_H
#include "codeBasic.h"

class Code {
    public:
        GolayEncode();
        GolayDecode();

    private:
        Row<int> word;
        Row<int> codeWord;

};

#endif
