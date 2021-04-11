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

using namespace std;

class lab1 {
public:
    static void run();

    static void testSobelOper(const QString &imageName, BorderEffectAction &borderPolicy);

    static void testGauss(const QString &imageName, double sigma, BorderEffectAction &borderPolicy);
};


#endif //ITOI_LAB1_H
