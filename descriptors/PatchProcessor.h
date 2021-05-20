//
// Created by mikhail on 17.05.2021.
//

#ifndef ITOI_PATCHPROCESSOR_H
#define ITOI_PATCHPROCESSOR_H


#include "../image/DoubleImage.h"
#include "MatchData.h"
#include "DescriptorUtil.h"
#include "../points/Harris.h"
#include "PatchDescriptor.h"

class PatchProcessor {
private:
    Harris harris;
public:
    static MatchData create(DoubleImage &first, DoubleImage &second, int gridHalfSize, int cellHalfSize);
    static vector<Descriptor> getDescriptors(DoubleImage &gradient, vector<InterestingPoint> &interestingPoints, int gridHalfSize, int cellHalfSize);
};


#endif //ITOI_PATCHPROCESSOR_H
