//
// Created by mikhail on 11.04.2021.
//

#include "BorderEffectAction.h"

bool BorderEffectAction::isBorder(DoubleImage &image, int x, int y) {
    return x < 0 || y < 0 || x >= image.getWidth() || y >= image.getHeight();
}

double BorderEffectAction::getPixel(DoubleImage &image, int x, int y) {
    if (!isBorder(image, x, y))
        return image(x, y);
    return getOuterPixel(image, x, y);
}
