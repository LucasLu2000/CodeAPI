#include "codeTester.h"

int main() {
    string inFile = "in.txt";
    // ifstream f;
    // f.open(inFile, ios::binary);
    string testText = "Hello!";
    cout << TextToBinaryString(testText);
    cout << readFileIntoString(inFile);
    // f.close();
    return 0;
}
