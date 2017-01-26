//
// Created by Cory King on 1/25/17.
//

#include "AnnounceHour.h"
#include <FastLED.h>

uint16_t AnnounceHour::readFrame(CRGB *buffer, ulong time) {

    static bool isblack = false;
    EVERY_N_SECONDS(1) {
        // Middle bar
        fill_solid(buffer + CORNER_1, CORNER_2 - CORNER_1, isblack ? CRGB::Black : CRGB::White);

        // Left bar
        fill_solid(buffer, CORNER_1, isblack ? CRGB::White : CRGB::Black);

        // Right bar
        fill_solid(buffer + CORNER_2, getNumLeds() - CORNER_2, isblack ? CRGB::White : CRGB::Black);

        isblack = !isblack;
    }
    return getNumLeds();
}

AnnounceHour::AnnounceHour(uint16 numLeds) : AbstractPattern(numLeds) {

}
