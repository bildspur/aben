//
// Created by Florian Bruggisser on 22.11.18.
//

#include "TimeBasedController.h"

TimeBasedController::TimeBasedController(unsigned long waitTime) {
    loopTimer = new Timer(waitTime);
}

void TimeBasedController::setup() {
    BaseController::setup();
}

void TimeBasedController::loop() {
    BaseController::loop();

    // loop timed loop if elapsed
    if (loopTimer->elapsed())
        timedLoop();
}

void TimeBasedController::timedLoop() {

}

TimeBasedController::~TimeBasedController() {
    delete loopTimer;
}
