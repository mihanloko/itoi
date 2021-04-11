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
    vector<double> data;
    QString name;

public:
    DoubleImage();

    DoubleImage(const QString& name);

    DoubleImage(const Image& image);

    DoubleImage normalize(float diff = 1.0);

    DoubleImage(const vector<double>& data, int height, int width);

    int getHeight() const;

    int getWidth() const;

    double &operator()(int x, int y);

    const QString &getName() const;

    DoubleImage(int width, int height);

    long size();

    vector<double>& getData();
};


#endif //ITOI_DOUBLEIMAGE_H
