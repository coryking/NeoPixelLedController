//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_RAINBOW_H
#define NEOPIXELLEDCONTROLLER_RAINBOW_H

#include "AbstractPattern.h"

class Rainbow: public HuePattern {
public:
    Rainbow(uint16 numLeds);

    virtual uint16_t readFrame(CRGB *buffer, ulong time);
};

#endif //NEOPIXELLEDCONTROLLER_RAINBOW_H
