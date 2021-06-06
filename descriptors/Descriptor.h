//
// Created by mikhail on 17.05.2021.
//

#ifndef ITOI_DESCRIPTOR_H
#define ITOI_DESCRIPTOR_H


#include "../image/DoubleImage.h"
#include "../points/InterestingPoint.h"

class Descriptor {
protected:
    vector<double> descriptor;
    InterestingPoint point;
public:

    Descriptor(InterestingPoint point);
    const InterestingPoint &getPoint() const;

    vector<double> &getDescriptor();

    void setDescriptor(vector<double> newDescriptor);

    void normalize();

    static double distance(Descriptor& firstDescriptor, Descriptor& secondDescriptor);

    void setPoint(const InterestingPoint &point);
};


#endif //ITOI_DESCRIPTOR_H
