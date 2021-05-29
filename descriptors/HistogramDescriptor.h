//
// Created by mikhail on 25.05.2021.
//

#ifndef ITOI_HISTOGRAMDESCRIPTOR_H
#define ITOI_HISTOGRAMDESCRIPTOR_H


#include "Descriptor.h"
#include "Basket.h"
#include "../filters/KernelFactory.h"
#include "../filters/FiltersImplementation.h"
#include "../borders/MirrorBorderEffect.h"

class HistogramDescriptor : public Descriptor {
public:
    HistogramDescriptor(DoubleImage &gradient, DoubleImage &gradientAngle,
                        InterestingPoint point, int gridSize, int cellSize, int basketSize, bool needNormalize = true);
};


#endif //ITOI_HISTOGRAMDESCRIPTOR_H
