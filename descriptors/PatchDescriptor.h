//
// Created by mikhail on 17.05.2021.
//

#ifndef ITOI_PATCHDESCRIPTOR_H
#define ITOI_PATCHDESCRIPTOR_H

#include "Descriptor.h"

class PatchDescriptor : public Descriptor {
public:
    PatchDescriptor(DoubleImage &gradient, InterestingPoint point, int gridHalfSize, int cellHalfSize);
};


#endif //ITOI_PATCHDESCRIPTOR_H
