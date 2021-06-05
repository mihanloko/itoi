//
// Created by mikhail on 11.04.2021.
//

#include "KernelFactory.h"


DoubleImage KernelFactory::GetSobelX() {
    return DoubleImage({
                               1.0, 0, -1.0,
                               2.0, 0, -2.0,
                               1.0, 0, -1.0
                       }, 3, 3);
}

DoubleImage KernelFactory::GetSobelY() {
    return DoubleImage({
                               1.0, 2.0, 1.0,
                               0.0, 0.0, 0.0,
                               -1.0, -2.0, -1.0
                       }, 3, 3);
}

pair<DoubleImage, DoubleImage> KernelFactory::GetSobelSeparableY() {
    return make_pair(DoubleImage({1, 2, 3}, 3, 1), DoubleImage({1, 0, -1}, 1, 3));
}


DoubleImage KernelFactory::GetIncreaseSharpness() {
    return DoubleImage({
                               -1.0, -1.0, -1.0,
                               -1.0, 9.0, -1.0,
                               -1.0, -1.0, -1.0
                       }, 3, 3);
}

DoubleImage KernelFactory::GetGauss(double sigma, bool isNeedNormalize) {
    auto halfSize = static_cast<int>(sigma * 3);
    int size = 2 * halfSize + 1;
    auto matrix_gauss = vector<double>(size * size);
    double normalize = 0.0;
    for (int x = -halfSize, i = 0; x <= halfSize; x++, i++) {
        for (int y = -halfSize, j = 0; y <= halfSize; y++, j++) {
            auto value = GetGaussKernelValue(x, y, sigma);
            matrix_gauss[i * size + j] = value;
            normalize += value;
        }
    }
    if (isNeedNormalize) {
        for (int i = 0; i < size * size; i++)
            matrix_gauss[i] /= normalize;
    }

    return DoubleImage(matrix_gauss, size, size);
}

pair<DoubleImage, DoubleImage> KernelFactory::GetGaussSeparableXY(int halfSize, bool normalize) {
    auto kernel = GetGaussSeparableX(halfSize, halfSize / 3.0, normalize);
    return GetSeparableFromKernel(kernel);
}

pair<DoubleImage, DoubleImage> KernelFactory::GetGaussSeparableXY(double sigma, bool normalize) {
    auto kernel = GetGaussSeparableX(sigma, normalize);
    return make_pair(DoubleImage(kernel, kernel.size(), 1), DoubleImage(kernel, 1, kernel.size()));
}

pair<DoubleImage, DoubleImage> KernelFactory::GetSeparableFromKernel(const vector<double>& kernel){
    int size = kernel.size();
    return make_pair(DoubleImage(kernel, size, 1), DoubleImage(kernel, 1, size));
}

double KernelFactory::GetGaussKernelValue(int x, int y, double sigma) {
    auto ss2 = sigma * sigma * 2;
    auto top = exp(-(x * x + y * y) / (ss2));
    auto bottom = M_PI * ss2;
    return top / bottom;
}

vector<double> KernelFactory::GetGaussSeparableX(double sigma, bool normalize) {
    int halfSize = static_cast<int>(sigma) * 3;
    int size = 2 * halfSize + 1;
    auto row = vector<double>(size);
    double sum = 0.0;
    auto ss2 = sigma * sigma * 2;
    for (int i = -halfSize, k = 0; i <= halfSize; i++, k++) {
        double value = exp(-(i * i) / ss2) / (M_PI * ss2);
        row[k] = value;
        sum += value;
    }
    if (normalize)
        for (int i = 0; i < size; ++i)
            row[i] /= sum;
    return row;
}

vector<double> KernelFactory::GetGaussSeparableX(int halfSize, double sigma, bool normalize) {
    auto size = halfSize * 2 + 1;
    auto row = vector<double>(size);
    double coef = 1 / (sqrt(2 * M_PI) * sigma);
    for (int x = -halfSize; x <= halfSize; x++) {
        row[x + halfSize] = coef * exp(-(x * x) / (2 * (sigma * sigma)));
    }
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += row[i];
    }
    if (normalize)
        for (int i = 0; i < size; i++) {
            row[i] /= sum;
        }
    return row;
}