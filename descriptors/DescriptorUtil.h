//
// Created by mikhail on 17.05.2021.
//

#ifndef ITOI_DESCRIPTORUTIL_H
#define ITOI_DESCRIPTORUTIL_H


#include <QPainter>
#include <cmath>
#include "../filters/FiltersImplementation.h"
#include "../image/DoubleImage.h"
#include "MatchData.h"
#include "../points/DataSaver.h"

class DescriptorUtil {
public:
    static DoubleImage getGradient(DoubleImage &image, bool normalize = true);

    static MatchData match(vector<Descriptor> &firstList, vector<Descriptor> &secondList);

    static Descriptor* getClosest(Descriptor &descriptor, vector<Descriptor> &descriptors);

    static int getMinIndex(vector<double> distances, int excludeIndex);

    static QImage markMatching(DoubleImage &a, DoubleImage &b, MatchData& data);

    static DoubleImage getGradient(DoubleImage &first, DoubleImage &second, double (*counterFunc)(double, double));

    static DoubleImage getGradient(DoubleImage &first, DoubleImage &second);

    static DoubleImage getGradientAngle(DoubleImage &first, DoubleImage &second);
};


#endif //ITOI_DESCRIPTORUTIL_H
