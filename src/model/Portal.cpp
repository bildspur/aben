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
    if (activated) {
        activatedTimeStamp = millis();
    }

    Portal::activated = activated;
}

void Portal::onlineStateReceived() {
    onlineTimeStamp = millis();
}

bool Portal::isOnline(unsigned long maxTimeSinceUpdate) {
    return (millis() - onlineTimeStamp) <= maxTimeSinceUpdate;
}

void Portal::updateActivation(unsigned long activationTime) {
    if (millis() - activatedTimeStamp >= activationTime && isActivated())
        setActivated(false);
}
