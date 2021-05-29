//
// Created by mikhail on 25.05.2021.
//

#include "HistogramProcessor.h"

vector<Descriptor> HistogramProcessor::createDescriptors(DoubleImage &img) {
    auto x = FiltersImplementation::derivativeX(img);
    auto y = FiltersImplementation::derivativeY(img);

    auto gradient = DescriptorUtil::getGradient(x, y);
    auto gradientAngle = DescriptorUtil::getGradientAngle(x, y);

    Harris harris;
    auto points = harris.makeHarris(img);

    return createDescriptors(gradient, gradientAngle, points);
}

vector<Descriptor> HistogramProcessor::createDescriptors(DoubleImage &gradient, DoubleImage &gradientAngle,
                                                       vector<InterestingPoint> &points) {
    vector<Descriptor> descriptors;
    descriptors.reserve(points.size());
    for (const auto &item : points)
        descriptors.push_back(HistogramDescriptor(gradient, gradientAngle, item, gridSize, cellSize, basketSize));
    return descriptors;
}

DoubleImage &HistogramProcessor::getFirstImage() {
    return firstImage;
}

DoubleImage &HistogramProcessor::getSecondImage() {
    return secondImage;
}

HistogramProcessor::HistogramProcessor(DoubleImage &firstImage, DoubleImage &second, int gridSize, int cellSize,
                                   int basketSize)
        : firstImage(firstImage), secondImage(second), gridSize(gridSize), cellSize(cellSize),
          basketSize(basketSize) {

}

MatchData HistogramProcessor::create(DoubleImage &first, DoubleImage &second, int gridSize, int cellSize, int basketSize) {
    auto creator = HistogramProcessor(first, second, gridSize, cellSize, basketSize);
    auto firstDescriptor = creator.createDescriptors(creator.getFirstImage());

    auto secondDescriptor = creator.createDescriptors(creator.getSecondImage());

    return DescriptorUtil::match(firstDescriptor, secondDescriptor);
}
