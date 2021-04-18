//
// Created by mikhail on 13.02.2021.
//

#include "DoubleImage.h"

DoubleImage::DoubleImage() {

}

DoubleImage::DoubleImage(const QString& name) {
    this->name = name;
    QImage image("resources/in/" + name);
    height = image.height();
    width = image.width();
    data = vector<double>(width * height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            (*this)(x, y) = (0.229 * image.pixelColor(x, y).red() + 0.587 * image.pixelColor(x, y).green() + 0.114 * image.pixelColor(x, y).blue()) / 255.;
        }
    }
}

int DoubleImage::getHeight() const {
    return height;
}

int DoubleImage::getWidth() const {
    return width;
}

double &DoubleImage::operator()(int x, int y) {
    return data[x + y * width];
}

DoubleImage::DoubleImage(const Image &image) {
    this->name = image.getName();
    width = image.getWidth();
    height = image.getHeight();
    data = vector<double>(width * height);
    auto oldData = image.getData();
    int min = oldData[0];
    int max = oldData[0];
    for (int i = 1; i < data.size(); i++) {
        if (min > data[i]) min = oldData[i];
        if (max < data[i]) max = oldData[i];
    }
    for (int i = 0; i < width * height; i++) {
        data[i] = (image.getData()[i] - min) * (1.0 - 0) / (max - min) + 0;
    }
}

const QString &DoubleImage::getName() const {
    return name;
}

DoubleImage::DoubleImage(const vector<double> &data, int height, int width) {
    this->width = width;
    this->height = height;
    this->data = vector<double>(data.size());
    for (int i = 0; i < data.size(); i++)
        this->data[i] = data[i];
}

DoubleImage::DoubleImage(int width, int height) {
    this->width = width;
    this->height = height;
    this->data = vector<double>(width * height, 0);
}

DoubleImage DoubleImage::normalize(float diff) {
    double max = data[0];
    double min = data[0];
    long size = width * height;
    for (int i = 0; i < size; i++) {
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
    }
    // normalizing
    auto res = vector<double>(size);
    for (int i = 0; i < size; i++) {
        res[i] = (data[i] - min) * (diff / (max - min));
    }
    return DoubleImage(res, height, width);
}

long DoubleImage::size() {
    return data.size();
}

vector<double> &DoubleImage::getData() {
    return data;
}

DoubleImage::DoubleImage(const DoubleImage &image) {
    width = image.getWidth();
    height = image.getHeight();
    data = vector<double>(width * height);
    for (int i = 0; i < size(); i++) {
        data[i] = image.data[i];
    }
}

