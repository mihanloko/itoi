//
// Created by mikhail on 25.05.2021.
//

#ifndef ITOI_HISTOGRAMCREATOR_H
#define ITOI_HISTOGRAMCREATOR_H


#include "../image/DoubleImage.h"
#include "MatchData.h"
#include "DescriptorUtil.h"
#include "HistogramDescriptor.h"
#include "../points/Harris.h"

class HistogramCreator {
private:
    DoubleImage &firstImage;
    DoubleImage &secondImage;
    int gridSize;
    int cellSize;
    int basketSize;
    int pointsCount;

    vector<Descriptor> createDescriptors(DoubleImage &img);

    vector<Descriptor> createDescriptors(DoubleImage &gradient, DoubleImage &gradientAngle, vector<InterestingPoint> &points);

public:
    DoubleImage &getFirstImage();

    DoubleImage &getSecondImage();

public:
    HistogramCreator(DoubleImage &firstImage, DoubleImage &second, int gridSize, int cellSize, int basketSize,
                     int pointsCount);

    static MatchData create(DoubleImage &first, DoubleImage &second, int _gridSize, int _cellSize, int _basketSize,
                            int _pointsCount, bool showAll = false);

};


#endif //ITOI_HISTOGRAMCREATOR_H
