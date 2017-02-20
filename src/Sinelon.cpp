//
// Created by Cory King on 1/24/17.
//

#include "Sinelon.h"

uint16_t Sinelon::readFrame(CRGB *buffer, ulong time) {
    HuePattern::readFrame(buffer, time);

    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy( buffer, getNumLeds(), 20);
    int pos = beatsin16(13,0,getNumLeds());
    buffer[pos] += CHSV( gHue, 255, 192);
    return getNumLeds();
}

Sinelon::Sinelon(uint16 numLeds) : HuePattern(numLeds) {

}

