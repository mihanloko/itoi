//
// Created by mikhail on 06.06.2021.
//

#ifndef ITOI_LAB5_H
#define ITOI_LAB5_H

#include "../image/DoubleImage.h"
#include "../descriptors/HistogramProcessor.h"
#include "../descriptors/RotationInvariantProcessor.h"

class lab5 {
public:
    static void run();

    static void processPair(DoubleImage &a, DoubleImage &b, int gridHalfSize, int cellHalfSize, QString name, int basketSize);
};


#endif //ITOI_LAB5_H
