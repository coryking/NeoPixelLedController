//
// Created by Cory King on 1/24/17.
//

#include "Confetti.h"

uint16_t Confetti::readFrame(CRGB *buffer, ulong time) {
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow

    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy( _buffer, getNumLeds(), 10);
    int pos = random16(getNumLeds());
    _buffer[pos] += CHSV( gHue + random8(64), 200, 255);

    memcpy(buffer, _buffer, sizeof(CRGB) * getNumLeds());
    return getNumLeds();
}

Confetti::Confetti(uint16 numLeds) : AbstractPattern(numLeds) {
    _buffer = (CRGB*)malloc(numLeds * sizeof(CRGB));
    gHue = random(0, 255);
}

Confetti::~Confetti() {
    free(_buffer);
}
