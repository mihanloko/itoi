//
// Created by mikhail on 18.05.2021.
//

#ifndef ITOI_LAB4_H
#define ITOI_LAB4_H

#include "../image/DoubleImage.h"
#include "../descriptors/HistogramProcessor.h"

class lab4 {
public:
    static void run();

    static void processPair(DoubleImage &a, DoubleImage &b, int gridHalfSize, int cellHalfSize, QString name, int basketSize);
};


#endif //ITOI_LAB4_H
