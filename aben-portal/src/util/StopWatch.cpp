//
// Created by Florian Bruggisser on 23.10.18.
//

#include "StopWatch.h"
#include "Arduino.h"

StopWatch::StopWatch() = default;

void StopWatch::start() {
    running = true;
    startTime = millis();
}

void StopWatch::stop() {
    running = false;
    stopTime = millis();
}

unsigned long StopWatch::elapsed() {
    if (running)
        return millis() - startTime;

    return stopTime - startTime;
}
