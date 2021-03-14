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
    vector<unsigned char > data;
    QString name;

public:
    Image();

    Image(const QString& name);

    int getHeight() const;

    int getWidth() const;

    unsigned char &operator()(int x, int y);

    const vector<unsigned char> &getData() const;

    const QString &getName() const;

};


#endif //ITOI_IMAGE_H
