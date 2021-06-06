//
// Created by mikhail on 06.06.2021.
//

#include "RotationInvariantProcessor.h"

vector<Descriptor> RotationInvariantProcessor::createDescriptors(DoubleImage &img) {

    double PI = 3.141592653589793238462643;
    int FULL_BINS_COUNT = 36;
    int blockSize = 4;
    int binsCount = 8;
    double NEXT_PEAK_THRESHOLD = 0.8;

    double fullStep = 2 * PI / FULL_BINS_COUNT;

    auto dx = FiltersImplementation::derivativeX(img);
    auto dy = FiltersImplementation::derivativeY(img);

    auto gradient = DescriptorUtil::getGradient(dx, dy);
    auto gradientAngle = DescriptorUtil::getGradientAngle(dx, dy);

    Harris harris;
    auto points = harris.makeHarris(img);
    auto gauss = KernelFactory::GetGauss(3);

    vector<Descriptor> descriptors;

    for(InterestingPoint point : points) {

        vector<double> full = calculateHistograms(gradient, dx, dy, gauss,
                                            1, gridSize * blockSize, FULL_BINS_COUNT, point, 0)[0][0];

        int peak = findMaximum(full, -1);
        int secondPeak = findMaximum(full, peak);

        vector<double> angles;
        angles.push_back(peak * fullStep);

        if (full[secondPeak] / full[peak] > NEXT_PEAK_THRESHOLD) {
            angles.push_back(secondPeak * fullStep);
        }

        for (double angle : angles) {
            Descriptor d = Descriptor(point);
            auto histograms = calculateHistograms(gradient, dx, dy, gauss, gridSize, blockSize, binsCount, point, angle);
            vector<double> v = toVector(histograms, gridSize, binsCount);
            d.setDescriptor(v);
            descriptors.push_back(d);
        }
    }

    return descriptors;

}

vector<vector<vector<double>>> RotationInvariantProcessor::calculateHistograms(DoubleImage& gradient, DoubleImage& dx, DoubleImage& dy, DoubleImage& gauss,
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

DoubleImage &RotationInvariantProcessor::getFirstImage() {
    return firstImage;
}

DoubleImage &RotationInvariantProcessor::getSecondImage() {
    return secondImage;
}

RotationInvariantProcessor::RotationInvariantProcessor(DoubleImage &firstImage, DoubleImage &second, int gridSize, int cellSize,
                             int basketSize)
        : firstImage(firstImage), secondImage(second), gridSize(gridSize), cellSize(cellSize),
          basketSize(basketSize) {

}

MatchData RotationInvariantProcessor::create(DoubleImage &first, DoubleImage &second, int gridSize, int cellSize, int basketSize) {
    auto creator = RotationInvariantProcessor(first, second, gridSize, cellSize, basketSize);
    auto firstDescriptor = creator.createDescriptors(creator.getFirstImage());

    auto secondDescriptor = creator.createDescriptors(creator.getSecondImage());

    return DescriptorUtil::match(firstDescriptor, secondDescriptor);
}

int RotationInvariantProcessor::findMaximum(vector<double> &array, int exclude) {
    int index = -1;
    for(int i = 0; i < array.size(); i++) {
        if (i != exclude && (index == -1 || array[i] > array[index])) {
            index = i;
        }
    }

    return index;
}

vector<double> RotationInvariantProcessor::toVector(vector<vector<vector<double>>>& bins, int gridSize, int binsCount) {
    vector<double> result = vector<double>(gridSize * gridSize * binsCount);

    for(int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            for (int k = 0; k < binsCount; k++) {
                result[i * gridSize * binsCount + j * binsCount + k] = bins[i][j][k];
            }
        }
    }

    double sum = 0;
    for(double d : result) {
        sum += d * d;
    }
    double length = sqrt(sum);

    for (double & i : result) {
        i = i / length;
    }

    return result;
}

