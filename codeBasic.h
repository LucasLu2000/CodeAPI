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

// this is the parent class
class Code {
    public:
        Code(); // should ask the user for the word and then the generator matrix
        Code(int the_n, int the_k, int the_d, int the_q);
        int getN();
        int getK();
        int getD();
        int getQ();
        void printCode(); // should print n, k, d, the type of the code and then the
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
        vector<int> getPivotCols (Mat<int M>);
        Mat<int> rightInvMatrix (Mat<int> M);

    private:
        int n;
        int k;
        int d;
        int q; // the number of GF, so it must be a prime or a power of prime
        Row<int> word;
        Mat<int> genMatrix;
        Row<int> codeWord;
        Row<int> receivedWord;

};

#endif
