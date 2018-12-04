//
// Created by Florian Bruggisser on 02.12.18.
//

#include <util/PinReader.h>
#include <util/StatusLed.h>
#include "RemoteMotionDetector.h"


RemoteMotionDetector::RemoteMotionDetector(App *app, OscController *osc, uint8_t triggerPin, uint8_t echoPin) :
        TimeBasedController(app->getSettings().getAppFrameRate(), FRAMES_PER_SECOND) {
    this->app = app;
    this->sensor = new HCSR04MotionSensor(triggerPin, echoPin, app->getSettings().getMinThreshold());
    this->osc = osc;
}

void RemoteMotionDetector::setup() {
    TimeBasedController::setup();

    sensor->setup();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void RemoteMotionDetector::timedLoop() {
    TimeBasedController::loop();

    // set settings
    sensor->setMinThreshold(app->getSettings().getMinThreshold());
    sensor->measure();

    auto motionDetected = sensor->isMotionDetected(true);

    if (motionDetected && !pinState) {
        Serial.println("portal has been activated!");
        osc->send("/aben/portal/activated", app->getSettings().getPortalId());
        pinState = true;
        digitalWrite(LED_BUILTIN, LOW);
    } else if (!motionDetected && pinState) {
        pinState = false;
        digitalWrite(LED_BUILTIN, HIGH);
    }
}