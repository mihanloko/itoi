//
// Created by mikhail on 25.05.2021.
//

#include "HistogramCreator.h"

vector<Descriptor> HistogramCreator::createDescriptors(DoubleImage &img) {
    auto x = FiltersImplementation::derivativeX(img);
    auto y = FiltersImplementation::derivativeY(img);

    auto gradient = DescriptorUtil::getGradient(x, y);
    auto gradientAngle = DescriptorUtil::getGradientAngle(x, y);

    Harris harris;
    auto points = harris.makeHarris(img);

    return createDescriptors(gradient, gradientAngle, points);
}

vector<Descriptor> HistogramCreator::createDescriptors(DoubleImage &gradient, DoubleImage &gradientAngle,
                                                       vector<InterestingPoint> &points) {
    vector<Descriptor> descriptors;
    descriptors.reserve(points.size());
    for (const auto &item : points)
        descriptors.push_back(HistogramDescriptor(gradient, gradientAngle, item, gridSize, cellSize, basketSize));
    return descriptors;
}

DoubleImage &HistogramCreator::getFirstImage() {
    return firstImage;
}

DoubleImage &HistogramCreator::getSecondImage() {
    return secondImage;
}

HistogramCreator::HistogramCreator(DoubleImage &firstImage, DoubleImage &second, int gridSize, int cellSize,
                                   int basketSize, int pointsCount)
        : firstImage(firstImage), secondImage(second), gridSize(gridSize), cellSize(cellSize),
          basketSize(basketSize), pointsCount(pointsCount) {

}

MatchData HistogramCreator::create(DoubleImage &first, DoubleImage &second, int _gridSize, int _cellSize, int _basketSize,
                         int _pointsCount, bool showAll) {
    auto creator = HistogramCreator(first, second, _gridSize, _cellSize, _basketSize, _pointsCount);
    auto firstDescriptor = creator.createDescriptors(creator.getFirstImage());

    auto secondDescriptor = creator.createDescriptors(creator.getSecondImage());

    return DescriptorUtil::match(firstDescriptor, secondDescriptor);
}
