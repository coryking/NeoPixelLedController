//
// Created by Cory King on 1/25/17.
//

#include "TestPattern.h"

uint16_t TestPattern::readFrame(CRGB *buffer, ulong time) {
    static int pattern = 0;

    EVERY_N_SECONDS(2) {
        pattern++;
    }
    switch(pattern % 5) {
        case 0:
            fill_solid(buffer, getNumLeds(), CRGB::Black);

            buffer[0] = CRGB::White;
            buffer[CORNER_1 - 1] = CRGB::White;
            buffer[CORNER_1] = CRGB::White;
            buffer[CORNER_2 - 1] = CRGB::White;
            buffer[CORNER_2] = CRGB::White;
            buffer[getNumLeds() - 1] = CRGB::White;
            break;
        case 1:
            fill_solid(buffer,getNumLeds(), CRGB::Red);
            break;
        case 2:
            fill_solid(buffer, getNumLeds(), CRGB::Green);
            break;
        case 3:
            fill_solid(buffer,getNumLeds(), CRGB::Blue);
            break;
        case 4:
            fill_solid(buffer,getNumLeds(), CRGB::White);
            break;
        case 5:
            fill_solid(buffer,getNumLeds(), CRGB::Gray);
            break;
    }

}

TestPattern::TestPattern(uint16 numLeds) : AbstractPattern(numLeds) {

}
