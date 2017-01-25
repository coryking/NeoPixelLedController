//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_ABSTRACTPATTERN_H
#define NEOPIXELLEDCONTROLLER_ABSTRACTPATTERN_H

#include <Arduino.h>
#include <FastLED.h>

class AbstractPattern {
private:
    uint16 _numLeds;
    AbstractPattern();
public:

    /**
     * Read pixels from this AbstractPattern
     * @param buffer Buffer to read into
     * @param time Timestamp, in milliseconds, when this was called
     * @return Number of bytes read
     */
    virtual uint16_t readFrame(CRGB * buffer, ulong time) = 0;

    uint16 getNumLeds();

    AbstractPattern(uint16 numLeds);
};

#endif //NEOPIXELLEDCONTROLLER_ABSTRACTPATTERN_H
