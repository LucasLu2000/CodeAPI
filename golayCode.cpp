#include "codeBasic.h"
#include "golayCode.h"

GolayCode::GolayCode() : CyclicCode() {
    checkGolay();
    setGenerator(golayGenerator);
}

GolayCode::GolayCode(int the_n, int the_k, int the_d, int the_q) : CyclicCode(the_n, the_k, the_d, the_q) {
    checkGolay();
    setGenerator(golayGenerator);
}

void GolayCode::checkGolay() {
    while ((n != 23) || (k != 12) || (d != 7) || (q != 2)) { // we want to check if it is really a binary Golay code
        cout << "The parameters of the code given are not able to construct a binary Golay code. Please enter n, k, d, and q again." << endl;
        cout << "n: ";
        cin >> n;
        cout << "k: ";
        cin >> k;
        cout << "d: ";
        cin >> d;
        cout << "q: ";
        cin >> q;
    }
}
