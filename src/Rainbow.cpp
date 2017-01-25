//
// Created by Cory King on 1/24/17.
//
#include <Arduino.h>
#include <FastLED.h>
#include "Rainbow.h"

uint16_t Rainbow::readFrame(CRGB *buffer, ulong time) {
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
    fill_rainbow( buffer, getNumLeds(), gHue, 7);
    return getNumLeds();
}

Rainbow::Rainbow(uint16 numLeds) : AbstractPattern(numLeds) {

}
