//
// Created by Cory King on 1/25/17.
//

#include "FirePattern.h"

uint16_t FirePattern::readFrame(CRGB *buffer, ulong time) {
    this->onReadFrame();

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
        byte the_heat = heat[j];
        CRGB color = getColorFromHeat(the_heat);
        int pixelnumber;
        if( gReverseDirection ) {
            pixelnumber = (getNumLeds()-1) - j;
        } else {
            pixelnumber = j;
        }
        buffer[pixelnumber] = color;
    }
}

CRGB FirePattern::getColorFromHeat(byte the_heat) const {
    CRGB color = HeatColor(the_heat );
    return color;
}


FirePattern::FirePattern(uint16 numLeds, bool reverseDirection) : ReversablePattern(numLeds, reverseDirection) {
    heat = (byte *) malloc(getNumLeds() * sizeof(byte));

}
FirePattern::~FirePattern() {
    free(heat);
}

RainbowFirePattern::RainbowFirePattern(uint16 numLeds, bool reverseDirection) : FirePattern(numLeds,
                                                                                                  reverseDirection) {
    gPal = HeatColors_p;
}

CRGB RainbowFirePattern::getColorFromHeat(byte the_heat) const {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte colorindex = scale8( the_heat, 240);
    return ColorFromPalette( gPal, colorindex);
}

void RainbowFirePattern::onReadFrame() {
    FirePattern::onReadFrame();

    EVERY_N_MILLISECONDS(20) {
        gHue++;
        random16_add_entropy( random(0,10));
        CRGB darkcolor  = CHSV(this->gHue,255,192); // pure hue, three-quarters brightness
        CRGB lightcolor = CHSV(this->gHue,128,255); // half 'whitened', full brightness
        gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);

    }
}
