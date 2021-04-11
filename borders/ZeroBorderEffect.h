//
// Created by mikhail on 11.04.2021.
//

#ifndef ITOI_ZEROBORDEREFFECT_H
#define ITOI_ZEROBORDEREFFECT_H


#include "BorderEffectAction.h"

class ZeroBorderEffect : public BorderEffectAction {
protected:
    double getOuterPixel(DoubleImage &image, int x, int y) override;

public:
    QString toString() override;
};


#endif //ITOI_ZEROBORDEREFFECT_H
