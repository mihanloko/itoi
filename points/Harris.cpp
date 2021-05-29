//
// Created by mikhail on 27.04.2021.
//

#include "Harris.h"
#include "DataSaver.h"
#include "../borders/MirrorBorderEffect.h"

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
//    int right = filteredCandidates.size() > MAX_SIZE ? MAX_SIZE : filteredCandidates.size();
    return DataSaver::saveData(image, mins, filteredCandidates, "Harris");
//    return vector<InterestingPoint>(&filteredCandidates[0], &filteredCandidates[right]);
}


vector<InterestingPoint> Harris::localMaximum(DoubleImage& image, double thresholdCoeff) {
    vector<int> dx{-1, 0, 1, -1, 1, -1, 0, -1};
    vector<int> dy{-1, -1, -1, 0, 0, 1, 1, 1};
    int w = image.getWidth();
    int h = image.getHeight();

//    image.normalize();

    double min = std::numeric_limits<double>::max(),
            max = std::numeric_limits<double>::min();
    // min and max search
    for (int i = 0; i < image.size(); i++) {
        double temp = image.getData()[i];
        if (max < temp) max = temp;
        if (min > temp) min = temp;
    }

    MirrorBorderEffect effect;
    double threshold = min + (max - min) * thresholdCoeff;
    vector<InterestingPoint> result;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            bool isCorrect = true;
            double currentValue = image(i, j);
            for (int k = 0; k < dx.size() && isCorrect; k++) {
                if (i + dx[k] < 0 || i + dx[k] >= w || j + dy[k] < 0 || j + dy[k] >= h)
                    continue;
                if (currentValue < effect.getPixel(image, i + dx[k], j + dy[k]))
                    isCorrect = false;
            }
            if (isCorrect && currentValue > threshold) {
                result.emplace_back(i, j, currentValue);
            }
        }
    }
    return result;
}

vector<InterestingPoint> Harris::filter(vector<InterestingPoint> &points, int pointsCount) {
    if (pointsCount >= points.size())
        return points;
    sort(points.begin(), points.end(), [](InterestingPoint a, InterestingPoint b) {
        return b.getProbability() < a.getProbability();
    });
    double l = 0, r = numeric_limits<double>::max();
    for (int i = pointsCount; i > 0; i--) {
        double middle = (l + r) / 2;
        if (filter(points, middle).size() > pointsCount) {
            l = middle;
        } else {
            r = middle;
        }
    }
    auto filtered = filter(points, l);
    return vector<InterestingPoint>(points.begin(), points.begin() + min((int) filtered.size(), pointsCount));
}

vector<InterestingPoint> Harris::filter(vector<InterestingPoint> &points, double radius) {
    vector<InterestingPoint> filtered;
    for (int i = 0; i < points.size(); ++i) {
        bool ok = true;
        for (int j = 0; j < points.size(); ++j) {
            if (i == j) continue;
            if (InterestingPoint::distance(points[i], points[j]) < radius) {
                ok = false;
                break;
            }
        }
        if (ok) {
            filtered.push_back(points[i]);
        }
    }
    return filtered;
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
