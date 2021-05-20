//
// Created by mikhail on 17.05.2021.
//

#include "PatchDescriptor.h"
#include "../borders/MirrorBorderEffect.h"

PatchDescriptor::PatchDescriptor(DoubleImage &gradient, InterestingPoint point,
                                 int gridHalfSize, int cellHalfSize) : Descriptor(point) {
    int cellSize = cellHalfSize * 2 + 1;

    MirrorBorderEffect effect;
    for (int cellX = -gridHalfSize; cellX <= gridHalfSize; cellX++) {
        for (int cellY = -gridHalfSize; cellY <= gridHalfSize; cellY++) {
            double sum = 0;
            for (int pixelX = -cellHalfSize; pixelX <= cellHalfSize; pixelX++) {
                for (int pixelY = -cellHalfSize; pixelY <= cellHalfSize; pixelY++) {
                    int realX = point.getX() + cellX * cellSize + pixelX;
                    int realY = point.getY() + cellY * cellSize + pixelY;
                    sum += effect.getPixel(gradient, realX, realY);
                }
            }
            sum /= cellSize * cellSize;
            descriptor.push_back(sum);
        }
    }
    normalize();
}
