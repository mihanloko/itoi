//
// Created by mikhail on 01.05.2021.
//

#ifndef ITOI_DETECTORUTIL_H
#define ITOI_DETECTORUTIL_H

#include <vector>
#include <map>
#include <algorithm>
#include "InterestingPoint.h"
#include "../image/DoubleImage.h"

using namespace std;

class DetectorUtil {

public:
    static vector<InterestingPoint> getCandidates(vector<vector<double>> values, int width, int height);

    static vector<InterestingPoint> filter(vector<InterestingPoint> &points, int maxSize, int maxRadius);

    static vector<InterestingPoint> matToPoints(DoubleImage& mat);
};


#endif //ITOI_DETECTORUTIL_H
