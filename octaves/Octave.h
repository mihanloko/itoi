//
// Created by mikhail on 18.04.2021.
//

#ifndef ITOI_OCTAVE_H
#define ITOI_OCTAVE_H

#include <vector>
#include "OctaveElement.h"

using namespace std;

class Octave {
private:
    vector<OctaveElement> elements;
public:
    vector<OctaveElement> getElements() const;
    void addElement(const OctaveElement& element);
    OctaveElement getLast();
};


#endif //ITOI_OCTAVE_H
