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
        Row<int> newWord = addZeroTail(HC.getWord(),HC.getK());
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
            encodedRow.print("The decoded word:");
        }
        writeStringtoFile(binaryRowToString(deleteZeroTail(encodedNewWord)),outputFile);
        if (compareTwoFiles(inputFile,outputFile)) {
            cout << "Yes! They are the same." << endl;
        }
    #endif

    #ifdef Golay
        cout << "Golay code module is under construction." << endl;
    #endif

    return 0;
}
