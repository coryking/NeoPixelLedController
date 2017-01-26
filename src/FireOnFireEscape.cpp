//
// Created by Cory King on 1/25/17.
//

#include "FireOnFireEscape.h"

uint16_t FireOnFireEscape::readFrame(CRGB *buffer, ulong time) {
    const uint16 middleLedCount = (CORNER_2 - CORNER_1) / 2;
    CRGB* bufferPos = buffer;
    leftFire->readFrame(bufferPos, time);

    bufferPos = buffer + CORNER_1;
    leftFrontFire->readFrame(bufferPos, time);

    bufferPos = buffer + (CORNER_1 + middleLedCount + 1);
    rightFrontFire->readFrame(bufferPos, time);

    bufferPos = buffer + getNumLeds() - CORNER_1;
    rightFire->readFrame(bufferPos, time);
    return getNumLeds();
}

FireOnFireEscape::FireOnFireEscape(uint16 numLeds) : AbstractPattern(numLeds) {
    const uint16 middleLedCount = (CORNER_2 - CORNER_1) / 2;
    Serial.println(middleLedCount);
    leftFire = new FirePattern(CORNER_1, true);
    leftFrontFire = new FirePattern(middleLedCount, false);
    rightFrontFire = new FirePattern(middleLedCount, true);
    rightFire = new FirePattern(CORNER_1,false);

}
