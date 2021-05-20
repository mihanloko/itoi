//
// Created by mikhail on 17.05.2021.
//

#include "MatchData.h"

MatchData::MatchData(vector<pair<InterestingPoint, InterestingPoint>> &pointsPairs, vector<Descriptor> &descriptorsA,
                     vector<Descriptor> &descriptorsB)
        : pointsPairs(pointsPairs), descriptorsA(descriptorsA), descriptorsB(descriptorsB) {}

vector<pair<InterestingPoint, InterestingPoint>> &MatchData::getPointsPairs() {
    return pointsPairs;
}

vector<Descriptor> &MatchData::getDescriptorsA() {
    return descriptorsA;
}

vector<Descriptor> &MatchData::getDescriptorsB() {
    return descriptorsB;
}
