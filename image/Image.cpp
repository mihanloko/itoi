//
// Created by mikhail on 13.02.2021.
//

#include "Image.h"

Image::Image() {

}

Image::Image(const QString& name) {
    this->name = name;
    QImage image(name);
    height = image.height();
    width = image.width();
    data = vector<unsigned char>(width * height);
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
    return data[x + y * width];
}

const vector<unsigned char> &Image::getData() const {
    return data;
}

const QString &Image::getName() const {
    return name;
}

Image Image::fromDouble(vector<double> data, int width, int height) {
    Image image;
    image.width = width;
    image.height = height;
    image.data = vector<unsigned char>(width * height);
    for (int i = 0; i < width * height; i++) {
        image.data[i] = (unsigned char)data[i];
    }
    return image;
}

void Image::saveToFile(const QString &fileName) {
    QImage qImage{&data[0], width, height, QImage::Format_Grayscale8};
    qImage.save("resources/out/" + fileName);
}
