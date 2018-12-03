//
// Created by Florian on 04.12.17.
//

#include "AbenSceneController.h"
#include "SceneController.h"

AbenSceneController::AbenSceneController(Installation *installation, BaseScene *portalScene, BaseScene *showScene) :
        SceneController(installation, portalScene) {
    this->portalScene = portalScene;
    this->showScene = showScene;
}

void AbenSceneController::setup() {
    SceneController::setup();
}

void AbenSceneController::timedLoop() {
    SceneController::loop();
    selectRelevantScene();
}

void AbenSceneController::selectRelevantScene() {
    bool allActivated = areAllPortalsActivated();

    // switch to show scene
    if (allActivated && getActiveScene() != showScene) {
        setActiveScene(showScene);
        Serial.println("switched to show scene!");
    }

    if (!allActivated || showScene->isFinished()) {
        setActiveScene(portalScene);
        Serial.println("switched to portal scene!");
    }
}

bool AbenSceneController::areAllPortalsActivated() {
    bool allActivated = true;
    for (uint8_t i = 0; i < installation->getSize(); i++) {
        if (!installation->getPortal(i)->isActivated())
            allActivated = false;
    }
    return allActivated;
}
