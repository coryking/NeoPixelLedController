//
// Created by Cory King on 1/25/17.
//

#ifndef NEOPIXELLEDCONTROLLER_FIREONFIREESCAPE_H
#define NEOPIXELLEDCONTROLLER_FIREONFIREESCAPE_H


#include "AbstractPattern.h"
#include "FirePattern.h"

template <class T> class FireOnFireEscape : public AbstractPattern {
private:
    ReversablePattern* leftFire;
    ReversablePattern* leftFrontFire;
    ReversablePattern* rightFrontFire;
    ReversablePattern* rightFire;
public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time) {
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

    FireOnFireEscape(uint16 numLeds) : AbstractPattern(numLeds) {
                const uint16 middleLedCount = (CORNER_2 - CORNER_1) / 2;
                Serial.println(middleLedCount);
                leftFire = new T(CORNER_1, true);
                leftFrontFire = new T(middleLedCount, false);
                rightFrontFire = new T(middleLedCount, true);
                rightFire = new T(CORNER_1,false);
    }
};


#endif //NEOPIXELLEDCONTROLLER_FIREONFIREESCAPE_H
