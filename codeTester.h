#ifndef CODETESTER_H
#define CODETESTER_H
#include <bitset>
#include <math.h>
#include <string.h>
#include "codeBasic.h"
#include "noise.h"
#include "hammingCode.h"
#include "golayCode.h"

Row<int> textToBinaryRow(const string &text) {
    Row<int> binaryRow;
    vector<int> binaryVector;
    for (int c=0; c<text.length(); c++) {
        for (int i = 7; i >= 0; i--) {
            binaryVector.push_back((text[c] >> i) & 1);
            // binaryStr += to_string((text[c] / (int)pow(2,i)) % 2); //or the same as this, need #include <math.h>
        }
    }
    binaryRow = binaryVector;
    return binaryRow;
}

char strToChar(const string &str) { // only one byte or 8 bits can be seen as one charactor
    char parsed = 0;
    for (int i = 0; i < 8; i++) {
        if (str[i] == '1') {
            parsed |= 1 << (7 - i);
        }
    }
    return parsed;
}

string binaryRowToText(const Row<int> &binaryRow) {
    string text = "";
    string binaryText = "";
    for (int i=0; i<binaryRow.n_cols; i++) {
    binaryText += to_string(binaryRow(i));
    }
    for (int i=0; i<binaryText.length(); i+=8) {
        text += strToChar(binaryText.substr(i,i+7));
    }
    return text;
}

// This function does not work
// string binaryRowToText(Row<int> binaryRow) {
//     string text = "";
//     string binaryText = "";
//     for (int i=0; i<binaryRow.n_cols; i++) {
//         binaryText += to_string(binaryRow(i));
//     }
//     stringstream sstream(binaryText);
//     while (sstream.good())
//     {
//         bitset<8> bits;
//         sstream >> bits;
//         text += char(bits.to_ulong());
//     }
//     return text;
// }

// this function read a file name (string type) and then return a the file content as a string
string readFileIntoString(const string& path) {
    ifstream f;
    string textString="";
    string line;
    f.open(path);
    while (!f.eof()) {
        getline(f, line);
        textString += line;
    }
    f.close();
    return textString;
}

#endif
