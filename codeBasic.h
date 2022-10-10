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
        int getN() const;
        int getK() const;
        int getD() const;
        int getQ() const;
        void setWord(Row<int> the_word);
        void setReceivedWord(Row<int> the_receivedWord);
        Row<int> getWord();
        Row<int> getReceivedWord();
        void setParityCheck(Mat<int> the_parityCheckMatrix);
        Mat<int> getParityCheck();
        void setGenMatrix(Mat<int> the_genMatrix);
        Mat<int> getGenMatrix();
        void printCode(); // should print n, k, d, the type of the code
        Row<int> encode();
        Row<int> decode();
        Mat<int> randomMatrix(int r, int c); // this function creates a random matrix over a field given the number of rows and number of columns
        int compareRowVec(Row<int> a, Row<int> b);
        Mat<int> nonNegativeMatrix(Mat<int> M);
        Mat<int> dividesMatrix(Mat<int> M, int x);
        vector<int> baseq_rep(int n, int length);
        Mat<int> modMatrix(Mat<int> M);
        Mat<int> rrefMatrix(Mat<int> M);
        Mat<int> noZeroRowMatrix(Mat<int> M);
        vector<int> getPivotCols(const Mat<int> &M);
        Mat<int> getMatrixByCols(const Mat<int> &M, const vector<int> &pivotColList);
        Mat<int> rightInvMatrix(const Mat<int> &M);
        int countElement(Mat<int> M, int element);

    protected:
        int n;
        int k;
        int d;
        int q; // the number of GF, so it must be a prime or a power of prime

    private:
        void setN(int the_n);
        void setK(int the_k);
        void setD(int the_d);
        void setQ(int the_q);
        Row<int> word;
        Mat<int> parityCheckMatrix;
        Mat<int> genMatrix;
        Row<int> codeWord;
        Row<int> receivedWord;

};

#endif
