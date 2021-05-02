//
// Created by mikhail on 02.05.2021.
//

#ifndef ITOI_DATASAVER_H
#define ITOI_DATASAVER_H

#include <vector>
#include <QString>
#include "InterestingPoint.h"
#include "../image/DoubleImage.h"

using namespace std;

class DataSaver {
public:
    static vector<InterestingPoint> saveData(DoubleImage &image, vector<vector<double>> &mins, vector<InterestingPoint> &points, const QString& method);
};


#endif //ITOI_DATASAVER_H
