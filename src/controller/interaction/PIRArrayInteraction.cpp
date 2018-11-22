//
// Created by Florian Bruggisser on 22.11.18.
//

#include "PIRArrayInteraction.h"

PIRArrayInteraction::PIRArrayInteraction(Installation *installation, const uint8_t *sensorPins,
                                         unsigned int updateFrequency) : BaseController() {
    this->installation = installation;
    this->sensorCount = installation->getSize();

    assert(sensorCount == sizeof(sensorPins));

    // init sensors
    this->sensors = new PIRMotionSensorPtr[sensorCount];
    for (int i = 0; i < sensorCount; i++) {
        this->sensors[i] = new PIRMotionSensor(sensorPins[i], updateFrequency);
    }
}

void PIRArrayInteraction::setup() {
    BaseController::setup();

    // setup sensors
    for (int i = 0; i < sensorCount; i++) {
        this->sensors[i]->setup();
    }
}

void PIRArrayInteraction::loop() {
    BaseController::loop();

    // update sensors and activate doors
    for (int i = 0; i < sensorCount; i++) {
        this->sensors[i]->loop();

        if (sensors[i]->isMotionDetected(true)) {
            this->installation->getPortal(i)->setActivated(true);
        }
    }
}
