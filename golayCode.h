#ifndef GOLAYCODE_H
#define GOLAYCODE_H
#include "codeBasic.h"
#include "cyclicCode.h"

class GolayCode: public CyclicCode { // for now only works in binary

    public:
        GolayCode();
        GolayCode(int the_n, int the_k, int the_d, int the_q);
        void checkGolay();
        // void setGolayParityCheck();
        // Row<int> GolayEncode(const Row<int> the_word);
        // Row<int> GolayDecode(const Row<int> the_receivedWord); // this function finds the original word

    private:
        const Row<int> golayGenerator = {1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1};

};

#endif
