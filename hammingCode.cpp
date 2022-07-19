#include "hammingCode.h"

// this function gives the parity-check matrix. Need to figure out how to create this when q is not 2.
Mat<int> HammingCode::parityCheck (int n, int r, int q) {
    Mat<int> H(n,r,fill::zeros);
    for (int i=1; i < n+1; i++) {
        vector<int> row = baseq_rep(i,q,r);
        for (int j=0; j < r; j++) {
            H(i-1,j) = row[j];
        }
    }
    return H;
}
