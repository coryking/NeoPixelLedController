//
// Created by Cory King on 1/25/17.
//

#include "FirePattern.h"

uint16_t FirePattern::readFrame(CRGB *buffer, ulong time) {

    // Step 1.  Cool down every cell a little
    for( int i = 0; i < getNumLeds(); i++) {
        heat[i] = qsub8( heat[i],  random8(0, ((FOFE_COOLING * 10) / getNumLeds()) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= getNumLeds() - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < FOFE_SPARKING ) {
        int y = random8(7);
        heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < getNumLeds(); j++) {
        CRGB color = HeatColor( heat[j]);
        int pixelnumber;
        if( gReverseDirection ) {
            pixelnumber = (getNumLeds()-1) - j;
        } else {
            pixelnumber = j;
        }
        buffer[pixelnumber] = color;
    }
}

FirePattern::FirePattern(uint16 numLeds) : FirePattern::FirePattern(numLeds, false) {
}

FirePattern::FirePattern(uint16 numLeds, bool reverseDirection) : AbstractPattern(numLeds) {
    this->gReverseDirection = reverseDirection;
    heat = (byte *) malloc(getNumLeds() * sizeof(byte));

}
FirePattern::~FirePattern() {
    free(heat);
}
