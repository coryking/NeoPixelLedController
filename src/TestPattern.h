//
// Created by Cory King on 1/25/17.
//

#ifndef NEOPIXELLEDCONTROLLER_TESTPATTERN_H
#define NEOPIXELLEDCONTROLLER_TESTPATTERN_H

#include <FastLED.h>
#include "AbstractPattern.h"

#define TEST_RUNTIME 10 * 1000

class TestPattern : public AbstractPattern {
private:
    virtual uint16_t getMinRuntime() {
        return TEST_RUNTIME;
    }
public:
    TestPattern(uint16 numLeds);

    virtual uint16_t readFrame(CRGB *buffer, ulong time);
};


#endif //NEOPIXELLEDCONTROLLER_TESTPATTERN_H
