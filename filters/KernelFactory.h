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

    static DoubleImage GetGauss(double sigma, bool isNeedNormalize = false);
    static vector<double> GetGaussSeparableX(double sigma, bool normalize  = false);

    static pair<DoubleImage, DoubleImage> GetGaussSeparableXY(double sigma, bool normalize = false);

    static pair<DoubleImage, DoubleImage> GetSobelSeparableY();

    static double GetGaussKernelValue(int x, int y, double sigma);

    static pair<DoubleImage, DoubleImage> GetGaussSeparableXY(int halfSize, bool normalize = true);

    static vector<double> GetGaussSeparableX(int halfSize, double sigma, bool normalize);

    static pair<DoubleImage, DoubleImage> GetSeparableFromKernel(const vector<double> &kernel);
};


#endif //ITOI_KERNELFACTORY_H
