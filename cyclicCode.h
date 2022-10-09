#ifndef CYCLICCODE_H
#define CYCLICCODE_H
#include "codeBasic.h"

class CyclicCode: public Code { // for now only works in binary

    public:
        CyclicCode();
        CyclicCode(int the_n, int the_k, int the_d, int the_q);
        void setGenerator(const Row<int> the_gen);
        Row<int> getGenerator();
        Row<int> CyclicEncode(const Row<int> the_word, const Row<int> the_gen);
        Row<int> CyclicDecode(const Row<int> the_receivedWord); // this function finds the original word

    private:
        Row<int> generator;

};

#endif
