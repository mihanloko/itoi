//
// Created by mikhail on 25.05.2021.
//

#include "HistogramDescriptor.h"

HistogramDescriptor::HistogramDescriptor(DoubleImage &gradient, DoubleImage &gradientAngle, InterestingPoint point,
                                         int gridSize, int cellSize, int basketSize, bool needNormalize) : Descriptor(point)  {
    this->point = point;
    this->descriptor.reserve(gridSize * gridSize * basketSize);

    vector<vector<Basket>> baskets(gridSize, vector(gridSize, Basket(basketSize)));
    int border = gridSize * cellSize;
    int halfBorder = border / 2;

    auto gauss = KernelFactory::GetGaussSeparableXY(halfBorder);
    int left = -halfBorder, right = border - halfBorder;
    MirrorBorderEffect effect;

    for (int x = left; x < right; x++) {
        for (int y = left; y < right; y++) {
            int realX = (point.getX() + x);
            int realY = (point.getY() + y);
            double phi = effect.getPixel(gradientAngle, realX, realY);
            double gradientValue = effect.getPixel(gradient, realX, realY);
            double gaussValue = FiltersImplementation::getSeparableValue(gauss, halfBorder + x, halfBorder + y);

            int i = (x - left) / cellSize;
            int j = (y - left) / cellSize;
            baskets[i][j].add(phi, gradientValue * gaussValue);
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            auto basket = baskets[i][j].getBasket();
            this->descriptor.insert(this->descriptor.end(), basket.begin(), basket.end());
        }
    }
    if (needNormalize)
        normalize();

}
