//
// Created by mikhail on 18.04.2021.
//

#include "Octave.h"


vector<OctaveElement> Octave::getElements() const {
    return elements;
}

void Octave::addElement(const OctaveElement& element) {
    elements.push_back(element);
}

OctaveElement Octave::getLast() {
    return elements.back();
}

