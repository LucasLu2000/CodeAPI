#ifndef NOISE_H
#define NOISE_H
#include "codeBasic.h"
#include <iomanip>

// binary symmetric channel
class Noise {
    public:
        Noise();
        Noise(double the_bitUnchangeRate, int the_seed = time(NULL));
        double getRate() const;
        void setRate(double the_bitUnchangeRate);
        int getSeed();
        void setSeed(int the_seed);
        Row<int> noiseGenerator(Row<int> encodedWord);

    private:
        double bitUnchangeRate;
        int sd;
};

#endif
