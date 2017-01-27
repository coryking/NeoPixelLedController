//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_ABSTRACTPATTERN_H
#define NEOPIXELLEDCONTROLLER_ABSTRACTPATTERN_H

#include <Arduino.h>
#include <FastLED.h>

#define DEFAULT_DURATION 45 * 1000

#define CORNER_1 38
#define CORNER_2 (38 + 95)

class AbstractPattern {
private:
    ulong _startTime;

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

    void resetRuntime();

    ulong getRuntime();
    /**
     * Determines if this object can be stopped (i.e. has this made it past minRunTime?)
     * @return returns true if you can stop this
     */
    bool canStop();

    /**
         * Get the minimum milliseconds this can run for
         * @return returns minimum milliseconds this can run for
         */
    virtual uint16_t getMinRuntime() {
        return DEFAULT_DURATION;
    }
};

#endif //NEOPIXELLEDCONTROLLER_ABSTRACTPATTERN_H
