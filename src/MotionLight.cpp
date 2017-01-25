//
// Created by Cory King on 1/24/17.
//

#include "MotionLight.h"

uint16_t MotionLight::readFrame(CRGB *buffer, ulong time) {
    EVERY_N_MILLISECONDS(20) {
        buffer[getPosition(-3)] = CRGB::Black;
        buffer[getPosition(-2)] = CRGB::DarkBlue;
        buffer[getPosition(-1)] = CRGB::Blue;
        buffer[getPosition(0)] = CRGB::LightBlue;
        location = location + getDirection();
        buffer[getPosition(0)] = CRGB::White;
    }

}

MotionLight::MotionLight(uint16 numLeds) : AbstractPattern(numLeds) {

}

Direction MotionLight::getDirection() {
    return _dir;
}

Direction MotionLight::setDirection(Direction dir) {
    if(dir==Forward) {
        location = 0;
    } else {
        location = getNumLeds() - 1;
    }
    _dir = dir;
    return Forward;
}

uint16_t MotionLight::getPosition(int16_t offset) {
    return (location + offset * getDirection()) % getNumLeds();
}