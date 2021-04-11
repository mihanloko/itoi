//
// Created by mikhail on 11.04.2021.
//

#ifndef ITOI_MIRRORBORDEREFFECT_H
#define ITOI_MIRRORBORDEREFFECT_H


#include "BorderEffectAction.h"

class MirrorBorderEffect : public BorderEffectAction {
protected:
    double getOuterPixel(DoubleImage &image, int x, int y) override;

public:
    QString toString() override;
};


#endif //ITOI_MIRRORBORDEREFFECT_H
