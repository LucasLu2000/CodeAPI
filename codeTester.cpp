#include "codeTester.h"

int main() {
    string inputFile = "input.txt";
    string outputFile = "output.txt";
    Row<int> row1 = stringToBinaryRow(readFileIntoString(inputFile));
    writeStringtoFile(binaryRowToString(row1),outputFile);
    Row<int> row2 = stringToBinaryRow(readFileIntoString(outputFile));
    row1.print("This is row1:");
    row2.print("This is row2:");

    #ifdef Hamming
        HammingCode HC(7,4,3,2,3);
        cout << HC.getN() << endl;
        cout << HC.getK() << endl;
        cout << "md5 of 'grape': " << md5("grape") << endl;
        if (md5(readFileIntoString(inputFile)) == md5(readFileIntoString(outputFile)+"/n")) {
            cout << "They are the same!" << endl;
        }
        Mat<int> mx = {{1,0,0},{0,1,0},{0,0,1}};
        Mat<int> mxC = mx.col(1);
        mx.print("mx:");
        mxC.print("The second column of mx:");
        mx.insert_cols(1,mxC);
        mx.print("The new mx:");
        HC.HammingEncode({1,0,0,0}).print("encoded:");
        HC.HammingDecode({1,1,1,0,0,0,1}).print("decoded:");
    #endif

    #ifdef Golay
        cout << "Hello!" << endl;
    #endif

    return 0;
}
