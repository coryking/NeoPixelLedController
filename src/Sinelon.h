//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_SINELON_H
#define NEOPIXELLEDCONTROLLER_SINELON_H

#include <FastLED.h>
#include "AbstractPattern.h"

class Sinelon : public HuePattern {
public:
    uint16_t readFrame(CRGB *buffer, ulong time);

    Sinelon(uint16 numLeds);
};


#endif //NEOPIXELLEDCONTROLLER_SINELON_H
