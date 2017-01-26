//
// Created by Cory King on 1/25/17.
//

#ifndef NEOPIXELLEDCONTROLLER_FIREONFIREESCAPE_H
#define NEOPIXELLEDCONTROLLER_FIREONFIREESCAPE_H


#include "AbstractPattern.h"
#include "FirePattern.h"

class FireOnFireEscape : public AbstractPattern {
private:
    FirePattern* leftFire;
    FirePattern* leftFrontFire;
    FirePattern* rightFrontFire;
    FirePattern* rightFire;
public:
    virtual uint16_t readFrame(CRGB *buffer, ulong time);

    FireOnFireEscape(uint16 numLeds);
};


#endif //NEOPIXELLEDCONTROLLER_FIREONFIREESCAPE_H
