//
// Created by mikhail on 18.04.2021.
//

#ifndef ITOI_OCTAVEFACTORY_H
#define ITOI_OCTAVEFACTORY_H

#include <cmath>
#include <iostream>
#include "../image/DoubleImage.h"
#include "Octave.h"

using namespace std;

class OctaveFactory {
public:
    static vector<Octave> generateOctaves(int octavesCount, int nLevels, double sigma0, const DoubleImage &inputImage, double sigmaA = 0.5);

    static Octave generateOneOctave(int nLevels, double sigma0, const DoubleImage& startImage, double k, double globalSigma);

    static double calculateDeltaSigma(double oldSigma, double newSigma);

    static DoubleImage L(DoubleImage &inputImage, vector<Octave> pyramid, double sigma);

    static DoubleImage getHalfSizeImage(DoubleImage &image);
};


#endif //ITOI_OCTAVEFACTORY_H
