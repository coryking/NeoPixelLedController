//
// Created by Cory King on 1/25/17.
//

#ifndef NEOPIXELLEDCONTROLLER_FIREPATTERN_H
#define NEOPIXELLEDCONTROLLER_FIREPATTERN_H


#include "AbstractPattern.h"
#include "ReversablePattern.h"

#define FOFE_COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define FOFE_SPARKING 120


class FirePattern : public ReversablePattern {
private:
    byte* heat;
public:
    FirePattern(uint16 numLeds, bool reverseDirection);

    virtual ~FirePattern();

    virtual uint16_t readFrame(CRGB *buffer, ulong time);
};


#endif //NEOPIXELLEDCONTROLLER_FIREPATTERN_H
