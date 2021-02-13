//
// Created by mikhail on 13.02.2021.
//

#include "DoubleImage.h"

DoubleImage::DoubleImage() {

}

DoubleImage::DoubleImage(const QString& name) {
    QImage image(name);
    height = image.height();
    width = image.width();
    data = std::make_unique<double[]>(width * height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            (*this)(x, y) = (0.229 * image.pixelColor(x, y).red() + 0.587 * image.pixelColor(x, y).green() + 0.114 * image.pixelColor(x, y).blue()) / 255.;
        }
    }
//    image.pixelColor(0, 0).gre;

}

int DoubleImage::getHeight() const {
    return height;
}

int DoubleImage::getWidth() const {
    return width;
}

double &DoubleImage::operator()(int x, int y) {
    return data.get()[x + y * width];
}

DoubleImage::DoubleImage(const Image &image) {
    width = image.getWidth();
    height = image.getHeight();
    data = std::make_unique<double[]>(width * height);
    for (int i = 0; i < width * height; i++) {
        data.get()[i] = image.getData()[i] / 255.;
    }
}
