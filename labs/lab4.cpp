//
// Created by mikhail on 132.05.2021.
//

#include "lab4.h"
#include "../descriptors/HistogramCreator.h"

void lab4::run() {
    DoubleImage cat("cat.jpg");
    DoubleImage cat_contrast("cat_contrast.png");
    DoubleImage cat_moved("cat_moved.png");
    DoubleImage cat_contrast_moved("cat_contrast_moved.png");
    DoubleImage Lenna("Lenna.png");
    DoubleImage Lenna_moved("Lenna_moved.png");

    processPair(cat, cat, 8, 4, "cat_cat.png", 8, 32);
    processPair(cat, cat_contrast, 8, 4, "cat_cat_contrast.png", 8, 32);
    processPair(cat, cat_moved, 8, 4, "cat_cat_moved.png", 8, 32);
    processPair(cat, cat_contrast_moved, 8, 4, "cat_cat_contrast_moved.png", 8, 32);
    processPair(Lenna, Lenna_moved, 8, 4, "Lenna_Lenna_moved.png", 8, 32);
    processPair(Lenna, Lenna, 8, 4, "Lenna_Lenna.png", 8, 32);

}

void lab4::processPair(DoubleImage &a, DoubleImage& b, int gridHalfSize, int cellHalfSize, QString name, int basketSize,
                       int pointsCount) {
    auto matching = HistogramCreator::create(a, b, gridHalfSize, cellHalfSize, basketSize, pointsCount);
    auto resultImage = DescriptorUtil::markMatching(a, b, matching);
    resultImage.save("resources/out/" + name);
}
