//
// Created by mikhail on 11.04.2021.
//

#include "lab1.h"
#include "../filters/FiltersImplementation.h"
#include "../filters/KernelFactory.h"

void lab1::run() {
    CopyBorderEffect copyBorderEffect;
    MirrorBorderEffect mirrorBorderEffect;
    ZeroBorderEffect zeroBorderEffect;
    testSobelOper("resources/in/cat.jpg", copyBorderEffect);
    testSobelOper("resources/in/cat.jpg", mirrorBorderEffect);
    testSobelOper("resources/in/cat.jpg", zeroBorderEffect);
    testGauss("resources/in/cat.jpg", 0.4, copyBorderEffect);
    testGauss("resources/in/cat.jpg", 5, mirrorBorderEffect);
    testGauss("resources/in/cat.jpg", 2.6, zeroBorderEffect);
    cout << "end work" << endl;
}

static void testSobelOper(const QString &imageName, BorderEffectAction &borderEffectAction) {
    auto input = Image(imageName);
    auto doubleInputImage = DoubleImage(input);
    auto sobelXImage = FiltersImplementation::derivX(doubleInputImage);
    auto sobelYSeparableImage = FiltersImplementation::applySeparable(doubleInputImage, KernelFactory::GetSobelSeparableY());
    auto sobelYImage = FiltersImplementation::derivY(doubleInputImage);
    auto result = DoubleImage(input.getWidth(), input.getHeight());
    for (int i = 0; i < result.size(); ++i)
        result.getData()[i] = sqrt(sobelXImage.getData()[i] * sobelXImage.getData()[i] +
                                sobelYImage.getData()[i] * sobelYImage.getData()[i]);
    Image::fromDouble(sobelXImage.getData(), sobelXImage.getWidth(), sobelXImage.getHeight()).saveToFile(
            "derivativeX_" + imageName + borderEffectAction.toString());
    Image::fromDouble(sobelYSeparableImage.getData(), sobelYSeparableImage.getWidth(), sobelYSeparableImage.getHeight()).saveToFile(
            "separable_derivativeY_" + imageName + borderEffectAction.toString() );
    Image::fromDouble(sobelYImage.getData(), sobelYImage.getWidth(), sobelYImage.getHeight()).saveToFile(
            "derivativeY_" + imageName + borderEffectAction.toString());
    Image::fromDouble(result.getData(), result.getWidth(), result.getHeight()).saveToFile(
            "sobel_" + imageName + borderEffectAction.toString());
}

static void testGauss(const QString &imageName, double sigma, BorderEffectAction &borderEffectAction) {
    auto input = Image(imageName);
    auto doubleInputImage = DoubleImage(input);
    double sigmaForTwiceFiltering = sigma;
    double sigmaSum = sigmaForTwiceFiltering * sqrt(2);
    cout << "start for " << imageName.toStdString() << " with sigmaForTwiceFiltering " << sigma << endl;
    cout << "start for " << imageName.toStdString() << " with sigmaSum " << sigmaSum << endl;
    auto gaussA = FiltersImplementation::applyGauss(doubleInputImage, sigmaForTwiceFiltering, borderEffectAction);
    auto twiceGauss = FiltersImplementation::applyGauss(gaussA, sigmaForTwiceFiltering, borderEffectAction);
    auto gaussSum = FiltersImplementation::applyGauss(doubleInputImage, sigmaSum, borderEffectAction);
    auto separableGauss = FiltersImplementation::applyGaussSeparable(doubleInputImage, sigmaSum, borderEffectAction);
    Image::fromDouble(twiceGauss.getData(), twiceGauss.getWidth(), twiceGauss.getHeight()).saveToFile(
            "gauss_twice_sigma" + imageName + QString::fromStdString(to_string(sigmaForTwiceFiltering)) + '_' +
            borderEffectAction.toString());
    Image::fromDouble(gaussSum.getData(), gaussSum.getWidth(), gaussSum.getHeight()).saveToFile(
            "gauss_sigma" + imageName + QString::fromStdString(to_string(sigmaSum)) + '_' +
            borderEffectAction.toString());
        Image::fromDouble(separableGauss.getData(), separableGauss.getWidth(), separableGauss.getHeight()).saveToFile(
                "separable_gauss_sigma" + imageName + QString::fromStdString(to_string(sigmaSum)) + '_' +
                borderEffectAction.toString());
}
