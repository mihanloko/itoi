//
// Created by mikhail on 17.05.2021.
//

#ifndef ITOI_MATCHDATA_H
#define ITOI_MATCHDATA_H

#include <vector>
#include "../points/InterestingPoint.h"
#include "Descriptor.h"

using namespace std;

class MatchData {
private:
    vector<pair<InterestingPoint, InterestingPoint>> pointsPairs;
    vector<Descriptor> descriptorsA;
    vector<Descriptor> descriptorsB;
public:
    MatchData(vector<pair<InterestingPoint, InterestingPoint>> &pointsPairs, vector<Descriptor> &descriptorsA,
              vector<Descriptor> &descriptorsB);

    vector<pair<InterestingPoint, InterestingPoint>> &getPointsPairs() ;

    vector<Descriptor> &getDescriptorsA() ;

    vector<Descriptor> &getDescriptorsB() ;
};


#endif //ITOI_MATCHDATA_H
