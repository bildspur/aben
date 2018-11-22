//
// Created by Florian Bruggisser on 22.11.18.
//

#include "TimeBasedController.h"

TimeBasedController::TimeBasedController(unsigned long time, TimeType timeType) {
    auto waitTime = time;

    // calculate fps
    if (timeType == FRAMES_PER_SECOND)
        waitTime = static_cast<unsigned long>(lround(1000.0 / waitTime));

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
