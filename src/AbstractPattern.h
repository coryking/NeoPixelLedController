//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_ABSTRACTPATTERN_H
#define NEOPIXELLEDCONTROLLER_ABSTRACTPATTERN_H

#include <Arduino.h>
#include <FastLED.h>

#define DEFAULT_DURATION 3 * 60 * 1000

#define FIRST_LED_OFFSET 1
#define FIRST_LED_LENGTH 56
#define WEIRD_PART_OFFSET (FIRST_LED_LENGTH + FIRST_LED_OFFSET)
#define WEIRD_PART_LENGTH 9
#define VERTICAL_PART_OFFSET (WEIRD_PART_OFFSET + WEIRD_PART_LENGTH)
#define VERTICAL_LENGTH 36

#define FIRE_ESCAPE_OFFSET (VERTICAL_PART_OFFSET + VERTICAL_LENGTH)
#define CORNER_1_LENGTH 38
#define CORNER_1 (FIRE_ESCAPE_OFFSET + CORNER_1_LENGTH)

#define MIDDLE_LENGTH 95

#define CORNER_2 (MIDDLE_LENGTH + CORNER_1)

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

    virtual void resetRuntime();

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

class HuePattern : public AbstractPattern {
protected:
    uint8_t gHue = 0; // rotating "base color" used by many of the patterns
    uint8_t gHueDelay = 20;
public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time) {
        EVERY_N_MILLISECONDS(gHueDelay) {
            gHue++;
        }
    }

    virtual void resetRuntime() {
        gHueDelay = random(15, 50);

        AbstractPattern::resetRuntime();
    }
    HuePattern(uint16 numLeds) : AbstractPattern(numLeds) {
        gHue = random(0,255);
        gHueDelay = random(15, 50);
    }
};

#endif //NEOPIXELLEDCONTROLLER_ABSTRACTPATTERN_H
