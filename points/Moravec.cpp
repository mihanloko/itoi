//
// Created by mikhail on 27.04.2021.
//

#include "Moravec.h"

vector<InterestingPoint> Moravec::makeMoravec(DoubleImage &image) {
    auto imageFiltered = FiltersImplementation::applyGauss(image, 0.66);
    int width = image.getWidth();
    int height = image.getHeight();
    auto mins = getMinimums(image);
    auto candidates = DetectorUtil::getCandidates(mins, width, height);
    auto filteredCandidates = vector<InterestingPoint>();
    for (InterestingPoint point: candidates) {
        if (point.getProbability() > MIN_PROBABILITY) {
            filteredCandidates.push_back(point);
        }
    }
    sort(filteredCandidates.begin(), filteredCandidates.end(), [](const InterestingPoint & a, const InterestingPoint & b) -> bool {
        return b.getProbability() > a.getProbability();
    });
    int right = filteredCandidates.size() > MAX_SIZE ? MAX_SIZE : filteredCandidates.size();
    return vector<InterestingPoint>(&filteredCandidates[0], &filteredCandidates[right]);
}

vector<vector<double>> Moravec::getMinimums(DoubleImage &image, BorderEffectAction &action) {
    int height = image.getHeight();
    int width = image.getWidth();
    auto mins = vector<vector<double>>(width, vector<double>(height));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            double min = std::numeric_limits<double>::max();
            for (int k = 0; k < dx.size(); k++) {
                double sum = 0;
                for (int u = -WINDOW_RADIUS; u <= WINDOW_RADIUS; u++) {
                    for (int v = -WINDOW_RADIUS; v <= WINDOW_RADIUS; v++) {
                        sum += sqr(action.getPixel(image, i + u, j + v) -
                                   action.getPixel(image, i + u + dx[k], j + v + dy[k]));
                    }
                }
                min = (min < sum) ? min : sum;
            }
            mins[i][j] = min;
        }
    }
    return mins;
}

double Moravec::sqr(double value) {
    return value * value;
}
