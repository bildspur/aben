//
// Created by Florian on 28.11.17.
//

#include "BaseScene.h"

BaseScene::BaseScene(const char *name, Installation *installation) {
    this->name = name;
    this->installation = installation;
}

void BaseScene::setup() {
    BaseController::setup();
}

void BaseScene::loop() {
    BaseController::loop();
}

const char *BaseScene::getName() const {
    return name;
}

bool BaseScene::isFinished() const {
    return finished;
}

void BaseScene::setFinished(bool finished) {
    BaseScene::finished = finished;
}

void BaseScene::reset() {
    this->finished = false;
}
