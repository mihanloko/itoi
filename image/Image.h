//
// Created by mikhail on 13.02.2021.
//

#ifndef ITOI_IMAGE_H
#define ITOI_IMAGE_H

#include <memory>
#include <QImage>

using namespace std;


class Image {
private:
    int width, height;
    unique_ptr<unsigned char[]> data;

public:
    Image();

    Image(const QString& name);

    int getHeight() const;

    int getWidth() const;

    unsigned char &operator()(int x, int y);

    const unique_ptr<unsigned char[]> &getData() const;

};


#endif //ITOI_IMAGE_H
