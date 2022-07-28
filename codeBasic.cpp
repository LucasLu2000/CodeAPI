#include "codeBasic.h"

Code::Code() : n(1), k(1), d(1), q(2) {

}

Code::Code(int the_n, int the_k, int the_d, int the_q) : n(the_n), k(the_k), d(the_d), q(the_q) {

}

int Code::getN() {
    return n;
}

int Code::getK() {
    return k;
}

int Code::getD() {
    return d;
}

int Code::getQ() {
    return q;
}

void Code::setWord(Row<int> the_word) {
    word = the_word;
}

void Code::setReceivedWord(Row<int> the_receivedWord) {
    receivedWord= the_receivedWord;
}

Row<int> Code::getWord() {
    return word;
}

Row<int> Code::getReceivedWord() {
    return receivedWord;
}

void Code::setParityCheck(Mat<int> the_parityCheckMatrix) {
    parityCheckMatrix = the_parityCheckMatrix;
}

Mat<int> Code::getParityCheck() {
    return parityCheckMatrix;
}

void Code::setGenMatrix(Mat<int> the_genMatrix) {
    genMatrix = the_genMatrix;
}

Mat<int> Code::getGenMatrix() {
    return genMatrix;
}

void Code::printCode() {
    cout << "The parameters of the code are: " << n << ", " << k << ", " << d;
}

// this function creates a random matrix over a field given the number of rows and number of columns
Mat<int> Code::randomMatrix(int r, int c, int q) {
    Mat<int> M(r,c,fill::zeros);
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            M(i,j) = rand() % q;
        }
    }
    return M;
}

// this function compares two row vectors having the same length.
// It returns 1 if larger, 0 if equal, and -1 if smaller.
int Code::compareRowVec(Row<int> a, Row<int> b) {
    int compareInt = 0;
    for (int i=0; i<a.n_cols; i++) {
        if (a(i) > b(i)) {
            compareInt = 1;
            break;
        }
        else if (a(i) < b(i)) {
            compareInt = -1;
            break;
        }
    }
    return compareInt;
}

// this function turns all entries of a matrix in a field to be non-negative
Mat<int> Code::nonNegativeMatrix(Mat<int> M, int q) {
    Mat<int> Mdivide = M;
    for (int i=0; i < M.n_rows; i++) {
        for (int j=0; j < M.n_cols; j++) {
            while (Mdivide(i,j) < 0) {
                Mdivide(i,j) = Mdivide(i,j)+q;
            }
        }
    }
    return Mdivide;
}

// this function divids a matrix (a row class object also works) by an element in the field
Mat<int> Code::dividesMatrix(Mat<int> M, int x, int q) {
    Mat<int> Mdivide = M;
    for (int i=0; i < M.n_rows; i++) {
        for (int j=0; j < M.n_cols; j++) {
            int ij = M(i,j);
            while ((ij % x) != 0) {
                ij += q;
            }
            ij = ij / x;
            Mdivide(i,j) = ij;
        }
    }
    return Mdivide;
}

// this function changes n from base 10 to base q and then returns a vector of a given length
vector<int> Code::baseq_rep(int n, int q, int length) {
    vector<int> number = {};
    for (int i = 0; i < length; i++) {
        int remainder = n % q;
        number.push_back(remainder);
        n = n / q;
    }
    return number;
}

// this function changes a matrix from base 10 to base 2
Mat<int> Code::modMatrix(Mat<int> M, int q) {
    Mat<int> Mmodq = M;
    for (int i=0; i < Mmodq.n_rows; i++) {
        for (int j=0; j < Mmodq.n_cols; j++) {
            int ij = M(i,j);
            Mmodq(i,j) = ij % q;
        }
    }
    return Mmodq;
}

// this functions returns rref of the matrix
Mat<int> Code::rrefMatrix(Mat<int> M, int q) {
    Mat<int> rrefM = M;
    // the next step is to find the rref of GD, for now only work in binary field
    for (int i=0; i < rrefM.n_rows; i++) {
        int nonZeroIndex = 0;
        for (int j=0; j < rrefM.n_cols; j++) {
            if (rrefM(i,j) != 0) {
                j = rrefM.n_cols;
                break;
            }
            else {
                nonZeroIndex ++;
            }
        }
        if (nonZeroIndex < rrefM.n_cols) {
            rrefM.row(i) = dividesMatrix(rrefM.row(i),rrefM(i,nonZeroIndex),q);
            for (int k=0; k < rrefM.n_rows; k++) {
                if (k != i) {
                    rrefM.row(k) = nonNegativeMatrix((rrefM.row(k) - (rrefM.row(i) * rrefM(k,nonZeroIndex))),q);
                }
            }
        }
    }

    rrefM = modMatrix(rrefM,q);

    // permute the rows. Try to put numbers to the top left corner using bubble sort algorithm
    int count = 0;
    while (count < rrefM.n_rows-1) {
        count = 0;
        for (int i=0; i < rrefM.n_rows-1; i++) {
            if (compareRowVec(rrefM.row(i),rrefM.row(i+1)) == -1) {
                rrefM.swap_rows(i,i+1);
            }
            else {
                count ++;
            }
        }
    }

    return rrefM;
}

// this function eliminates all zero rows in a matrix
Mat<int> Code::noZeroRowMatrix(Mat<int> M) {
    Mat<int> MnoZero;
    vector<int> rowList;
    for (int i=0; i < M.n_rows; i++) {
        int allZero = 1;
        for (int j=0; j < M.n_cols; j++) {
            if (M(i,j) != 0) {
                allZero = 0;
                break;
            }
        }
        if (allZero == 0) {
            rowList.push_back(i);
        }
    }
    MnoZero = M.row(rowList[0]);
    for (int i=1; i < rowList.size(); i++) {
        MnoZero = join_vert(MnoZero,M.row(rowList[i]));
    }
    return MnoZero;
}

// this function finds all pivot columns and then return them as a vector
vector<int> Code::getPivotCols(const Mat<int> &M) {
     vector<int> newPermuList; // record the the index of all pivot column
     for (int i=0; i < M.n_cols; i++) { // cols
         for (int j=0; j < M.n_rows; j++) { // rows
             if (M(j,i) == 1) {
                 int count = 0;
                 for (int k=0; k < M.n_rows; k++) {
                     if (M(k,i) == 0) {
                         count++;
                     }
                 }
                 if (count == (M.n_rows-1)) {
                     newPermuList.push_back(i); // then we know that this column i is a pivot column
                     break;
                 }
             }
         }
     }
     return newPermuList;
}

// This function returns a sub matrix given a matrix and a list of column indexes
Mat<int> Code::getMatrixByCols(const Mat<int> &M, const vector<int> &pivotColList) {
    Mat<int> newM = M.col(pivotColList[0]);
    for (int i=1; i<pivotColList.size(); i++) {
        newM = join_horiz(newM,M.col(pivotColList[i]));
    }
    return newM;
}

//This function finds the right inverse of a matrix, the matrix must have more columns than rows and have full rank
Mat<int> Code::rightInvMatrix(const Mat<int> &M) {
    Mat<int> rrefM = rrefMatrix(M,q);
    vector<int> pivotColList = getPivotCols(rrefM);
    Mat<int> invM = getMatrixByCols(M,pivotColList);
    invM = join_horiz(invM,eye<Mat<int>>(M.n_rows,M.n_rows));
    invM = rrefMatrix(invM,q);
    invM.print("invM after rref:");
    invM = invM.submat(0,M.n_rows,M.n_rows-1,2*M.n_rows-1);
    Mat<int> rightInvM(M.n_cols,M.n_rows,fill::zeros);
    invM.print("invM:");
    int countIndex = 0; // count the row index of the square matrix
    for (int i=0; i<M.n_cols; i++) {
        if (find(pivotColList.begin(), pivotColList.end(), i) != pivotColList.end()) {
            rightInvM.row(i) = invM.row(countIndex);
            countIndex++;
        }
    }
    (M*rightInvM).print();
    return rightInvM;
}

int Code::countElement(Mat<int> M, int element) {
    int n = 0;
    for (int i=0; i<M.n_rows; i++) {
        for (int j=0; j<M.n_cols; j++) {
            if (M(i,j)==element) {
                n++;
            };
        }
    }
    return n;
}
