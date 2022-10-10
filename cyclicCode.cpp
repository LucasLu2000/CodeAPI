#include "cyclicCode.h"
#include <cmath>

CyclicCode::CyclicCode() : Code() {

}

CyclicCode::CyclicCode(int the_n, int the_k, int the_d, int the_q) : Code(the_n, the_k, the_d, the_q) {
}

void CyclicCode::setGenerator(const Row<int> the_gen) {
    generator = the_gen;
}

Row<int> CyclicCode::getGenerator(){
    return generator;
}

void CyclicCode::setCyclicGenMatrix() {
    Mat<int> GM(k,n,fill::zeros);
    Row<int> temGen = generator;
    for (int i=0; i < k; i++) { //row
        GM.row(i) = shift(temGen, +i);
    }
    setGenMatrix(GM);
}

Row<int> CyclicCode::CyclicEncode(const Row<int> the_word) {
    Row<int> encodedWord = modMatrix(conv(the_word, generator)); // conv may not preserve length
    int numOfZeros = n - encodedWord.n_cols;
    if (numOfZeros >= 0) {
        Row<int> zeroTail(numOfZeros, fill::zeros);
        encodedWord = join_horiz(encodedWord,zeroTail);
    }
    else {
        encodedWord.shed_cols(n,encodedWord.n_cols-1);
    }
    return encodedWord;
}

// First add zeros so that two polynomials are with same length
Row<int> CyclicCode::minusPolynomial(const Row<int> p1, const Row<int> p2, const int length) {
    Row<int> newp1 = p1;
    Row<int> newp2 = p2;
    int numOfZerosp1 = length - p1.n_cols;
    int numOfZerosp2 = length - p1.n_cols;
    if (numOfZerosp1 != 0 && numOfZerosp2 != 0) {
        Row<int> zeroTailp1(numOfZerosp1, fill::zeros);
        Row<int> zeroTailp2(numOfZerosp2, fill::zeros);
        newp1 = join_horiz(p1,zeroTailp1);
        newp2 = join_horiz(p2,zeroTailp2);
    }
    return nonNegativeMatrix(newp1 - newp2);
}

int CyclicCode::degreePolynomial(const Row<int> poly) {
    int degree;
    for (int i=poly.n_cols-1; i>=0; i--) {
        if (poly(i) != 0) {
            degree = i;
            break;
        }
    }
    return degree;
}

Row<int> CyclicCode::modPolynomial(const Row<int> p1, const Row<int> p2, const int length) {
    Row<int> remainder = p1;
    int numOfZeros = length - remainder.n_cols;
    if (numOfZeros != 0) {
        Row<int> zeroTail(numOfZeros, fill::zeros);
        remainder = join_horiz(remainder,zeroTail);
    }
    int degRem = degreePolynomial(remainder);
    int degp2 = degreePolynomial(p2);
    while (degRem >= 0 && degRem >= degp2) {
        Row<int> oneTerm(length, fill::zeros);
        oneTerm(degRem-degp2) = 1;
        Row<int> p2Term = modMatrix(conv(p2, oneTerm));
        int numOfZerosp2 = n - p2Term.n_cols;
        if (numOfZerosp2 >= 0) {
            Row<int> zeroTailp2(numOfZerosp2, fill::zeros);
            p2Term = join_horiz(p2Term,zeroTailp2);
        }
        else {
            p2Term.shed_cols(length,p2Term.n_cols-1);
        }
        remainder = minusPolynomial(remainder,p2Term,length);
        degRem = degreePolynomial(remainder);
    }
    return remainder;
}

// Coding Theory The Essentials P112
Row<int> CyclicCode::CyclicDecode(const Row<int> the_receivedWord){
    Row<int> correctedWord;
    int t = floor((d-1)/2);
    Row<int> synPoly = modPolynomial(the_receivedWord,generator,n);
    while (countElement(synPoly,1) >= t) {
        synPoly = modPolynomial(synPoly,generator,n);
    }
    setCyclicGenMatrix();
    Mat<int> rightInvG = rightInvMatrix(getGenMatrix());
    Mat<int> originalWord = modMatrix(correctedWord*rightInvG);
    return originalWord;
}
