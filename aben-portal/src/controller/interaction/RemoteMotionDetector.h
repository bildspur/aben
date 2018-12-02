//
// Created by Florian Bruggisser on 02.12.18.
//

#ifndef ABEN_PORTAL_REMOTEMOTIONDETECTOR_H
#define ABEN_PORTAL_REMOTEMOTIONDETECTOR_H


#include <controller/BaseController.h>
#include <controller/interaction/sensor/HCSR04MotionSensor.h>
#include <controller/app/App.h>
#include <controller/network/OscController.h>

class RemoteMotionDetector : public TimeBasedController {
private:
    typedef HCSR04MotionSensor *HCSR04MotionSensorPtr;

    HCSR04MotionSensorPtr sensor;

    App *app;

    OscController *osc;

public:
    RemoteMotionDetector(App *app, OscController *osc, uint8_t triggerPin, uint8_t echoPin);

    void setup() override;

    void timedLoop() override;
};


#endif //ABEN_PORTAL_REMOTEMOTIONDETECTOR_H
