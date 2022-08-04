#include "codeTester.h"

int main() {

    #ifdef Hamming
        HammingCode HC(7,4,3,2,3);
        cout << "This is Hamming code test platform." << endl;
        string inputFile;
        cout << "The input file: ";
        cin >> inputFile;
        string outputFile;
        cout << "The output file: ";
        cin >> outputFile;
        HC.setWord(stringToBinaryRow(readFileIntoString(inputFile)));
        HC.getWord().print("The word:");
        Row<int> newWord = addZeroTail(HC.getWord(),HC.getK()); // so that the length of the row is divisible by k
        Row<int> encodedNewWord;
        for (int i=0; i<newWord.n_cols; i+=HC.getK()) {
            Row<int> encodedRow = HC.HammingEncode(newWord.cols(i,i+HC.getK()-1));
            encodedRow.print("The encoded word:");
            if (i==0) {
                encodedNewWord = encodedRow;
            }
            else {
                encodedNewWord = join_horiz(encodedNewWord,encodedRow);
            }
        }
        Noise N1(1);
        Row<int> receivedWord = N1.noiseGenerator(encodedNewWord);
        Row<int> decodedNewWord;
        for (int i=0; i<receivedWord.n_cols; i+=HC.getN()) {
            Row<int> decodedRow = HC.HammingDecode(receivedWord.cols(i,i+HC.getN()-1));
            decodedRow.print("The decoded word:");
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
