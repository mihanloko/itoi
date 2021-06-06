//
// Created by mikhail on 06.06.2021.
//

#ifndef ITOI_ROTATIONINVARIANTPROCESSOR_H
#define ITOI_ROTATIONINVARIANTPROCESSOR_H

#include "../image/DoubleImage.h"
#include <cmath>
#include "MatchData.h"
#include "DescriptorUtil.h"
#include "HistogramDescriptor.h"
#include "../points/Harris.h"


class RotationInvariantProcessor {
private:
    DoubleImage &firstImage;
    DoubleImage &secondImage;
    int gridSize;
    int cellSize;
    int basketSize;

    vector<Descriptor> createDescriptors(DoubleImage &img);

    vector<vector<vector<double>>> calculateHistograms(DoubleImage& gradient, DoubleImage& dx, DoubleImage& dy, DoubleImage& gauss,
                                                       int gridSize, int blockSize, int binsCount,
                                                       InterestingPoint& center, double angle);

    int findMaximum(vector<double> &array, int exclude);

    vector<double> toVector(vector<vector<vector<double>>>& bins, int gridSize, int binsCount);


public:
    DoubleImage &getFirstImage();

    DoubleImage &getSecondImage();

    RotationInvariantProcessor(DoubleImage &firstImage, DoubleImage &second, int gridSize, int cellSize, int basketSize);

    static MatchData create(DoubleImage &first, DoubleImage &second, int gridSize, int cellSize, int basketSize);

};



#endif //ITOI_ROTATIONINVARIANTPROCESSOR_H
