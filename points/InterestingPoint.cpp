//
// Created by mikhail on 27.04.2021.
//

#include "InterestingPoint.h"

int InterestingPoint::getX() const {
    return x;
}

void InterestingPoint::setX(int x) {
    InterestingPoint::x = x;
}

int InterestingPoint::getY() const {
    return y;
}

void InterestingPoint::setY(int y) {
    InterestingPoint::y = y;
}

double InterestingPoint::getProbability() const {
    return probability;
}

void InterestingPoint::setProbability(double probability) {
    InterestingPoint::probability = probability;
}

InterestingPoint::InterestingPoint(int x, int y, double probability) : x(x), y(y), probability(probability) {}
