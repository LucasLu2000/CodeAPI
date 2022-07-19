#ifndef CODEBASIC_H
#define CODEBASIC_H
#include <iostream>
#include <fstream>
#include <armadillo>
#include <vector>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
using namespace arma;

class Code {
    public:
        Code();
        Row<int> encode();
        Row<int> decode();
        Mat<int> randomMatrix (int r, int c, int q); // this function creates a random matrix over a field given the number of rows and number of columns
        int compareRowVec (Row<int> a, Row<int> b);
        Mat<int> nonNegativeMatrix (Mat<int> M, int q);
        Mat<int> dividesMatrix (Mat<int> M, int x, int q);
        vector<int> baseq_rep (int n, int q, int length);
        Mat<int> modMatrix (Mat<int> M, int q);
        Mat<int> rrefMatrix (Mat<int> M, int q);
        Mat<int> noZeroRowMatrix (Mat<int> M);


    private:
        Row<int> word;
        Mat<int> genMatrix;
        Row<int> codeWord;
        Row<int> receivedWord;

};

#endif
