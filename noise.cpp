#include "noise.h"

Noise::Noise() : bitUnchangeRate(0) {

}

Noise::Noise(double the_bitUnchangeRate, int the_seed) : bitUnchangeRate(the_bitUnchangeRate), sd(the_seed) {

}

double Noise::getRate() const {
    return bitUnchangeRate;
}

void Noise::setRate(double the_bitUnchangeRate) {
    bitUnchangeRate = the_bitUnchangeRate;
}

int Noise::getSeed() {
    return sd;
}

void Noise::setSeed(int the_seed) {
    sd = the_seed;
}

Row<int> Noise::noiseGenerator(Row<int>encodedWord) { // only works in binary
    Row<int> the_receivedWord = encodedWord;
    int FLOAT_MIN = 0;
    int FLOAT_MAX = 1;
    srand(sd);
    double randNum;
    for (int i=0; i<encodedWord.n_cols; i++) {
        randNum = FLOAT_MIN + (double)(rand()) / ((double)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
        cout << "Here is the rand: " << randNum << endl;
        if (randNum > bitUnchangeRate) {
            if (the_receivedWord(i)) {
                the_receivedWord(i) = 0;
            }
            the_receivedWord(i) = 1;
        }
    }
    return the_receivedWord;
}
