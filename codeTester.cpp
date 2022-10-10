#include "codeTester.h"

int main() {

    cout << "This is an API for some error-correcting codes." << endl;
    string inputFile;
    cout << "The input file: ";
    cin >> inputFile;
    string outputFile;
    cout << "The output file: ";
    cin >> outputFile;

    #ifdef Hamming
        cout << "This is binary Hamming code test platform." << endl;
        HammingCode HC(7,4,3,2);
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
        cout << "This is binary Golay code test platform." << endl;
        GolayCode GC(23,12,7,2);
        // Row<int> B = {0,1,1,0};
        // int z = 0;
        // Row<int> C = shift(B, +z);
        // C.print();
        GC.setWord(stringToBinaryRow(readFileIntoString(inputFile)));
        Row<int> newWord = addZeroTail(GC.getWord(),GC.getK()); // so that the length of the row is divisible by k
        Row<int> encodedNewWord;
        for (int i=0; i<newWord.n_cols; i+=GC.getK()) {
            Row<int> encodedRow = GC.CyclicEncode(newWord.cols(i,i+GC.getK()-1));
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
        for (int i=0; i<receivedWord.n_cols; i+=GC.getN()) {
            Row<int> receivedRow = receivedWord.cols(i,i+GC.getN()-1);
            Row<int> decodedRow = GC.CyclicDecode(receivedRow);
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

    return 0;
}
