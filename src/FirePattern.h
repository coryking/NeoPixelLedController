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
protected:
    virtual CRGB getColorFromHeat(byte the_heat) const;
    virtual void onReadFrame() {}
public:
    FirePattern(uint16 numLeds, bool reverseDirection);

    virtual ~FirePattern();

    virtual uint16_t readFrame(CRGB *buffer, ulong time);

};

class RainbowFirePattern : public  FirePattern {
private:
    uint8_t gHue = 0; // rotating "base color" used by many of the patterns
    CRGBPalette16 gPal;

public:
    RainbowFirePattern(uint16 numLeds, bool reverseDirection);

protected:
    virtual CRGB getColorFromHeat(byte the_heat) const;

    virtual void onReadFrame();
};


#endif //NEOPIXELLEDCONTROLLER_FIREPATTERN_H
