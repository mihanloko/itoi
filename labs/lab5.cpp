//
// Created by mikhail on 06.06.2021.
//

#include "lab5.h"

void lab5::run() {
    DoubleImage cat("cat.jpg");
    DoubleImage catr("cat-r.jpg");
    DoubleImage catr2("cat-r2.jpg");
    DoubleImage cat_contrast("cat_contrast.jpg");
    DoubleImage cat_moved("cat_moved.jpg");
    DoubleImage Lenna("Lenna.png");
    DoubleImage Lennar("Lenna_r.png");
    DoubleImage Lennar2("Lenna_r2.png");
    DoubleImage Lenna_contrast("Lenna_contrast.png");
    DoubleImage Lenna_moved("Lenna_moved.png");
    DoubleImage cat2("cat2.jpg");
    DoubleImage cat2rotated("cat2-rotated.jpg");
    DoubleImage mi("mimimi.jpg");
    DoubleImage mirotated("mimimi-side.jpg");
    DoubleImage mirotated2("mimimi-r2.jpg");

    processPair(cat2, cat2rotated, 4, 4, "cat2.png", 8);
    processPair(mi, mirotated, 4, 4, "mi.png", 8);
    processPair(mi, mirotated2, 4, 4, "mi2.png", 8);

    processPair(Lenna, Lennar, 4, 4, "Lennar1.png", 8);
    processPair(Lenna, Lennar2, 4, 4, "Lennar2.png", 8);
    processPair(cat, catr, 4, 4, "catr.png", 8);
    processPair(cat, catr2, 4, 4, "catr2.png", 8);
}

void lab5::processPair(DoubleImage &a, DoubleImage& b, int gridHalfSize, int cellHalfSize, QString name, int basketSize) {
    auto matching = RotationInvariantProcessor::create(a, b, gridHalfSize, cellHalfSize, basketSize);
    auto resultImage = DescriptorUtil::markMatching(a, b, matching);
    resultImage.save("resources/out/" + name);
}
