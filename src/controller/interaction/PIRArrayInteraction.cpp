//
// Created by Florian Bruggisser on 22.11.18.
//

#include "PIRArrayInteraction.h"

PIRArrayInteraction::PIRArrayInteraction(Installation *installation, const uint8_t *sensorPins)
        : TimeBasedController(PIR_ARRAY_IX_FPS, FRAMES_PER_SECOND) {
    this->installation = installation;
    this->sensorCount = installation->getSize();

    assert(sensorCount == sizeof(sensorPins));

    // init sensors
    this->sensors = new PIRMotionSensorPtr[sensorCount];
    for (int i = 0; i < sensorCount; i++) {
        this->sensors[i] = new PIRMotionSensor(sensorPins[i]);
    }
}

void PIRArrayInteraction::setup() {
    TimeBasedController::setup();

    // setup sensors
    for (int i = 0; i < sensorCount; i++) {
        this->sensors[i]->setup();
    }
}

void PIRArrayInteraction::timedLoop() {
    TimeBasedController::timedLoop();

    // update sensors and activate doors
    for (int i = 0; i < sensorCount; i++) {
        this->sensors[i]->measure();

        if (sensors[i]->isMotionDetected(true)) {
            this->installation->getPortal(i)->setActivated(true);
        }
    }
}
