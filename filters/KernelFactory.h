//
// Created by mikhail on 11.04.2021.
//

#ifndef ITOI_KERNELFACTORY_H
#define ITOI_KERNELFACTORY_H

#include <cmath>
#include "../image/DoubleImage.h"


class KernelFactory {
public:
    static DoubleImage GetSobelX();

    static DoubleImage GetSobelY();

    static DoubleImage GetIncreaseSharpness();

    static DoubleImage GetGauss(double sigma);
    static vector<double> GetGaussSeparableX(double sigma);
    static DoubleImage GetGauss(double sigma, int radius, bool normalize = false);

    static pair<DoubleImage, DoubleImage> GetGaussSeparableXY(double sigma);

    static pair<DoubleImage, DoubleImage> GetSobelSeparableY();
};


#endif //ITOI_KERNELFACTORY_H
