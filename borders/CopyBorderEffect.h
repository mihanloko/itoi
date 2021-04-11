//
// Created by mikhail on 11.04.2021.
//

#ifndef ITOI_COPYBORDEREFFECT_H
#define ITOI_COPYBORDEREFFECT_H


#include "BorderEffectAction.h"

class CopyBorderEffect : public BorderEffectAction {
protected:
    double getOuterPixel(DoubleImage &image, int x, int y) override;

public:
    QString toString() override;
};


#endif //ITOI_COPYBORDEREFFECT_H
