//
// Created by Florian Bruggisser on 22.11.18.
//

#include "PIRMotionSensor.h"

PIRMotionSensor::PIRMotionSensor(uint8_t pin, unsigned int updateFrequency) : MotionSensor(updateFrequency) {
    this->pin = pin;
}

void PIRMotionSensor::setup() {
    MotionSensor::setup();

    // setup pin mode
    pinMode(pin, INPUT_PULLDOWN);
}

void PIRMotionSensor::measure() {
    MotionSensor::measure();

    // check pin change
    auto pinValue = digitalRead(pin);

    // pin went high
    if (!pinState && pinValue == HIGH) {
        this->motionDetected = true;
        pinState = true;
    }

    // pin went low
    if (pinState && pinValue == LOW) {
        pinState = false;
    }
}
