#include "noise.h"

Noise::Noise() : bitChangeRate(0) {

}

Noise::Noise(double the_bitChangeRate) : bitChangeRate(the_bitChangeRate) {

}

double Noise::getRate() const {
    return bitChangeRate;
}

void Noise::setRate(double the_bitChangeRate) {
    bitChangeRate = the_bitChangeRate;
}

void Noise::noiseGenerator() { // Row<int>encodedWord
    int FLOAT_MIN = 0;
    int FLOAT_MAX = 1;
    srand(1);
    cout << setprecision(6) << FLOAT_MIN + (double)(rand()) / ((double)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN))) << endl;
}
