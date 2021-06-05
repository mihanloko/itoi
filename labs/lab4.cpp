//
// Created by mikhail on 132.05.2021.
//

#include "lab4.h"

void lab4::run() {
    DoubleImage cat("cat.jpg");
    DoubleImage cat_contrast("cat_contrast.jpg");
    DoubleImage cat_moved("cat_moved.jpg");
    DoubleImage Lenna("Lenna.png");
    DoubleImage Lenna_contrast("Lenna_contrast.png");
    DoubleImage Lenna_moved("Lenna_moved.png");

    processPair(cat, cat_contrast, 8, 4, "cat_contrast.png", 8);
    processPair(cat, cat_moved, 8, 4, "cat_moved.png", 8);
    processPair(Lenna, Lenna_contrast, 8, 4, "Lenna_contrast.png", 8);
    processPair(Lenna, Lenna_moved, 8, 4, "Lenna_moved.png", 8);
    processPair(cat, cat, 4, 4, "cat.png", 8);
    processPair(Lenna, Lenna, 8, 4, "Lenna.png", 8);

}

void lab4::processPair(DoubleImage &a, DoubleImage& b, int gridHalfSize, int cellHalfSize, QString name, int basketSize) {
    auto matching = HistogramProcessor::create(a, b, gridHalfSize, cellHalfSize, basketSize);
    auto resultImage = DescriptorUtil::markMatching(a, b, matching);
    resultImage.save("resources/out/" + name);
}
