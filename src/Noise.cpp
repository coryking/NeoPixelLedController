//
// Created by Cory King on 1/24/17.
//

#include <FastLED.h>
#include "Noise.h"

uint16_t Noise::readFrame(CRGB *buffer, ulong time) {
    EVERY_N_MILLISECONDS(10) {
        nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);  // Blend towards the target palette
        for(int i = 0; i < getNumLeds(); i++) {                                      // Just ONE loop to fill up the LED array as all of the pixels change.
            uint8_t index = inoise8(i*scale, dist+i*scale) % 255;                  // Get a value from the noise function. I'm using both x and y axis.
            buffer[i] = ColorFromPalette(currentPalette, index, 255, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
        }
        dist += beatsin8(10,1, 4);                                               // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
        // In some sketches, I've used millis() instead of an incremented counter. Works a treat.
    }

    EVERY_N_SECONDS(5) {             // Change the target palette to a random one every 5 seconds.
        targetPalette = CRGBPalette16(
                CHSV(random8(), 255, random8(128,255)),
                CHSV(random8(), 255, random8(128,255)),
                CHSV(random8(), 192, random8(128,255)),
                CHSV(random8(), 255, random8(128,255)));
    }
}

Noise::Noise(uint16 numLeds) : AbstractPattern(numLeds) {
    currentPalette = CRGBPalette16(CRGB::Black);
    targetPalette = OceanColors_p;
    dist = random16(12345);
}

void Noise::resetRuntime() {
    AbstractPattern::resetRuntime();
    minRuntime = DEFAULT_DURATION + random(0, DEFAULT_DURATION * 10);
}
