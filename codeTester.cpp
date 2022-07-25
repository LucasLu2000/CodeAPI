#include "codeTester.h"

int main() {
    string inFile = "in.txt";
    // ifstream f;
    // f.open(inFile, ios::binary);
    string testText = "Hello!";
    textToBinaryRow(testText).print();
    string str = binaryRowToText(textToBinaryRow(testText));
    cout << testText.length();
    cout << endl;
    cout << str.length();
    cout << endl;
    if (testText == binaryRowToText(textToBinaryRow(testText))) {
        cout << "They are the same!";
    }
    cout << endl;
    cout << readFileIntoString(inFile) << endl;
    textToBinaryRow(readFileIntoString(inFile)).print();
    return 0;
}
