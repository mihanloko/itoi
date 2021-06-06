//
// Created by mikhail on 17.05.2021.
//

#include "Descriptor.h"


void Descriptor::normalize() {
    double sum = 0;
    for (double d: descriptor) {
        sum += d;
    }
    if (abs(sum) < 0.001)
        return;
    vector<double> normalized(descriptor.size());
    for (int i = 0; i < descriptor.size(); i++) {
        normalized[i] = descriptor[i] / sum;
    }
    setDescriptor(normalized);
}

double Descriptor::distance(Descriptor &firstDescriptor, Descriptor &secondDescriptor) {
    auto descA = firstDescriptor.getDescriptor();
    auto descB = secondDescriptor.getDescriptor();
    double sum = 0;
    for (int i = 0; i < descA.size(); i++) {
        sum += (descA[i] - descB[i]) * (descA[i] - descB[i]);
    }
    return sqrt(sum);
}

vector<double> &Descriptor::getDescriptor() {
    return descriptor;
}

void Descriptor::setDescriptor(vector<double> newDescriptor) {
    Descriptor::descriptor = newDescriptor;
}

Descriptor::Descriptor(InterestingPoint point) : point(point) {

}

const InterestingPoint &Descriptor::getPoint() const {
    return point;
}

void Descriptor::setPoint(const InterestingPoint &point) {
    Descriptor::point = point;
}
