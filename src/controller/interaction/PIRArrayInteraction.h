//
// Created by Florian Bruggisser on 22.11.18.
//

#ifndef ABEN_PIRARRAYINTERACTION_H
#define ABEN_PIRARRAYINTERACTION_H


#include <controller/BaseController.h>
#include <model/Installation.h>
#include <controller/interaction/sensor/PIRMotionSensor.h>

#define PIR_ARRAY_IX_FPS 60

class PIRArrayInteraction : public TimeBasedController {
private:
    typedef PIRMotionSensor *PIRMotionSensorPtr;

    unsigned int sensorCount;

    PIRMotionSensorPtr *sensors;

    Installation *installation;

public:
    explicit PIRArrayInteraction(Installation *installation, const uint8_t *sensorPins);

    void setup() override;

    void timedLoop() override;
};


#endif //ABEN_PIRARRAYINTERACTION_H
