//
// Created by mikhail on 18.04.2021.
//

#ifndef ITOI_LAB2_H
#define ITOI_LAB2_H


#include <QString>
#include <iostream>
#include "../octaves/Octave.h"

using namespace std;

class lab2 {
private:
    int nOctaves, nLevels;
    double sigma0, sigmaA, sigmaL;
    const QString &imageName, &ext;
public:
    lab2(int nOctaves, int nLevels, double sigma0, double sigmaA, double sigmaL, const QString &imageName,
         const QString &ext) : nOctaves(nOctaves), nLevels(nLevels), sigma0(sigma0), sigmaA(sigmaA), sigmaL(sigmaL),
                               imageName(imageName), ext(ext) {};

    static void run();

    void process();

    void saveCompoundImage(const vector<Octave> &octaves);
};


#endif //ITOI_LAB2_H
