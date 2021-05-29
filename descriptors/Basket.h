//
// Created by mikhail on 25.05.2021.
//

#ifndef ITOI_BASKET_H
#define ITOI_BASKET_H

#include <vector>
#include <cmath>

using namespace std;

class Basket {
protected:
    static inline double PI2 = 2 * M_PI;
    vector<double> basket;
    int size;
    double step;
public:
    Basket(int size = 32);

    void add(double angle, double value);

    static double normalize(double angle);

    vector<double> &getBasket();

    vector<double> getHighestAngles();

    pair<int, double> getMaxAngle(int excludeIndex = -1, double min = numeric_limits<double>::min());

    static double interpolate(double x1, double y1, double x2, double y2, double x3, double y3);
};


#endif //ITOI_BASKET_H
