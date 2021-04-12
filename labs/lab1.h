//
// Created by mikhail on 11.04.2021.
//

#ifndef ITOI_LAB1_H
#define ITOI_LAB1_H

#include <iostream>
#include <QString>
#include <cmath>

#include "../borders/CopyBorderEffect.h"
#include "../borders/MirrorBorderEffect.h"
#include "../borders/ZeroBorderEffect.h"
#include "../filters/FiltersImplementation.h"
#include "../filters/KernelFactory.h"

using namespace std;

class lab1 {
public:
    static void run();

    static void sobelOperatorTest(const QString &imageName, BorderEffectAction &borderEffectAction);

    static void gaussTest(const QString &imageName, double sigma, BorderEffectAction &borderEffectAction);
};


#endif //ITOI_LAB1_H
