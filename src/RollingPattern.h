//
// Created by Cory King on 1/28/17.
//

#ifndef NEOPIXELLEDCONTROLLER_ROLLINGPATTERN_H
#define NEOPIXELLEDCONTROLLER_ROLLINGPATTERN_H

#include <Arduino.h>
#include <FastLED.h>
#include "AbstractPattern.h"

#define INVERSE_WIDTH 10

class RollingPattern : public HuePattern {
protected:
    CRGBPalette16 palette;
    uint8_t BeatsPerMinute = 62;

public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time) {

        HuePattern::readFrame(buffer,time);

        uint8_t beat = beatsin8( BeatsPerMinute, 220, 255);
        for( int i = 0; i < getNumLeds(); i++) { //9948
            uint8_t brightness = 255; // abs(127 - (beat - gHue + (i * INVERSE_WIDTH)) % 255);

            buffer[i] = ColorFromPalette(palette, gHue+(i), brightness);
        }
    }

    virtual void resetRuntime() {
        HuePattern::resetRuntime();
        BeatsPerMinute = random(50, 80);
    }

    RollingPattern(uint16 numLeds, CRGBPalette16 thePallete) : HuePattern(numLeds) {palette = thePallete;}
};

#endif //NEOPIXELLEDCONTROLLER_ROLLINGPATTERN_H
