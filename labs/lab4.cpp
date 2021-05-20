//
// Created by mikhail on 18.05.2021.
//

#include "lab4.h"
#include "../descriptors/PatchProcessor.h"

void lab4::run() {
    DoubleImage cat("cat.jpg");
    DoubleImage cat_contrast("cat_contrast.png");
    DoubleImage cat_moved("cat_moved.png");
    DoubleImage cat_contrast_moved("cat_contrast_moved.png");
    DoubleImage Lenna("Lenna.png");
    DoubleImage Lenna_moved("Lenna_moved.png");

    processPair(cat, cat, 4, 4, "cat_cat.png");
    processPair(cat, cat_contrast, 4, 6, "cat_cat_contrast.png");
    processPair(cat, cat_moved, 6, 4, "cat_cat_moved.png");
    processPair(cat, cat_contrast_moved, 6, 6, "cat_cat_contrast_moved.png");

    processPair(Lenna, Lenna_moved, 4, 4, "Lenna_Lenna_moved.png");
    processPair(Lenna, Lenna, 4, 4, "Lenna_Lenna.png");

}

void lab4::processPair(DoubleImage &a, DoubleImage& b, int gridHalfSize, int cellHalfSize, QString name) {
    auto matching = PatchProcessor::create(a, b, gridHalfSize, cellHalfSize);
    auto resultImage = DescriptorUtil::markMatching(a, b, matching);
    resultImage.save("resources/out/" + name);
}
