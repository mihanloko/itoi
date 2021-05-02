//
// Created by mikhail on 01.05.2021.
//

#include "lab3.h"

void lab3::run() {
    Moravec moravec;
    Harris harris;

    DoubleImage cat("cat.jpg");
    DoubleImage wall("wall.jpg");

    harris.makeHarris(cat);
    harris.makeHarris(wall);

    moravec.makeMoravec(cat);
    moravec.makeMoravec(wall);

    DoubleImage cat_noised("cat_noised.jpg");
    DoubleImage cat_rotated("cat_rotated.png");
    DoubleImage cat_contrast("cat_contrast.png");

    moravec.makeMoravec(cat_contrast);
    moravec.makeMoravec(cat_rotated);
    moravec.makeMoravec(cat_noised);

    harris.makeHarris(cat_contrast);
    harris.makeHarris(cat_rotated);
    harris.makeHarris(cat_noised);
}
