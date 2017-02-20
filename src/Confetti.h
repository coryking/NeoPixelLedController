//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_CONFETTI_H
#define NEOPIXELLEDCONTROLLER_CONFETTI_H

#include <FastLED.h>
#include "AbstractPattern.h"


class Confetti : public HuePattern {
public:
    uint16_t readFrame(CRGB *buffer, ulong time);

    Confetti(uint16 numLeds);
};


#endif //NEOPIXELLEDCONTROLLER_CONFETTI_H
