//
// Created by mikhail on 01.05.2021.
//

#include "DetectorUtil.h"

vector<InterestingPoint> DetectorUtil::getCandidates(vector<vector<double>> values, int width, int height) {
    static const vector<int> dx{-1, 0, 1, -1, 1, -1, 0, -1};
    static const vector<int> dy{-1, -1, -1, 0, 0, 1, 1, 1};
    vector<InterestingPoint> candidates = vector<InterestingPoint>();
    double min = std::numeric_limits<double>::max(),
            max = std::numeric_limits<double>::min();

    for (auto &i : values) {
        for (auto temp: i) {
            if (max < temp) max = temp;
            if (min > temp) min = temp;
        }
    }
    double threshold = min + (max - min) * 0.05;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            bool ok = true;
            double currentValue = values[i][j];
            for (int k = 0; k < dx.size() && ok; k++) {
                if (i + dx[k] < 0 ||
                    i + dx[k] >= width ||
                    j + dy[k] < 0 ||
                    j + dy[k] >= height) continue;
                if (currentValue < values[i + dx[k]][j + dy[k]])
                    ok = false;
            }
            if (ok && currentValue > threshold) {
                candidates.emplace_back(i, j, values[i][j]);
            }
        }
    }
    return candidates;
}

vector<InterestingPoint> DetectorUtil::filter(vector<InterestingPoint> &points, int maxSize, int maxRadius) {
    vector<InterestingPoint> result(points);
    int r = 0;
    while (result.size() > maxRadius && r < maxSize) {
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result.size(); j++) {
                double dist = InterestingPoint::distance(result[i], result[j]);
                if (dist <= r) {
                    if (result[i].getProbability() < result[j].getProbability()) {
                        result.erase(result.begin() + i);
                        i--;
                        j = result.size();
                    }
                }
            }
        }
        r++;
    }
    sort(result.begin(), result.end(), [](const InterestingPoint & a, const InterestingPoint & b) -> bool {
        return b.getProbability() > a.getProbability();
    });
    if (result.size() > 50) {
        result = vector<InterestingPoint>(&result[0], &result[50]);
    }
    return result;
}

vector<InterestingPoint> DetectorUtil::matToPoints(DoubleImage &mat) {
    vector<InterestingPoint> list;
    for (int x = 0; x < mat.getWidth(); x++)
        for (int y = 0; y < mat.getHeight(); y++)
            if (mat(x, y) > 1e-6) list.emplace_back(x, y, mat(x, y));
    return list;
}
