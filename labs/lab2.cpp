//
// Created by mikhail on 18.04.2021.
//

#include "lab2.h"
#include "../octaves/OctaveFactory.h"

void lab2::run() {
//        a
    lab2(5, 2, 1, 0.5, 7.13, "butterfly", ".jpg").work();
    lab2(3, 2, 1.5, 0.8, 4, "shrek", ".jpg").work();
    lab2(3, 4, 0.7, 0.3, 3, "cat_dog", ".jpg").work();
//        b
    lab2(2, 4, 1, 0.5, 3, "butterfly1", ".jpg").work();
    lab2(3, 3, 1, 0.5, 6, "butterfly2", ".jpg").work();
    lab2(4, 2, 1, 0.5, 9, "butterfly3", ".jpg").work();
}

void lab2::work() {
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
            Image::fromDouble(elements[j].getImage().getData(),
                              elements[j].getImage().getWidth(),
                              elements[j].getImage().getHeight()).saveToFile(QString::fromStdString(fileName));
        }
    }
    auto L = OctaveFactory::L(inputDouble, octaves, sigmaL);
    Image::fromDouble(L.getData(), L.getWidth(), L.getHeight()).saveToFile(imageName +
                                                                           "L_" +
                                                                           QString::fromStdString(to_string(sigmaL)) +
                                                                           ext);
    saveAsCompoundImage(octaves);
}

void lab2::saveAsCompoundImage(const vector<Octave> &octaves) {
    for (int i = 0; i < nLevels; i++) {
        auto resultImage = Image::fromDouble(octaves[0].getElements()[i].getImage().getData(),
                                             octaves[0].getElements()[i].getImage().getWidth(),
                                             octaves[0].getElements()[i].getImage().getHeight());
        for (int j = 0; j < nOctaves; j++) {
            auto curImage = Image::fromDouble(octaves[j].getElements()[i].getImage().getData(),
                                              octaves[j].getElements()[i].getImage().getWidth(),
                                              octaves[j].getElements()[i].getImage().getHeight());
            for (int x = 0; x < curImage.getWidth(); x++)
                for (int y = 0; y < curImage.getHeight(); y++)
                    resultImage(x, (resultImage.getHeight() - curImage.getHeight() + y)) = curImage(x, y);
        }
        resultImage.saveToFile(imageName + QString::fromStdString("_compound_lvl_" + to_string(i)) + ext);
    }
}
