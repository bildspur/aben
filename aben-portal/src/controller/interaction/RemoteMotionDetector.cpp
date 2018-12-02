//
// Created by Florian Bruggisser on 02.12.18.
//

#include "RemoteMotionDetector.h"


RemoteMotionDetector::RemoteMotionDetector(App *app, OscController *osc, uint8_t triggerPin, uint8_t echoPin) :
        TimeBasedController(app->getSettings().getAppFrameRate(), FRAMES_PER_SECOND) {
    this->app = app;
    this->sensor = new HCSR04MotionSensor(triggerPin, echoPin);
    this->osc = osc;
}

void RemoteMotionDetector::setup() {
    TimeBasedController::setup();

    sensor->setup();
}

void RemoteMotionDetector::timedLoop() {
    TimeBasedController::loop();

    sensor->measure();
    auto motionDetected = sensor->isMotionDetected(true);

    if (motionDetected && !pinState) {
        Serial.println("portal has been activated!");
        osc->send("/aben/portal/active", app->getSettings().getPortalId());
    } else if (!motionDetected && pinState) {
        pinState = false;
    }
}