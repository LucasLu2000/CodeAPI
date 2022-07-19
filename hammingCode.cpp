#include "hammingCode.h"

Mat<int> HammingCode::randomMatrix(int r, int c, int q) {
    Mat<int> M(r,c,fill::zeros);
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            M(i,j) = rand() % q;
        }
    }
    return M;
}
