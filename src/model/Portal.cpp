//
// Created by Florian on 27.11.17.
//

#include <HardwareSerial.h>
#include "Portal.h"

Portal::Portal(unsigned short id) {
    this->id = id;
    this->led = new RGBLed();
}

void Portal::update() {
    led->update();
}

unsigned short Portal::getId() {
    return id;
}

void Portal::turnOn() {
    led->turnOn(true);
}

void Portal::turnOff() {
    led->turnOff(true);
}

RGBLedPtr Portal::getLed() {
    return led;
}

bool Portal::isActivated() const {
    return activated;
}

void Portal::setActivated(bool activated) {
    Portal::activated = activated;
}
