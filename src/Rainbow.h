//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_RAINBOW_H
#define NEOPIXELLEDCONTROLLER_RAINBOW_H

#include "AbstractPattern.h"

class Rainbow: public AbstractPattern {
public:
    Rainbow(uint16 numLeds);

    virtual uint16_t readFrame(CRGB *buffer, ulong time);

protected:
    uint8_t gHue = 0; // rotating "base color" used by many of the patterns

};

#endif //NEOPIXELLEDCONTROLLER_RAINBOW_H
