//
// Created by mikhail on 11.04.2021.
//

#ifndef ITOI_BORDEREFFECTACTION_H
#define ITOI_BORDEREFFECTACTION_H


#include "../image/DoubleImage.h"

class BorderEffectAction {
protected:
    static bool isBorder(DoubleImage &image, int x, int y);
    virtual double getOuterPixel(DoubleImage &image, int x, int y) = 0;

public:
    double getPixel(DoubleImage &image, int x, int y);
    virtual QString toString() = 0;
};


#endif //ITOI_BORDEREFFECTACTION_H
