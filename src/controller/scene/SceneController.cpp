//
// Created by Florian on 04.12.17.
//

#include "SceneController.h"

SceneController::SceneController(Installation *installation, BaseScene *defaultScene) :
        TimeBasedController(installation->getSettings().getAppFrameRate(), FRAMES_PER_SECOND) {
    this->installation = installation;
    this->activeScene = defaultScene;
}

void SceneController::setup() {
    TimeBasedController::setup();

    activeScene->setup();
}

void SceneController::timedLoop() {
    TimeBasedController::loop();

    // update scene
    if (running)
        activeScene->loop();
}

BaseScene *SceneController::getActiveScene() const {
    return activeScene;
}

void SceneController::setActiveScene(BaseScene *activeScene) {
    SceneController::activeScene = activeScene;
}

bool SceneController::isRunning() const {
    return running;
}

void SceneController::setRunning(bool running) {
    SceneController::running = running;
}
