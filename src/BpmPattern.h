//
// Created by Cory King on 1/28/17.
//

#ifndef NEOPIXELLEDCONTROLLER_BPMPATTERN_H
#define NEOPIXELLEDCONTROLLER_BPMPATTERN_H

#include <Arduino.h>
#include <FastLED.h>
#include "AbstractPattern.h"

#define INVERSE_WIDTH 10

class BpmPattern : public HuePattern {
public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time) {

        HuePattern::readFrame(buffer,time);
        uint8_t BeatsPerMinute = 62;
        CRGBPalette16 palette = CloudColors_p;
        uint8_t beat = beatsin8( BeatsPerMinute, 191, 255);

        for( int i = 0; i < getNumLeds(); i++) { //9948
            buffer[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*INVERSE_WIDTH));
        }
    }

    BpmPattern(uint16 numLeds) : HuePattern(numLeds) {}
};

#endif //NEOPIXELLEDCONTROLLER_BPMPATTERN_H
