//
// Created by Cory King on 1/24/17.
//

#include "AbstractPattern.h"
#include <pixeltypes.h>

AbstractPattern::AbstractPattern() {
    _startTime = millis();
}

unsigned short AbstractPattern::getNumLeds() {
    return _numLeds;
}

AbstractPattern::AbstractPattern(uint16 numLeds) : AbstractPattern::AbstractPattern() {
    _numLeds=numLeds;
}

void AbstractPattern::resetRuntime() {
    _startTime = millis();
}

ulong AbstractPattern::getRuntime() {
    return millis() - _startTime;
}

bool AbstractPattern::canStop() {
    return getRuntime() >= getMinRuntime();
}
