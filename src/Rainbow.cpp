//
// Created by Cory King on 1/24/17.
//
#include <Arduino.h>
#include <FastLED.h>
#include "Rainbow.h"

uint16_t Rainbow::readFrame(CRGB *buffer, ulong time) {
    HuePattern::readFrame(buffer,time);
    fill_rainbow( buffer, getNumLeds(), gHue, 7);
    return getNumLeds();
}

Rainbow::Rainbow(uint16 numLeds) : HuePattern(numLeds) {

}
