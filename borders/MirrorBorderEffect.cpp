//
// Created by mikhail on 11.04.2021.
//

#include "MirrorBorderEffect.h"

double MirrorBorderEffect::getOuterPixel(DoubleImage &image, int x, int y) {
    if (y < 0)
        y += image.getHeight();
    else if (y >= image.getHeight())
        y -= image.getHeight();
    if (x < 0)
        x += image.getWidth();
    else if (x >= image.getWidth())
        x -= image.getWidth();
    return image(x, y);
}

QString MirrorBorderEffect::toString() {
    return "Mirror";
}
