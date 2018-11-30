//
// Created by Florian on 29.11.17.
//

#include "MotionSensor.h"

MotionSensor::MotionSensor() {
}

void MotionSensor::setup() {
}

bool MotionSensor::isMotionDetected(bool clearFlag) {
    bool value = motionDetected;

    // clear value if requested
    if (clearFlag)
        motionDetected = false;

    return value;
}

void MotionSensor::measure() {
    // to implement
}
