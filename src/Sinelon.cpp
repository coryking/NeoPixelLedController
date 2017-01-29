//
// Created by Cory King on 1/24/17.
//

#include "Sinelon.h"

uint16_t Sinelon::readFrame(CRGB *buffer, ulong time) {
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow

    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy( buffer, getNumLeds(), 20);
    int pos = beatsin16(13,0,getNumLeds());
    buffer[pos] += CHSV( gHue, 255, 192);
    return getNumLeds();
}

Sinelon::Sinelon(uint16 numLeds) : AbstractPattern(numLeds) {
}

