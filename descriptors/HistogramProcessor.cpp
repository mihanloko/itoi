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
    auto gauss = KernelFactory::GetGauss(3);

    vector<Descriptor> descriptors;
    for (auto &point: points) {
        vector<vector<vector<double>>> bins = calculateHistograms(gradient, x, y, gauss, gridSize, 4, basketSize, point, 0);
        vector<double> v(gridSize * gridSize * basketSize);
        for(int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                for (int k = 0; k < basketSize; k++) {
                    v[i * gridSize * basketSize + j * basketSize + k] = bins[i][j][k];
                }
            }
        }
        Descriptor d = Descriptor(point);
        d.setDescriptor(v);
        descriptors.push_back(d);
    }
    return descriptors;
}

vector<vector<vector<double>>> HistogramProcessor::calculateHistograms(DoubleImage& gradient, DoubleImage& dx, DoubleImage& dy, DoubleImage& gauss,
                                        int gridSize, int blockSize, int binsCount,
                                        InterestingPoint& center, double angle) {
    CopyBorderEffect effect;
    int gaussK = gauss.getWidth() / 2;

    double PI = 3.141592653589793238462643;
    vector<vector<vector<double>>> bins(gridSize, vector<vector<double>>(gridSize, vector<double>(binsCount)));
    double step = 2 * PI / binsCount;

    int from = gridSize * blockSize / 2, to = gridSize * blockSize - from;
    for(int u = -from; u < to; u++)
        for(int v = -from; v < to; v++) {
            int x = center.getX() + u, y = center.getY() + v;

            double theta = atan2(effect.getPixel(dy, x, y), effect.getPixel(dx, x, y)) + PI;
            double value = effect.getPixel(gradient, x, y);

            int rotatedU = (int)round(u * cos(angle) + v * sin(angle));
            int rotatedV = (int)round(v * cos(angle) - u * sin(angle));

            double rotatedTheta = theta - angle;
            if(rotatedTheta < 0) rotatedTheta += PI * 2;

            int column = (rotatedU + from) / blockSize;
            int row = (rotatedV + from) / blockSize;

            if(column < 0 || column >= gridSize || row < 0 || row >= gridSize) continue;

            value = value * gauss(rotatedU + gaussK, rotatedV + gaussK);

            int leftBin = min((int)floor(rotatedTheta / step), binsCount - 1);
            int rightBin = (leftBin + 1) % binsCount;

            double ratio = fmod(rotatedTheta, step) / step;
            bins[row][column][leftBin] += value * (1 - ratio);
            bins[row][column][rightBin] += value * ratio;
        }

    return bins;
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
