//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_SINELON_H
#define NEOPIXELLEDCONTROLLER_SINELON_H

#include <FastLED.h>
#include "AbstractPattern.h"

class Sinelon : public AbstractPattern {
protected:
    uint8_t gHue = 0; // rotating "base color" used by many of the patterns
    CRGB* _buffer;

public:
    uint16_t readFrame(CRGB *buffer, ulong time);

    Sinelon(uint16 numLeds);

    ~Sinelon();
};


#endif //NEOPIXELLEDCONTROLLER_SINELON_H
