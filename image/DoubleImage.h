//
// Created by mikhail on 13.02.2021.
//

#ifndef ITOI_DOUBLEIMAGE_H
#define ITOI_DOUBLEIMAGE_H

#include <memory>
#include <QImage>
#include "Image.h"

using namespace std;

class DoubleImage {
private:
    int width, height;
    unique_ptr<double[]> data;

public:
    DoubleImage();

    DoubleImage(const QString& name);

    DoubleImage(const Image& image);

    int getHeight() const;

    int getWidth() const;

    double &operator()(int x, int y);
};


#endif //ITOI_DOUBLEIMAGE_H
