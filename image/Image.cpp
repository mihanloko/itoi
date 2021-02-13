//
// Created by mikhail on 13.02.2021.
//

#include "Image.h"

Image::Image() {

}

Image::Image(const QString& name) {
    QImage image(name);
    height = image.height();
    width = image.width();
    data = std::make_unique<unsigned char[]>(width * height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            (*this)(x, y) = (0.229 * image.pixelColor(x, y).red() + 0.587 * image.pixelColor(x, y).green() + 0.114 * image.pixelColor(x, y).blue());
        }
    }
//    image.pixelColor(0, 0).gre;

}

int Image::getHeight() const {
    return height;
}

int Image::getWidth() const {
    return width;
}

unsigned char &Image::operator()(int x, int y) {
    return data.get()[x + y * width];
}

const unique_ptr<unsigned char[]> &Image::getData() const {
    return data;
}
