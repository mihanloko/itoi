//
// Created by mikhail on 18.04.2021.
//
#include "OctaveFactory.h"
#include "../filters/FiltersImplementation.h"

vector<struct Octave>OctaveFactory::generateOctaves(int octavesCount, int nLevels, double sigma0, const DoubleImage &inputImage,
                                double sigmaA) {
    double k = pow(2.0, 1.0 / nLevels); // интервал между масштабами в октаве
    auto deltaSigma = calculateDeltaSigma(sigmaA, sigma0);
    auto newImage = DoubleImage(inputImage);
    auto startImage = FiltersImplementation::applyGauss(newImage, deltaSigma);
    auto globalSigma = sigma0;
    vector<Octave> octaves;
    for (int i = 0; i < octavesCount; i++) {
        auto octave = generateOneOctave(nLevels, sigma0, startImage, k, globalSigma);
        octaves.push_back(octave);
        globalSigma *= 2l;
        startImage = getHalfSizeImage(octave.getLast().getImage());
    }
    return octaves;
}

Octave OctaveFactory::generateOneOctave(int nLevels, double sigma0, const DoubleImage &startImage, double k,
                                  double globalSigma) {
    auto result = Octave();
    auto startElement = OctaveElement(sigma0, globalSigma, startImage);
    result.addElement(startElement);
    auto oldSigma = sigma0;
    double curK = k;
    for (int i = 1; i <= nLevels; i++) {

        auto newSigma = oldSigma * curK;
        auto deltaSigma = calculateDeltaSigma(oldSigma, newSigma);
        auto newImage = FiltersImplementation::applyGauss(startElement.getImage(), deltaSigma);
        OctaveElement element(newSigma, globalSigma * curK, newImage);
        result.addElement(OctaveElement(element));
        curK *= k;
    }
    return result;
}

double OctaveFactory::calculateDeltaSigma(double oldSigma, double newSigma) {
    return sqrt(newSigma * newSigma - oldSigma * oldSigma);
}

DoubleImage OctaveFactory::getHalfSizeImage(DoubleImage &image) {
    auto res = DoubleImage(image.getWidth() / 2, image.getHeight() / 2);

    for (int x = 0; x < res.getWidth(); x++)
        for (int y = 0; y < res.getHeight(); y++)
            res(x, y) = image(x * 2, y * 2);
    if (res.size() != ((image.getWidth() / 2) * (image.getHeight() / 2))) {
        cout << "Invalid function" << endl;
        throw runtime_error("invalid");
    }
    return DoubleImage(res.normalize());
//    return DoubleImage(pixels, image.getWidth() / 2, image.getHeight() / 2);;
}


DoubleImage OctaveFactory::L(DoubleImage &inputImage, vector<Octave> pyramid, double sigma) {
    auto targetLayer = pyramid[0].getElements()[0];

    //Поиск нужной октавы
    int octaveLevel = 0;
    int octaveCount = 0;
    for (auto &octave : pyramid) {
        for (auto &layer : octave.getElements()) {
            if (fabs(layer.getGlobalSigma() - sigma) < fabs(targetLayer.getGlobalSigma() - sigma)) {
                targetLayer = layer;
                octaveLevel = octaveCount;
            }
        }
        octaveCount++;
    }

    int transformationCoef =static_cast<int>(pow(2, octaveLevel));
    auto output = DoubleImage(inputImage.getWidth(), inputImage.getHeight());
    for (int x = 0; x < inputImage.getWidth(); x++)
        for (int y = 0; y < inputImage.getHeight(); y++) {
            //преобразование координат
            int x_n = static_cast<int>(x / transformationCoef);
            int y_n = static_cast<int>(y / transformationCoef);
            if (y_n >= targetLayer.getImage().getHeight()) y_n = targetLayer.getImage().getHeight() - 1;
            if (x_n >= targetLayer.getImage().getWidth()) x_n = targetLayer.getImage().getWidth() - 1;

            output(x, y) = targetLayer.getImage()(x_n, y_n);
        }
    return output;
}
