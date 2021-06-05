//
// Created by mikhail on 27.04.2021.
//

#include "Harris.h"
#include "DataSaver.h"
#include "../borders/ZeroBorderEffect.h"

vector<InterestingPoint> Harris::makeHarris(DoubleImage &image, BorderEffectAction &action) {
    auto gauss = KernelFactory::GetGauss(WINDOW_RADIUS);
    int gaussK = gauss.getWidth() / 2;

    auto dx = FiltersImplementation::derivativeX(image);
    auto dy = FiltersImplementation::derivativeY(image);

    DoubleImage lambdas = image.withSameSize();
    for(int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            double A = 0, B = 0, C = 0;

            for (int u = -WINDOW_RADIUS; u <= WINDOW_RADIUS; u++)
                for (int v = -WINDOW_RADIUS; v <= WINDOW_RADIUS; v++) {
                    double multiplier = gauss(u + gaussK, v + gaussK);

                    A += multiplier * sqr(action.getPixel(dx, x + u, y + v));
                    B += multiplier * action.getPixel(dx, x + u, y + v) * action.getPixel(dy, x + u, y + v);
                    C += multiplier * sqr(action.getPixel(dy, x + u, y + v));
                }

            lambdas(x, y) = calcLambdaMin(A, B, C);
        }
    }

    lambdas = lambdas.normalize();
    auto result = lambdas.withSameSize();

    for(int x = 0; x < lambdas.getWidth(); x++) {
        for (int y = 0; y < lambdas.getHeight(); y++) {
            if (lambdas(x, y) <= MIN_PROBABILITY || hasLargerNeighbour(lambdas, x, y)) {
                continue;
            }
            result(x, y) = lambdas(x, y);
        }
    }

    auto points = DetectorUtil::matToPoints(result);
    return DetectorUtil::filter(points, 100, min(image.getHeight() / 2, image.getWidth() / 2));
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

double Harris::calcLambdaMin(double A, double B, double C) {
    double a = 1, b = -(A + C), c = A * C - B * B;
    double D = b * b - 4 * a * c;

    if (D < 0 && D > -1e-6) D = 0;
    if (D < 0) return 0;

    double lambda1 = (-b + sqrt(D)) / (2 * a);
    double lambda2 = (-b - sqrt(D)) / (2 * a);

    return min(lambda1, lambda2);
}

bool Harris::hasLargerNeighbour(DoubleImage& image, int x, int y) {
    ZeroBorderEffect effect;
    for(int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;
            if (effect.getPixel(image, x + dx, y + dy) - image(x, y) > 1e-4)
                return true;
        }
    }
    return false;
}
