//
// Created by mikhail on 01.05.2021.
//

#ifndef ITOI_LAB3_H
#define ITOI_LAB3_H


#include <QString>
#include "../image/Image.h"

class lab3 {
private:
    const QString &imageName, &extension;
    int pointsCount = 100;
    int windowSize = 4;
    double harrisThresholdCoef = 0.2;
    double moravecThresholdCoef = 0.2;
    Image inputImage;
public:
    lab3(const QString &imageName, const QString &extension) : imageName(imageName), extension(extension) {
        this->inputImage = Image(imageName + extension);
    }
    static void run();
};


#endif //ITOI_LAB3_H
