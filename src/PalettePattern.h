//
// Created by Cory King on 1/28/17.
//

#ifndef NEOPIXELLEDCONTROLLER_PALETTEPATTERN_H
#define NEOPIXELLEDCONTROLLER_PALETTEPATTERN_H


#include "AbstractPattern.h"
#include "ReversablePattern.h"

class PalettePattern : public ReversablePattern {
private:
    uint8_t  startIndex =0;
    uint8_t lastSecond = 99;
    void ChangePalettePeriodically(ulong time);

    CRGBPalette16 currentPalette;
    TBlendType currentBlending;

    void SetupTotallyRandomPalette();

    void SetupBlackAndWhiteStripedPalette();

    void SetupPurpleAndGreenPalette();

    static TProgmemRGBPalette16 const myRedWhiteBluePalette_p;


public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time);

    PalettePattern(uint16 numLeds, bool reverseDirection);

};


#endif //NEOPIXELLEDCONTROLLER_PALETTEPATTERN_H
