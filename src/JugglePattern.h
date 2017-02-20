//
// Created by Cory King on 1/28/17.
//

#ifndef NEOPIXELLEDCONTROLLER_JUGGLEPATTERN_H
#define NEOPIXELLEDCONTROLLER_JUGGLEPATTERN_H

#include <Arduino.h>
#include <FastLED.h>
#include "AbstractPattern.h"

class JugglePattern : public AbstractPattern {
public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time) {
        fadeToBlackBy( buffer, getNumLeds(), 20);
        byte dothue = 0;
        for( int i = 0; i < 8; i++) {
            buffer[beatsin16(i+7,0,getNumLeds())] |= CHSV(dothue, 200, 255);
            dothue += 32;
        }
    }

    JugglePattern(uint16 numLeds) : AbstractPattern(numLeds) {

    }
};


#endif //NEOPIXELLEDCONTROLLER_JUGGLEPATTERN_H
