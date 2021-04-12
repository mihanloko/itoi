//
// Created by mikhail on 11.04.2021.
//

#include "lab1.h"

void lab1::run() {
    CopyBorderEffect copyBorderEffect;
    MirrorBorderEffect mirrorBorderEffect;
    ZeroBorderEffect zeroBorderEffect;
    sobelOperatorTest("cat.jpg", copyBorderEffect);
    sobelOperatorTest("wall.jpg", mirrorBorderEffect);
    sobelOperatorTest("cat  .jpg", zeroBorderEffect);
    gaussTest("cat.jpg", 2.5, copyBorderEffect);
    gaussTest("cat.jpg", 2.5, mirrorBorderEffect);
    gaussTest("cat.jpg", 2.5, zeroBorderEffect);
}

void lab1::sobelOperatorTest(const QString &imageName, BorderEffectAction &borderEffectAction) {
    auto input = Image(imageName);
    auto doubleInputImage = DoubleImage(input);
    auto sobelXImage = FiltersImplementation::derivativeX(doubleInputImage);
    auto sobelYSeparableImage = FiltersImplementation::applySeparable(doubleInputImage,
                                                                      KernelFactory::GetSobelSeparableY());
    auto sobelYImage = FiltersImplementation::derivativeY(doubleInputImage);
    auto result = DoubleImage(input.getWidth(), input.getHeight());
    for (int i = 0; i < result.size(); ++i) {
        result.getData()[i] = sqrt(sobelXImage.getData()[i] * sobelXImage.getData()[i] +
                                   sobelYImage.getData()[i] * sobelYImage.getData()[i]);
    }
    Image::fromDouble(sobelXImage.normalize(255).getData(), sobelXImage.getWidth(), sobelXImage.getHeight()).saveToFile(
            "derivativeX_" + borderEffectAction.toString() + "_" + imageName);
    Image::fromDouble(sobelYSeparableImage.normalize(255).getData(),
                      sobelYSeparableImage.getWidth(),
                      sobelYSeparableImage.getHeight()).saveToFile("separable_derivativeY_" +
                                                                   borderEffectAction.toString() +
                                                                   "_" +
                                                                   imageName);
    Image::fromDouble(sobelYImage.normalize(255).getData(), sobelYImage.getWidth(), sobelYImage.getHeight())
            .saveToFile("derivativeY_" + borderEffectAction.toString() + "_" + imageName);
    Image::fromDouble(result.normalize(255).getData(), result.getWidth(), result.getHeight())
            .saveToFile("sobel_" + borderEffectAction.toString() + "_" + imageName);
}

void lab1::gaussTest(const QString &imageName, double sigma, BorderEffectAction &borderEffectAction) {
    auto input = Image(imageName);
    auto doubleInputImage = DoubleImage(input);
    double sigmaForTwiceFiltering = sigma;
    double sigmaSum = sigmaForTwiceFiltering * sqrt(2);
    auto gaussA = FiltersImplementation::applyGauss(doubleInputImage, sigmaForTwiceFiltering, borderEffectAction);
    auto twiceGauss = FiltersImplementation::applyGauss(gaussA, sigmaForTwiceFiltering, borderEffectAction);
    auto gaussSum = FiltersImplementation::applyGauss(doubleInputImage, sigmaSum, borderEffectAction);
    auto separableGauss = FiltersImplementation::applyGaussSeparable(doubleInputImage, sigmaSum, borderEffectAction);
    Image::fromDouble(twiceGauss.normalize(255).getData(), twiceGauss.getWidth(), twiceGauss.getHeight()).saveToFile(
            "gauss_twice_sigma_" +
            QString::fromStdString(to_string(sigmaForTwiceFiltering)) +
            '_' +
            borderEffectAction.toString() +
            "_" +
            imageName);
    Image::fromDouble(gaussSum.normalize(255).getData(), gaussSum.getWidth(), gaussSum.getHeight()).saveToFile(
            "gauss_sigma_" +
            QString::fromStdString(to_string(sigmaSum)) +
            '_' +
            borderEffectAction.toString() +
            "_" +
            imageName);
}
