//
// Created by mikhail on 17.05.2021.
//

#include "PatchProcessor.h"

MatchData PatchProcessor::create(DoubleImage &first, DoubleImage &second, int gridHalfSize, int cellHalfSize) {
    auto gradientFirst = DescriptorUtil::getGradient(first, true);
    auto gradientSecond = DescriptorUtil::getGradient(second, true);

    auto harris = Harris();

    auto pointsFirst = harris.makeHarris(first);
    auto pointsSecond = harris.makeHarris(second);

    auto descriptorsFirst = getDescriptors(gradientFirst, pointsFirst, gridHalfSize, cellHalfSize);
    auto descriptorsSecond = getDescriptors(gradientSecond, pointsSecond, gridHalfSize, cellHalfSize);

    return DescriptorUtil::match(descriptorsFirst, descriptorsSecond);
}

vector<Descriptor> PatchProcessor::getDescriptors(DoubleImage &gradient, vector<InterestingPoint> &interestingPoints, int gridHalfSize,int cellHalfSize) {
    vector<Descriptor> result;
    result.reserve(interestingPoints.size());
    for (const auto &item : interestingPoints) {
        result.push_back(PatchDescriptor(gradient, item, gridHalfSize, cellHalfSize));
    }
    return result;
}
