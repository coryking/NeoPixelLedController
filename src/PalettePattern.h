//
// Created by Cory King on 1/28/17.
//

#ifndef NEOPIXELLEDCONTROLLER_PALETTEPATTERN_H
#define NEOPIXELLEDCONTROLLER_PALETTEPATTERN_H


#include "AbstractPattern.h"

class PalettePattern : public AbstractPattern {
private:
    uint8_t  startIndex =0;
    void ChangePalettePeriodically();

    CRGBPalette16 currentPalette;
    TBlendType currentBlending;

    void SetupTotallyRandomPalette();

    void SetupBlackAndWhiteStripedPalette();

    void SetupPurpleAndGreenPalette();

    static TProgmemRGBPalette16 const myRedWhiteBluePalette_p;
public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time);

    PalettePattern(uint16 numLeds);

};


#endif //NEOPIXELLEDCONTROLLER_PALETTEPATTERN_H
