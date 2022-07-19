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
        Code(Row<int>);
        Mat<int> randomMatrix (int r, int c, int q);
        int compareRowVec (Row<int> a, Row<int> b);
        Mat<int> nonNegativeMatrix (Mat<int> M, int q);
        Mat<int> dividesMatrix (Mat<int> M, int x, int q);
        

    private:

};

#endif
