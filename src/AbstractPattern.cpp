//
// Created by Cory King on 1/24/17.
//

#include "AbstractPattern.h"
#include <pixeltypes.h>

AbstractPattern::AbstractPattern() {

}

unsigned short AbstractPattern::getNumLeds() {
    return _numLeds;
}

AbstractPattern::AbstractPattern(uint16 numLeds) {
    _numLeds=numLeds;
}
