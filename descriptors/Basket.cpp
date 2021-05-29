//
// Created by mikhail on 25.05.2021.
//

#include "Basket.h"


Basket::Basket(int size) : size(size) {
    basket.resize(size);
    step = PI2 / (double) size;
}

void Basket::add(double angle, double value) {
    angle = normalize(angle) / step;
    int i = (int) angle;
    double center = i + 0.5;
    double weight = abs(center - angle);
    int neighbourI = (i + 1) % size;
    if (angle <= center) {
        neighbourI = (i - 1 + size) % size;
    }

    basket[i] += weight * value;
    basket[neighbourI] += (1 - weight) * value;
}

double Basket::normalize(double angle) {
    while (angle < 0)
        angle += PI2;
    while (angle >= PI2)
        angle -= PI2;
    return angle;
}

vector<double> &Basket::getBasket() {
    return basket;
}