#include "codeBasic.h"

Code::Code() : n(1), k(1), d(1), q(2) {
    // string input; // get a word from the user
    // cout << "Enter the length of the code: " << endl;
    // cin >> n;
    // cout << "Enter the r for a Hamming code of parameter [2^r-1,2^r-r-1,3]" << endl;
    // cin >> r;
    // cout << "Enter a word of length " << n-r << " over the binary field: ";
    // cin >> input;
    // Row<int> word(n-r,fill::zeros);
    // for (int i=0; i < input.length(); i++) {
    //     word[i] = input[i] - '0'; // convert each char to an int
    // }
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

void Code::printCode() {
    cout << "The parameters of the code are: " << n << ", " << k << ", " << d;
}

// this function creates a random matrix over a field given the number of rows and number of columns
Mat<int> Code::randomMatrix (int r, int c, int q) {
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
int Code::compareRowVec (Row<int> a, Row<int> b) {
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
Mat<int> Code::nonNegativeMatrix (Mat<int> M, int q) {
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
Mat<int> Code::dividesMatrix (Mat<int> M, int x, int q) {
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
vector<int> Code::baseq_rep (int n, int q, int length) {
    vector<int> number = {};
    for (int i = 0; i < length; i++) {
        int remainder = n % q;
        number.push_back(remainder);
        n = n / q;
    }
    return number;
}

// this function changes a matrix from base 10 to base 2
Mat<int> Code::modMatrix (Mat<int> M, int q) {
    Mat<int> Mmodq = M;
    for (int i=0; i < Mmodq.n_rows; i++) {
        for (int j=0; j < Mmodq.n_cols; j++) {
            int ij = M(i,j);
            Mmodq(i,j) = ij % q;
        }
    }
    return Mmodq;
}

Mat<int> Code::rrefMatrix (Mat<int> M, int q) {
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
            // cout << endl;
            // cout << "nonZero: " << GD(i,nonZeroIndex) << endl;
            rrefM.row(i) = dividesMatrix(rrefM.row(i),rrefM(i,nonZeroIndex),q);
            // cout << "i: " << i << endl;
            for (int k=0; k < rrefM.n_rows; k++) {
                if (k != i) {
                    // GD.row(k).print("k: ");
                    rrefM.row(k) = nonNegativeMatrix((rrefM.row(k) - (rrefM.row(i) * rrefM(k,nonZeroIndex))),q);
                    // GD.row(k).print("k: ");
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

//
Mat<int> Code::noZeroRowMatrix (Mat<int> M) {
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
