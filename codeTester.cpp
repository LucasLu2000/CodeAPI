#include "codeTester.h"

int main() {
    string inputFile = "input.txt";
    string outputFile = "output.txt";
    Row<int> row1 = stringToBinaryRow(readFileIntoString(inputFile));
    writeStringtoFile(binaryRowToString(row1),outputFile);
    Row<int> row2 = stringToBinaryRow(readFileIntoString(outputFile));
    row1.print("This is row1:");
    row2.print("This is row2:");
    // if (testText == binaryRowToText(textToBinaryRow(testText))) {
    //     cout << "They are the same!";
    // }
    return 0;
}
