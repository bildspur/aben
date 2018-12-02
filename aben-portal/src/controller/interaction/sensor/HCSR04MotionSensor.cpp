//
// Created by Florian Bruggisser on 22.11.18.
//

#include "HCSR04MotionSensor.h"

HCSR04MotionSensor::HCSR04MotionSensor(uint8_t triggerPin, uint8_t echoPin, float minThreshold)
        : MotionSensor() {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    this->minThreshold = minThreshold;
}

void HCSR04MotionSensor::setup() {
    MotionSensor::setup();

    // setup pin mode
    this->sensor = new NewPing(triggerPin, echoPin, maxDistance);
}

void HCSR04MotionSensor::measure() {
    MotionSensor::measure();

    auto sonic = preciseSonicSpeed();
    auto pingTime = sensor->ping_median(3);

    auto distanceCM = (pingTime / 2.0f) * sonic / 10000.0f;

    Serial.printf("Distance: %f\n", distanceCM);

    if (distanceCM > 0.0 && distanceCM <= minThreshold) {
        motionDetected = true;
    }
}

float HCSR04MotionSensor::getMinThreshold() const {
    return minThreshold;
}

void HCSR04MotionSensor::setMinThreshold(float minThreshold) {
    HCSR04MotionSensor::minThreshold = minThreshold;
}

float HCSR04MotionSensor::preciseSonicSpeed() {
    return 331.5f + (0.6f * theta);
}

float HCSR04MotionSensor::getMaxDistance() const {
    return maxDistance;
}

void HCSR04MotionSensor::setMaxDistance(float maxDistance) {
    HCSR04MotionSensor::maxDistance = maxDistance;
}

float HCSR04MotionSensor::getTheta() const {
    return theta;
}

void HCSR04MotionSensor::setTheta(float theta) {
    HCSR04MotionSensor::theta = theta;
}
