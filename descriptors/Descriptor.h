//
// Created by mikhail on 17.05.2021.
//

#ifndef ITOI_DESCRIPTOR_H
#define ITOI_DESCRIPTOR_H


#include "../image/DoubleImage.h"
#include "../points/InterestingPoint.h"

class Descriptor {
protected:
    Descriptor(InterestingPoint point);

    vector<double> descriptor;
    InterestingPoint point;
public:
    const InterestingPoint &getPoint() const;

    const vector<double> &getDescriptor() const;

    void setDescriptor(vector<double> newDescriptor);

    void normalize();

    static double distance(Descriptor& firstDescriptor, Descriptor& secondDescriptor);
};


#endif //ITOI_DESCRIPTOR_H
