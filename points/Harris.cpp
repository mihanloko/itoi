//
// Created by mikhail on 27.04.2021.
//

#include "Harris.h"

vector<InterestingPoint> Harris::makeHarris(DoubleImage &image, BorderEffectAction &action) {
    int width = image.getWidth();
    int height = image.getHeight();

    auto gaussKernel = KernelFactory::GetGauss(WINDOW_RADIUS);

    auto dx = FiltersImplementation::derivativeX(image);
    auto dy = FiltersImplementation::derivativeY(image);
    auto mins = vector<vector<double>>(width, vector<double>(height));

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            vector<vector<double>> currentMatrix(2, vector<double>(2, 0));
            for (int u = -WINDOW_RADIUS; u <= WINDOW_RADIUS; u++) {
                for (int v = -WINDOW_RADIUS; v <= WINDOW_RADIUS; v++) {
                    double Ix = action.getPixel(dx, x + u, y + v);
                    double Iy = action.getPixel(dy, x + u, y + v);
                    double gaussPoint = gaussKernel(u + WINDOW_RADIUS, v + WINDOW_RADIUS);
                    currentMatrix[0][0] += Ix * Ix * gaussPoint;
                    currentMatrix[0][1] += Ix * Iy * gaussPoint;
                    currentMatrix[1][0] += Ix * Iy * gaussPoint;
                    currentMatrix[1][1] += Iy * Iy * gaussPoint;
                }
            }
            vector<double> eigenvalues = getEigenValues(currentMatrix);
            mins[x][y] = min(eigenvalues[0], eigenvalues[1]);
        }
    }
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

vector<double> Harris::getEigenValues(vector<vector<double>> &matrix) {
    auto eigenvalues = vector<double>(2);

    double a = 1;
    double b = -matrix[0][0] - matrix[1][1];
    double c = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    double d = sqr(b) - 4 * a * c;
    if (abs(d) < 1e-4)
        d = 0;
    if (d < 0) {
        return eigenvalues;
    }

    eigenvalues[0] = (-b + sqrt(d)) / (2 * a);
    eigenvalues[1] = (-b - sqrt(d)) / (2 * a);

    return eigenvalues;
}

double Harris::sqr(double value) {
    return value * value;
}
