//
// Created by mikhail on 27.04.2021.
//

#ifndef ITOI_HARRIS_H
#define ITOI_HARRIS_H

#include <vector>
#include <cmath>
#include "../image/DoubleImage.h"
#include "InterestingPoint.h"
#include "../filters/FiltersImplementation.h"
#include "InterestingPoint.h"
#include "DetectorUtil.h"
#include "../filters/KernelFactory.h"

using namespace std;

class Harris {
private:
    static constexpr CopyBorderEffect DEFAULT_BORDER = CopyBorderEffect();
    vector<double> getEigenValues(vector<vector<double>> &mat);
    double sqr(double value);
    double MIN_PROBABILITY = 0.01;
    const int WINDOW_RADIUS = 3;
    double calcLambdaMin(double A, double B, double C);
    bool hasLargerNeighbour(DoubleImage& image, int x, int y);
public:
    vector<InterestingPoint> makeHarris(DoubleImage &image, BorderEffectAction &action = (BorderEffectAction &) DEFAULT_BORDER);
};


#endif //ITOI_HARRIS_H
