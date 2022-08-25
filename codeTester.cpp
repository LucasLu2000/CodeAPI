#include "codeTester.h"

int main() {

    cout << "This is an API for some error-correcting codes." << endl;

    #ifdef Hamming
        cout << "This is Hamming code test platform." << endl;
        HammingCode HC(6,4,3,2);
        string inputFile;
        cout << "The input file: ";
        cin >> inputFile;
        string outputFile;
        cout << "The output file: ";
        cin >> outputFile;
        HC.setWord(stringToBinaryRow(readFileIntoString(inputFile)));
        Row<int> newWord = addZeroTail(HC.getWord(),HC.getK()); // so that the length of the row is divisible by k
        Row<int> encodedNewWord;
        for (int i=0; i<newWord.n_cols; i+=HC.getK()) {
            Row<int> encodedRow = HC.HammingEncode(newWord.cols(i,i+HC.getK()-1));
            if (i==0) {
                encodedNewWord = encodedRow;
            }
            else {
                encodedNewWord = join_horiz(encodedNewWord,encodedRow);
            }
        }
        double stableRate;
        cout << "Please enter p, the probability that each digit received is the same as the digit sent: ";
        cin >> stableRate;
        Noise N1(stableRate);
        Row<int> receivedWord = N1.noiseGenerator(encodedNewWord);
        Row<int> decodedNewWord;
        for (int i=0; i<receivedWord.n_cols; i+=HC.getN()) {
            Row<int> receivedRow = receivedWord.cols(i,i+HC.getN()-1);
            Row<int> decodedRow = HC.HammingDecode(receivedRow);
            if (i==0) {
                decodedNewWord = decodedRow;
            }
            else {
                decodedNewWord = join_horiz(decodedNewWord,decodedRow);
            }
        }
        writeStringtoFile(binaryRowToString(deleteZeroTail(decodedNewWord)),outputFile);
        if (compareTwoFiles(inputFile,outputFile)) {
            cout << "Yes! They are the same." << endl;
        }
    #endif

    #ifdef Golay
        cout << "Golay code module is under construction." << endl;
    #endif

    return 0;
}
