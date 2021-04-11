//
// Created by mikhail on 11.04.2021.
//

#include "CopyBorderEffect.h"

double CopyBorderEffect::getOuterPixel(DoubleImage &image, int x, int y) {
    int resX = (x < 0) ? 0 : (image.getWidth() - 1);
    int resY = (y < 0) ? 0 : (image.getHeight() - 1);
    return image(resX, resY);
}

QString CopyBorderEffect::toString() {
    return "Copy";
}
