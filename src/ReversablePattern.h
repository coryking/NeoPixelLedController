//
// Created by Cory King on 1/28/17.
//

#ifndef NEOPIXELLEDCONTROLLER_REVERSABLEPATTERN_H
#define NEOPIXELLEDCONTROLLER_REVERSABLEPATTERN_H

#include <Arduino.h>
#include "AbstractPattern.h"

class ReversablePattern : public AbstractPattern {
protected:
    bool gReverseDirection;
public:
    ReversablePattern(uint16 numLeds, bool reverseDirection) : AbstractPattern(numLeds) {
        gReverseDirection = reverseDirection;
    }

};

#endif //NEOPIXELLEDCONTROLLER_REVERSABLEPATTERN_H
