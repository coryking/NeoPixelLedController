//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_CONFETTI_H
#define NEOPIXELLEDCONTROLLER_CONFETTI_H

#include <FastLED.h>
#include "AbstractPattern.h"


class Confetti : public AbstractPattern {
protected:
    uint8_t gHue = 0; // rotating "base color" used by many of the patterns
    CRGB * _buffer;
public:
    uint16_t readFrame(CRGB *buffer, ulong time);

    Confetti(uint16 numLeds);

    ~Confetti();
};


#endif //NEOPIXELLEDCONTROLLER_CONFETTI_H
