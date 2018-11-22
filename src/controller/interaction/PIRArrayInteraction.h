//
// Created by Florian Bruggisser on 22.11.18.
//

#ifndef ABEN_PIRARRAYINTERACTION_H
#define ABEN_PIRARRAYINTERACTION_H


#include <controller/BaseController.h>
#include <controller/app/Installation.h>
#include <controller/interaction/sensor/PIRMotionSensor.h>

class PIRArrayInteraction : public TimeBasedController {
private:
    typedef PIRMotionSensor *PIRMotionSensorPtr;

    unsigned int sensorCount;

    PIRMotionSensorPtr *sensors;

    Installation *installation;

    bool running;

public:
    explicit PIRArrayInteraction(Installation *installation, const uint8_t *sensorPins);

    void setup() override;

    void timedLoop() override;

    bool isRunning() const;

    void setRunning(bool running);
};


#endif //ABEN_PIRARRAYINTERACTION_H
