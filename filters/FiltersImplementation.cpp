//
// Created by mikhail on 11.04.2021.
//

#include "FiltersImplementation.h"


DoubleImage FiltersImplementation::applyCrossCorel(DoubleImage &image, DoubleImage &kernel, BorderEffectAction &borderPolicy) {
    int kernelW = kernel.getWidth();
    int kernelH = kernel.getHeight();
    if (!(kernelW % 2) || !(kernelH % 2)) {
        cerr << "Invalid kernel size" << endl;
    }
    int kernelKW = kernelW / 2;
    int kernelKH = kernelH / 2;
    auto result  = DoubleImage(image.getWidth(), image.getHeight());
    for (int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            double res = 0;
            for (int i = 0, u = -kernelKW; i < kernel.getWidth(); i++, u++) {
                for (int j = 0, v = -kernelKH; j < kernel.getHeight(); j++, v++) {
                    res += borderPolicy.getPixel(image, x + u, y + v) * kernel(i, j);
                }
            }
            result(x, y) = res;
        }
    }
    return result;
}

DoubleImage FiltersImplementation::applyConvolution(DoubleImage &image, DoubleImage &kernel, BorderEffectAction &borderPolicy) {
    int kernelW = kernel.getWidth();
    int kernelH = kernel.getHeight();
    if (!(kernelW % 2) || !(kernelH % 2)) {
        cerr << "Invalid kernel size. Width: " << kernelW << ", height: " << kernelH << endl;
    }
    int kernelKW = kernelW / 2;
    int kernelKH = kernelH / 2;
    auto result  = DoubleImage(image.getWidth(), image.getHeight());
    for (int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            double res = 0;
            for (int i = 0, u = -kernelKW; i < kernelW; i++, u++) {
                for (int j = 0, v = -kernelKH; j < kernelH; j++, v++) {
                    res += borderPolicy.getPixel(image, x - u, y - v) * kernel(i, j);
                }
            }
            result(x, y) = res;
        }
    }
    return result;
}
void FiltersImplementation::print(ostream &out, DoubleImage &matrix) {
    int w = matrix.getWidth();
    int h = matrix.getHeight();
    out << "Image [" << w << "," << h << "]" << endl;
    out << std::fixed;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            out << setprecision(3) << setw(7) << right << matrix(x, y);
        }
        out << endl;
    }
    out.flush();
}

DoubleImage FiltersImplementation::derivativeX(DoubleImage &image, BorderEffectAction &borderPolicy) {
    auto kernel = KernelFactory::GetSobelX();
    return applyConvolution(image, kernel, borderPolicy);
}

DoubleImage FiltersImplementation::derivativeY(DoubleImage &image, BorderEffectAction &borderPolicy) {
    auto kernel = KernelFactory::GetSobelY();
    return applyConvolution(image, kernel, borderPolicy);
}

DoubleImage FiltersImplementation::applyGauss(DoubleImage &image, double sigma, BorderEffectAction &policy, bool normalize){
    auto gaussFilter = KernelFactory::GetGauss(sigma);
    auto res = FiltersImplementation::applyConvolution(image, gaussFilter, policy);
    if (normalize)
        return res.normalize();
    return res;
}

DoubleImage FiltersImplementation::applyGaussSeparable(DoubleImage &image, double sigma, BorderEffectAction &policy, bool normalize) {
    auto result = applySeparable(image, KernelFactory::GetGaussSeparableXY(sigma), policy);
    if(normalize)
        return result.normalize();
    return result;
}

DoubleImage FiltersImplementation::applySeparable(DoubleImage &image, pair<DoubleImage, DoubleImage> pair, BorderEffectAction &policy) {
    auto resX = applyConvolution(image, pair.first, policy);
    auto resY = applyConvolution(resX, pair.second, policy);
    return resY;
}

double FiltersImplementation::getSeparableValue(pair<DoubleImage, DoubleImage> &pair, int x, int y) {
    return pair.first(x, 0) * pair.second(0, y);
}