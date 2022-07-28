#include "hammingCode.h"

HammingCode::HammingCode() : Code(), r(1) {

}

HammingCode::HammingCode(int the_n, int the_k, int the_d, int the_q, int the_r) : Code(the_n, the_k, the_d, the_q), r(the_r) {

}

// this function gives the parity-check matrix. Need to figure out how to create this when q is not 2.
void HammingCode::setHammingParityCheck() {
    // form the parity-check matrix by base changing
    Mat<int> H(n,r,fill::zeros);
    for (int i=1; i < n+1; i++) {
        vector<int> row = baseq_rep(i,q,r);
        for (int j=0; j < 3; j++) {
            H(i-1,j) = row[j];
        }
    }
    setParityCheck(H);
}

void HammingCode::setHammingGenMatrix() {
    setHammingParityCheck();
    Mat<int> H = getParityCheck();
    Mat<int> GD = H.t();
    GD = modMatrix(GD,q);
    GD = rrefMatrix(GD,q);
    GD.print("the parity-check matrix of the dual C:");
    GD = noZeroRowMatrix(GD);

    vector<int> permuList;
    for (int i=0; i < n; i++) {
        permuList.push_back(i);
    }

    vector<int> newPermuList; // record the the index of all pivot column
    for (int i=0; i < n; i++) { // cols
        for (int j=0; j < r; j++) { // rows
            if (GD(j,i) == 1) {
                int count = 0;
                for (int k=0; k < r; k++) {
                    if (GD(k,i) == 0) {
                        count++;
                    }
                }
                if (count == (r-1)) {
                    newPermuList.push_back(i); // then we know that this column i is a pivot column
                    break;
                }
            }
        }
    }

    for (int i=0; i < newPermuList.size(); i++) {
        swap(permuList[i],permuList[newPermuList[i]]);
    } // now the permuList contains the right permutation

    Mat<int> GDsorted = GD;
    for (int i=0; i < GDsorted.n_cols; i++) {
        GDsorted.col(i) = GD.col(permuList[i]);
    } // now the GDsorted matrix starts with a identity matrix

    Mat<int> HDsorted = GDsorted.submat(0,r,r-1,n-1);
    HDsorted = join_vert(HDsorted,eye<Mat<int>>(n-r,n-r));
    Mat<int> HD = HDsorted;

    for (int i=0; i < HD.n_rows; i++) {
        HD.row(i) = HDsorted.row(permuList[i]);
    } // now the GDsorted matrix starts with a identity matrix

    setGenMatrix(HD.t());
}

// this function uses Hamming encoding scheme to encode a given word
Row<int> HammingCode::HammingEncode(Row<int> the_word) {
    setWord(the_word);
    setHammingGenMatrix();
    return getWord()*getGenMatrix();
}

// this function uses Hamming decoding scheme to decode a given word
Row<int> HammingCode::HammingDecode(Row<int> the_receivedword) {
    Row<int> errorPatternRow0(n,fill::zeros);
    Mat<int> errorPattern = errorPatternRow0;
    errorPattern = join_vert(errorPattern,eye<Mat<int>>(n,n));
    Mat<int> H = getParityCheck();
    Row<int> syndromeRow0(r,fill::zeros);
    Mat<int> syndrome = join_vert(syndromeRow0,H);
    Mat<int> SDA = join_horiz(errorPattern,syndrome);
    Row<int> wH = modMatrix(the_receivedword*H,q);
    Row<int> correctedWord;
    for (int i=0; i<syndrome.n_rows; i++) {
        if (countElement(conv_to<Row<int>>::from(syndrome.row(i)==wH),1) == r) { // if two rows are the same, all entries are 1.
            correctedWord = modMatrix(the_receivedword+errorPattern.row(i),q);
            correctedWord.print("The corrected word:");
            break;
        }
    }
    // next step is to find the generator matrix. We have it in the encoding part
    Mat<int> rightInvG = rightInvMatrix(getGenMatrix());
    getGenMatrix().print("The genMatrix:");
    rightInvG.print("The rightInvG:");
    Mat<int> originalWord = modMatrix(correctedWord*rightInvG,q);

    return originalWord;
}
