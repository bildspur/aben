//
// Created by Florian Bruggisser on 21.11.18.
//

#include "Led.h"

void Led::update() {
    this->brightness.update();
}

Led::Led(float easingSpeed) {
    this->brightness = EasingValue(0.0, easingSpeed);
}

void Led::setBrightness(float value, bool easing) {
    if (!easing)
        brightness.set(value);

    brightness.setTarget(value);
}

float Led::getBrightness() {
    return brightness.get();
}

void Led::turnOn(bool easing) {
    setBrightness(LED_MAX_BRIGHTNESS, easing);
}

void Led::turnOff(bool easing) {
    setBrightness(LED_MIN_BRIGHTNESS, easing);
}
