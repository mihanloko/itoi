#include <QApplication>
#include <QDebug>
#include <QImage>
#include <fstream>
#include <iostream>
#include "image/Image.h"

using namespace std;

int main() {

    Image image("resources/cat.jpg");
    for (int i = 0; i < image.getWidth(); ++i) {
        cout << image(i, 0) * 1 << " ";
    }
    return 1;
}