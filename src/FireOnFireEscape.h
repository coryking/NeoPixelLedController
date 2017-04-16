//
// Created by Cory King on 1/25/17.
//

#ifndef NEOPIXELLEDCONTROLLER_FIREONFIREESCAPE_H
#define NEOPIXELLEDCONTROLLER_FIREONFIREESCAPE_H


#include <vector>
#include "AbstractPattern.h"
#include "FirePattern.h"

typedef struct {
    AbstractPattern* pattern;
    uint16 offset;
    uint16 length;

} LightString;

template <class T> class FireOnFireEscape : public AbstractPattern {
private:
    //std::vector<LightString> _lightStrings;
    ReversablePattern* bottomFire;
    ReversablePattern* leftFire;
    ReversablePattern* leftFrontFire;
    ReversablePattern* rightFrontFire;
    ReversablePattern* rightFire;
public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time) {
        /* for (auto & element : _lightStrings) {
            CRGB* bufferPos = buffer + element.offset;
            element.pattern->readFrame(bufferPos, time);
        }

        return getNumLeds(); */
        const uint16 middleLedCount = (CORNER_2 - CORNER_1) / 2;
        CRGB* bufferPos = buffer;
        bottomFire->readFrame(bufferPos, time);

        bufferPos = buffer + FIRE_ESCAPE_OFFSET;
        leftFire->readFrame(bufferPos, time);

        bufferPos = buffer + CORNER_1;
        leftFrontFire->readFrame(bufferPos, time);


        bufferPos = buffer + (CORNER_1 + middleLedCount + 1);
        rightFrontFire->readFrame(bufferPos, time);

        bufferPos = buffer + CORNER_2;
        rightFire->readFrame(bufferPos, time);
        return getNumLeds();

    }

    FireOnFireEscape(uint16 numLeds) : AbstractPattern(numLeds) {
        const uint16 middleLedCount = (CORNER_2 - CORNER_1) / 2;
        Serial.println(middleLedCount);
//        this->_lightStrings.push_back({new T(CORNER_1, true), 0, CORNER_1});
//        this->_lightStrings.push_back({new T(middleLedCount, false), CORNER_1, middleLedCount});
//        this->_lightStrings.push_back({new T(middleLedCount, true), CORNER_1 + middleLedCount  +1, middleLedCount});
//        this->_lightStrings.push_back({new T(CORNER_1, false),  CORNER_2, CORNER_1});
//
        bottomFire = new T(FIRE_ESCAPE_OFFSET, false);
        leftFire = new T(CORNER_1_LENGTH, true);
        leftFrontFire = new T(middleLedCount+1, false);
        rightFrontFire = new T(middleLedCount, true);
        rightFire = new T(CORNER_1_LENGTH,false);
    }
};


#endif //NEOPIXELLEDCONTROLLER_FIREONFIREESCAPE_H
