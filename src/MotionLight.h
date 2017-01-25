//
// Created by Cory King on 1/24/17.
//

#ifndef NEOPIXELLEDCONTROLLER_MOTIONLIGHT_H
#define NEOPIXELLEDCONTROLLER_MOTIONLIGHT_H

#include <FastLED.h>
#include "AbstractPattern.h"

enum Direction {
    Forward = 1,
    Backward = -1
};

class MotionLight : public AbstractPattern {
private:
    Direction _dir = Direction::Forward;
    uint16_t location;

public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time);
    Direction getDirection();
    Direction setDirection(Direction dir);
    MotionLight(uint16 numLeds);

    uint16_t getPosition(int16_t offset);
};


#endif //NEOPIXELLEDCONTROLLER_MOTIONLIGHT_H
