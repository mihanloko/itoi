//
// Created by mikhail on 27.04.2021.
//

#ifndef ITOI_INTERESTINGPOINT_H
#define ITOI_INTERESTINGPOINT_H


class InterestingPoint {
private:
    int x, y;
    double probability;
public:
    InterestingPoint(int x, int y, double probability);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    double getProbability() const;

    void setProbability(double probability);
};


#endif //ITOI_INTERESTINGPOINT_H
