#ifndef NOISE_H
#define NOISE_H
#include "codeBasic.h"
#include <iomanip>

// binary symmetric channel
class Noise {
    public:
        Noise();
        Noise(double the_bitChangeRate);
        double getRate() const;
        void setRate(double the_bitChangeRate);
        void noiseGenerator(int the_seed); //Row<int>encodedWord

    private:
        double bitChangeRate;

};

#endif
