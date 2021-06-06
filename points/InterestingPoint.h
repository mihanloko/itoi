//
// Created by mikhail on 27.04.2021.
//

#ifndef ITOI_INTERESTINGPOINT_H
#define ITOI_INTERESTINGPOINT_H

#include <cmath>

class InterestingPoint {
private:
    int x, y;
    double probability;
    double angle;
public:
    InterestingPoint(int x, int y, double probability);

    InterestingPoint(int x, int y, double probability, double angle);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    double getProbability() const;

    void setProbability(double probability);

    static double distance(InterestingPoint &a, InterestingPoint &b);

    double getAngle() const;
};


#endif //ITOI_INTERESTINGPOINT_H
