//
// Created by mikhail on 18.04.2021.
//

#ifndef ITOI_OCTAVEELEMENT_H
#define ITOI_OCTAVEELEMENT_H

#include "../image/DoubleImage.h"

class OctaveElement {
    private:
        double localSigma, globalSigma;
        DoubleImage image;
    public:
    OctaveElement(double localSigma, double globalSigma, const DoubleImage &image)
            : localSigma(localSigma), globalSigma(globalSigma), image(image) {}

    double getLocalSigma() const {
        return localSigma;
    }

    double getGlobalSigma() const {
        return globalSigma;
    }

    DoubleImage &getImage() {
        return image;
    }

};


#endif //ITOI_OCTAVEELEMENT_H
