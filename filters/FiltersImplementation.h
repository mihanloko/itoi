//
// Created by mikhail on 11.04.2021.
//

#ifndef ITOI_FILTERSIMPLEMENTATION_H
#define ITOI_FILTERSIMPLEMENTATION_H

#include <ostream>
#include <iomanip>
#include <iostream>

#include "../image/DoubleImage.h"
#include "../borders/CopyBorderEffect.h"
#include "KernelFactory.h"

class FiltersImplementation {
public:
    constexpr static CopyBorderEffect DEFAULT_ACTION = CopyBorderEffect();

    static void print(ostream &out, DoubleImage &matrix);

    static DoubleImage applyCrossCorel(DoubleImage &image, DoubleImage &kernel, BorderEffectAction &borderPolicy);

    static DoubleImage applyConvolution(DoubleImage &image, DoubleImage &kernel,
                                        BorderEffectAction &borderPolicy = (BorderEffectAction &) DEFAULT_ACTION);

    static DoubleImage derivativeX(DoubleImage &image,
                                   BorderEffectAction &borderPolicy = (BorderEffectAction &) DEFAULT_ACTION);

    static DoubleImage derivativeY(DoubleImage &image,
                                   BorderEffectAction &borderPolicy = (BorderEffectAction &) DEFAULT_ACTION);


    static DoubleImage applyGauss(DoubleImage &image, double sigma,
                                  BorderEffectAction &policy = (BorderEffectAction &) DEFAULT_ACTION, bool normalize = false);

    static DoubleImage applySeparable(DoubleImage &image, pair<DoubleImage,DoubleImage>,
                                      BorderEffectAction &policy = (BorderEffectAction &) DEFAULT_ACTION);

    static DoubleImage applyGaussSeparable(DoubleImage &image, double sigma,
                                           BorderEffectAction &policy = (BorderEffectAction &) DEFAULT_ACTION, bool normalize = false);

    static double getSeparableValue(pair<DoubleImage, DoubleImage> &pair, int x, int y);
};


#endif //ITOI_FILTERSIMPLEMENTATION_H
