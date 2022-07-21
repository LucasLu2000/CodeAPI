#include "codeTester.h"

int main() {
    string inFile = "in.txt";
    ifstream f;
    f.open(inFile, ios::binary);
    char c;
    while (f.get(c)) {
        string binaryStr = "";
        for (int i = 7; i >= 0; i--) {
            cout << ((c >> i) & 1);
            binaryStr += to_string((c >> i) & 1);
        } // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
        cout << BinaryStringToText(binaryStr);
        cout << endl;
    }
    cout << readFileIntoString(inFile);
    f.close();
    return 0;
}
