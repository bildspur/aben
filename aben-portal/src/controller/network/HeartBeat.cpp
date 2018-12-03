//
// Created by Florian Bruggisser on 26.11.18.
//

#include "HeartBeat.h"

HeartBeat::HeartBeat(unsigned long beatTime) : BaseController() {
    this->beatTimer = new Timer(beatTime);
}

void HeartBeat::setup() {
    BaseController::setup();

    beatTimer->reset();
}

void HeartBeat::loop() {
    BaseController::loop();

    if (beatTimer->elapsed()) {
        if (onHeartbeatCallback)
            onHeartbeatCallback();
    }
}

void HeartBeat::onHeartbeat(HeartBeat::HeartbeatHandler onHeartbeatCallback) {
    this->onHeartbeatCallback = onHeartbeatCallback;
}
