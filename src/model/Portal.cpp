//
// Created by Florian on 27.11.17.
//

#include <HardwareSerial.h>
#include "Portal.h"

Portal::Portal(uint8_t id, uint8_t distance
) {
    this->id = id;
}

void Portal::update() {
    brightness.update();
}

void Portal::setBrightness(float value, bool easing) {
    if (easing)
        brightness.setTarget(value);
    else
        brightness.set(value);
}

float Portal::getBrightness() {
    return brightness.get();
}

uint8_t Portal::getId() {
    return id;
}

void Portal::turnOn(bool easing) {
    setBrightness(LUBOID_MAX_BRIGHTNESS, easing);
}

void Portal::turnOff(bool easing) {
    setBrightness(LUBOID_MIN_BRIGHTNESS, easing);
}
