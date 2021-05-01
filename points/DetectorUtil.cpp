//
// Created by mikhail on 01.05.2021.
//

#include "DetectorUtil.h"

vector<InterestingPoint> DetectorUtil::getCandidates(vector<vector<double>> values, int width, int height) {
    static const vector<int> dx{-1, 0, 1, -1, 1, -1, 0, -1};
    static const vector<int> dy{-1, -1, -1, 0, 0, 1, 1, 1};
    vector<InterestingPoint> candidates = vector<InterestingPoint>();
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
            if (ok) {
                candidates.emplace_back( values[i][j], i, j);
            }
        }
    }
    return candidates;
}
