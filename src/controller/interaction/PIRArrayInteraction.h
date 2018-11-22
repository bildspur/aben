//
// Created by Florian Bruggisser on 22.11.18.
//

#ifndef ABEN_PIRARRAYINTERACTION_H
#define ABEN_PIRARRAYINTERACTION_H


#include <controller/BaseController.h>
#include <model/Installation.h>
#include <controller/interaction/sensor/PIRMotionSensor.h>

class PIRArrayInteraction : public BaseController {
private:
    typedef PIRMotionSensor *PIRMotionSensorPtr;

    unsigned int sensorCount;

    PIRMotionSensorPtr *sensors;

    Installation *installation;

public:
    explicit PIRArrayInteraction(Installation *installation, uint8_t *sensorPins, unsigned int updateFrequency = 250);

    void setup() override;

    void loop() override;
};


#endif //ABEN_PIRARRAYINTERACTION_H
