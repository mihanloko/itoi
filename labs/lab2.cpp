//
// Created by mikhail on 18.04.2021.
//

#include "lab2.h"
#include "../octaves/OctaveFactory.h"

void lab2::run() {
    lab2(5, 3, 1, 0.5, 7.13, "cat", ".jpg").process();
    lab2(4, 2, 1, 0.5, 9, "wall", ".jpg").process();
}

void lab2::process() {
    auto input = Image(imageName + ext);
    auto inputDouble = DoubleImage(input);
    auto octaves = OctaveFactory::generateOctaves(nOctaves, nLevels, sigma0, inputDouble, sigmaA);
    for (int i = 0; i < octaves.size(); i++) {
        auto elements = octaves[i].getElements();
        for (int j = 0; j < elements.size(); j++) {
            auto fileName = imageName.toStdString()
                      + "_octave_" + to_string(i) + "_lvl_" + to_string(j) +
                      "_local_" + to_string(elements[j].getLocalSigma()) +
                      "_global_" + to_string( elements[j].getGlobalSigma()) +
                      ext.toStdString();
            Image::fromDouble(elements[j].getImage().normalize(255).getData(),
                              elements[j].getImage().getWidth(),
                              elements[j].getImage().getHeight()).saveToFile(QString::fromStdString(fileName));
        }
    }
    auto L = OctaveFactory::L(inputDouble, octaves, sigmaL);
    Image::fromDouble(L.normalize(255).getData(), L.getWidth(), L.getHeight()).saveToFile(imageName +
                                                                           "_L_" +
                                                                           QString::fromStdString(to_string(sigmaL)) +
                                                                           ext);
    saveCompoundImage(octaves);
}

void lab2::saveCompoundImage(const vector<Octave> &octaves) {
    for (int i = 0; i < nLevels; i++) {
        auto resultImage = Image::fromDouble(octaves[0].getElements()[i].getImage().normalize(255).getData(),
                                             octaves[0].getElements()[i].getImage().getWidth(),
                                             octaves[0].getElements()[i].getImage().getHeight());
        for (int j = 0; j < nOctaves; j++) {
            auto curImage = Image::fromDouble(octaves[j].getElements()[i].getImage().normalize(255).getData(),
                                              octaves[j].getElements()[i].getImage().getWidth(),
                                              octaves[j].getElements()[i].getImage().getHeight());
            for (int x = 0; x < curImage.getWidth(); x++)
                for (int y = 0; y < curImage.getHeight(); y++)
                    resultImage(x, (resultImage.getHeight() - curImage.getHeight() + y)) = curImage(x, y);
        }
        resultImage.saveToFile(imageName + QString::fromStdString("_compound_lvl_" + to_string(i)) + ext);
    }
}
