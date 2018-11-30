//
// Created by Florian on 27.11.17.
//

#include <HardwareSerial.h>
#include "Portal.h"

Portal::Portal(unsigned short id) {
    this->id = id;
}

void Portal::update() {
}

unsigned short Portal::getId() {
    return id;
}

bool Portal::isActivated() const {
    return activated;
}

void Portal::setActivated(bool activated) {
    if (activated)
        activatedTimeStamp = millis();

    Portal::activated = activated;
}
