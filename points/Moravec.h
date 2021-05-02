//
// Created by mikhail on 27.04.2021.
//

#ifndef ITOI_MORAVEC_H
#define ITOI_MORAVEC_H

#include <vector>
#include <cmath>
#include <algorithm>
#include "../image/DoubleImage.h"
#include "InterestingPoint.h"
#include "../borders/BorderEffectAction.h"
#include "../borders/CopyBorderEffect.h"
#include "../filters/FiltersImplementation.h"
#include "DetectorUtil.h"
#include "DataSaver.h"

using namespace std;

class Moravec {
private:
    static constexpr CopyBorderEffect DEFAULT_BORDER = CopyBorderEffect();
    double MIN_PROBABILITY = 0.05;
    int MAX_SIZE = 2000;
    const vector<int> dx{-1, 0, 1, -1, 1, -1, 0, -1};
    const vector<int> dy{-1, -1, -1, 0, 0, 1, 1, 1};
    const int WINDOW_RADIUS = 2;

private:

    double sqr(double value);
    vector<vector<double>> getMinimums(DoubleImage &image, BorderEffectAction &action =  (BorderEffectAction &) DEFAULT_BORDER);

public:

    vector<InterestingPoint> makeMoravec(DoubleImage &image);
};


#endif //ITOI_MORAVEC_H
