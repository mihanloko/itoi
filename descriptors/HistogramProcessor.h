//
// Created by mikhail on 25.05.2021.
//

#ifndef ITOI_HISTOGRAMPROCESSOR_H
#define ITOI_HISTOGRAMPROCESSOR_H


#include "../image/DoubleImage.h"
#include <cmath>
#include "MatchData.h"
#include "DescriptorUtil.h"
#include "HistogramDescriptor.h"
#include "../points/Harris.h"

class HistogramProcessor {
private:
    DoubleImage &firstImage;
    DoubleImage &secondImage;
    int gridSize;
    int cellSize;
    int basketSize;

    vector<Descriptor> createDescriptors(DoubleImage &img);

    vector<Descriptor> createDescriptors(DoubleImage &gradient, DoubleImage &gradientAngle, vector<InterestingPoint> &points);

    vector<vector<vector<double>>> calculateHistograms(DoubleImage& gradient, DoubleImage& dx, DoubleImage& dy, DoubleImage& gauss,
                                                      int gridSize, int blockSize, int binsCount,
                                                       InterestingPoint& center, double angle);

public:
    DoubleImage &getFirstImage();

    DoubleImage &getSecondImage();

public:
    HistogramProcessor(DoubleImage &firstImage, DoubleImage &second, int gridSize, int cellSize, int basketSize);

    static MatchData create(DoubleImage &first, DoubleImage &second, int gridSize, int cellSize, int basketSize);

};


#endif //ITOI_HISTOGRAMPROCESSOR_H
